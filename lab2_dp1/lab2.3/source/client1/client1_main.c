/*
 * Rocco Luigi Scarcella - s267537
 * Esonero Programmazione Distribuita I - Masala
 * Laboratorio 2 Esercizio 3
 * Client per trasferimento file TCP iterativo
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

#define BUFLEN 65535
#define TIMEOUT 15

void request(int s, char **files, int nfiles);
int  get_request(int s, char *filename);
void save_file(char *filename, unsigned char *buf, int size, int timestamp);
void handle_error(int s, char *msg);

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
	printf("(%s) creating socket ... ", prog_name);
	csock = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	printf("done\n");

	/* PREPARE ADDRESS STRUCTURE */
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family      = AF_INET;
	saddr.sin_port        = tport_n;
	saddr.sin_addr.s_addr = taddr_h;

	/* CONNECT */
	showAddr("connecting to address", &saddr);
	Connect(csock, (struct sockaddr *) &saddr, sizeof(saddr));
	printf("done\n");

	request(csock, argv+3, argc-3);

	Close(csock);


	return 0;
}

void request(int s, char **files, int nfiles) {
	unsigned char  tbuf[BUFLEN];
	unsigned char  rbuf[BUFLEN];
	unsigned char  *buf;

	ssize_t        nbytes;

	fd_set         cset;
	struct timeval tval;

	char           *cmd;
	int            file_size, timestamp;
	int            res, i;

	char *sendcmd = "+OK\r\n";

	for (i = 0; i < nfiles; i++) {

		if (get_request(s, files[i]) == -1) break;

		FD_ZERO(&cset);
		FD_SET(s, &cset);
		tval.tv_sec  = TIMEOUT;
		tval.tv_usec = 0;

		if ((res = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
			err_sys ("(%s) error - select() failed", prog_name);
		} else if (res > 0) {
			// READ SERVER COMMAND
			nbytes = readline_unbuffered(s, rbuf, BUFLEN);
			if (nbytes == 5) {
				// received +OK from server
				// printf("(%s) ---OK--- %s\n", prog_name, rbuf);
			
				// READ FILE SIZE
				nbytes = readn(s, &file_size, sizeof(int));
				if (nbytes != sizeof(int)) {handle_error(s, "READ SOCKET ERROR");}
				file_size = htonl(file_size);

				// READ FILE
				buf = (unsigned char*) malloc(file_size * sizeof(unsigned char*));
				if (buf == NULL) {free(buf); handle_error(s, "MEMORY ERROR");}
				nbytes = readn(s, buf, file_size);
				if (nbytes != file_size) {handle_error(s, "READ SOCKET ERROR");}

				// READ TIMESTAMP
				nbytes = readn(s, &timestamp, sizeof(int));
				if (nbytes != sizeof(int)) {handle_error(s, "READ SOCKET ERROR");}
				timestamp = htonl(timestamp);

				save_file(files[i], buf, file_size, timestamp);

				free(buf);

			} else if (nbytes == 6) {
				// received -ERR from server
				handle_error(s, "ERR received from server");
			} else {
				// generic read error
				handle_error(s, "READ SOCKET ERROR");
			}


		} else {
			// TIMEOUT
			handle_error(s, "TIMEOUT");
		}
	}
}

int get_request(int s, char *filename) {
	char cmd[100];
	strcpy(cmd, "GET ");
	strcat(cmd, filename);
	strcat(cmd, "\r\n\0");

	if (writen(s, cmd, strlen(cmd)) != strlen(cmd)) {
		err_msg("(%s) WRITE SOCKET ERROR", prog_name);
		return -1;
	}

	return 1;
}

void save_file(char *filename, unsigned char *buf, int size, int timestamp) {

	FILE *fp;
	
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		err_msg("(%s) OPEN FILE ERROR", prog_name);
		exit(-1);
	}

	if (fwrite(buf, sizeof(unsigned char), size, fp) != size) {
		err_msg("(%s) WRITE FILE ERROR", prog_name);
		exit(-1);
	}

	printf("Received file           %s\n", filename);
	printf("Received file size      %d\n", size);
	printf("Received file timestamp %d\n", timestamp);

	fclose(fp);
}

void handle_error(int s, char *msg) {
	
	err_msg("(%s) ERR: %s", prog_name, msg);

	Close(s);

	err_msg("(%s) connection closed", prog_name, s);

	exit(1);
}