/*
 * Rocco Luigi Scarcella - s267537
 * Esonero Programmazione Distribuita I - Masala
 * Laboratorio 2 Esercizio 3
 * Client per trasferimento file TCP 
 */

/*
 * TEMPLATE
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>

#include "../errlib.h"
#include "../sockwrap.h"

#ifdef TRACE
#define trace(x) x
#else
#define trace(x)
#endif

#define BUFLEN  65535 // 1024
#define TIMEOUT 15

/* FUNCION PROTOTYPES */
void get_files(int s, char **files, int nfiles);
int  send_request(int s, char *filename);
void handle_error(int s, char *msg);

/* GLOBAL VARIABLES */
char *prog_name;

int main (int argc, char *argv[]) {

	int                csock;
	uint16_t           tport_n, tport_h; /* server port number net/host */
 	uint32_t           taddr_n, taddr_h; /* server IP addres net/host */
	struct sockaddr_in saddr;

	prog_name = argv[0];

	if (argc < 4) {
		err_quit("ERROR: wrong number of parameters\nUSAGE: %s <address> <port number> <file> ...");
	}

	taddr_h = inet_addr(argv[1]);
	if (taddr_h == INADDR_NONE) {
        err_quit("USAGE: %s <address>\n<address> should be an IP address", prog_name);
	}
	taddr_n = htons(taddr_h);


	tport_h = atoi(argv[2]);
	if (tport_h == 0) {
		err_quit("ERROR: wrong <port number>");
	}
	tport_n = htons(tport_h);

	/* CREATE SOCKET */
	trace( printf("(%s) creating socket ... ", prog_name) );
	csock = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	trace( printf("done\n") );

	/* PREPARE ADDRESS STRUCTURE */
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family      = AF_INET;
	saddr.sin_port        = tport_n;
	saddr.sin_addr.s_addr = taddr_h;

	/* CONNECT */
	showAddr("connecting to address", &saddr);
	Connect(csock, (struct sockaddr *) &saddr, sizeof(saddr));
	trace( printf("done\n") );
	
	get_files(csock, argv+3, argc-3);

	Close(csock);

	return 0;
}

/**
 * sends transfer request to server
 * receives and stores files  
 */
void get_files(int s, char **files, int nfiles) {
	unsigned char  tbuf[BUFLEN];
	unsigned char  rbuf[BUFLEN];

	ssize_t        nbytes, rbytes, len;

	fd_set         cset;
	struct timeval tval;

	int            file_size, timestamp;
	int            res, i;

	char           *request_accepted = "+OK\r\n";

	FILE           *fp;

	for (i = 0; i < nfiles; i++) {

		if (send_request(s, files[i]) == -1) {handle_error(s, "GET REQUEST ERROR");}

		FD_ZERO(&cset);
		FD_SET(s, &cset);
		tval.tv_sec  = TIMEOUT;
		tval.tv_usec = 0;

		if ((res = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
			err_sys ("(%s) error - select() failed", prog_name);
		} else if (res > 0) {
			// READ SERVER COMMAND
			nbytes = readline_unbuffered(s, rbuf, BUFLEN);
			if (nbytes == 5 && strcmp(request_accepted, rbuf) == 0) {
				// received +OK from server
				// now read file data from socket
			
				fp = fopen(files[i], "wb");
				if (fp == NULL) {
					trace( err_msg("(%s) OPEN FILE ERROR", prog_name) );
					exit(-1);
				}

				FD_ZERO(&cset); FD_SET(s, &cset);
				tval.tv_sec = TIMEOUT; tval.tv_usec = 0;
				if ((res = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
					err_sys ("(%s) error - select() failed", prog_name);
				} else if (res > 0) {

					// READ FILE SIZE
					nbytes = readn(s, &file_size, sizeof(int));
					if (nbytes != sizeof(int)) {handle_error(s, "READ SOCKET ERROR 1");}
					file_size = htonl(file_size);
				} else {
					// TIMEOUT
					err_msg("(%s) - timeout waiting for file size", prog_name);
					handle_error(s, "TIMEOUT");
				}

				FD_ZERO(&cset); FD_SET(s, &cset);
				tval.tv_sec = TIMEOUT; tval.tv_usec = 0;
				if ((res = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
					err_sys ("(%s) error - select() failed", prog_name);
				} else if (res > 0) {
					/* READ AND SAVE FILE */
					rbytes = 0;
					while (rbytes < file_size) {

						if((file_size - rbytes) < BUFLEN) len = file_size - rbytes;
						else len = BUFLEN;

						nbytes = readn(s, rbuf, len);

						/* SAVE DATA ON FILE */
						if (fwrite(rbuf, sizeof(unsigned char), nbytes, fp) != nbytes) {
							trace( err_msg("(%s) WRITE FILE ERROR", prog_name) );
							exit(-1);
						}

						rbytes += nbytes;
					}
				} else {
					// TIMEOUT
					err_msg ("(%s) - timeout waiting for file data", prog_name);
					handle_error(s, "TIMEOUT");
				}

				FD_ZERO(&cset); FD_SET(s, &cset);
				tval.tv_sec = TIMEOUT; tval.tv_usec = 0;
				if ((res = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
					err_sys ("(%s) error - select() failed", prog_name);
				} else if (res > 0) {
					/* READ TIMESTAMP */
					nbytes = readn(s, &timestamp, sizeof(int));
					if (nbytes != sizeof(int)) {handle_error(s, "READ SOCKET ERROR");}
					timestamp = htonl(timestamp);
				} else {
					// TIMEOUT
					err_msg ("(%s) - timeout waiting for file timestamp", prog_name);
					handle_error(s, "TIMEOUT");
				}

				printf("----------------------------------\n");
				printf("Received file           %s\n", files[i]);
				printf("Received file size      %d\n", file_size);
				printf("Received file timestamp %d\n", timestamp);

				fclose(fp);

			} else if (nbytes == 6) {
				// received -ERR from server
				handle_error(s, "ERR received from server");
			} else {
				// generic read error
				handle_error(s, "READ SOCKET ERROR");
			}


		} else {
			// TIMEOUT
			err_msg("(%s) - timeout waiting for request response", prog_name);
			handle_error(s, "TIMEOUT");
		}
	}
}
/**
 * sends get command to server
 */
int send_request(int s, char *filename) {
	char cmd[BUFLEN];
	strcpy(cmd, "GET ");
	strcat(cmd, filename);
	strcat(cmd, "\r\n\0");

	if (sendn(s, cmd, strlen(cmd), 0) != strlen(cmd)) {
		trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
		return -1;
	}

	return 1;
}

/**
 * prints an error message on console, 
 * closes the connection and exit
 */
void handle_error(int s, char *msg) {
	
	trace( err_msg("(%s) ERR: %s", prog_name, msg) );

	Close(s);

	trace( err_msg("(%s) connection closed", prog_name, s) );

	exit(1);
}