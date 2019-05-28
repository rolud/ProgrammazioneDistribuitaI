/*
 * Rocco Luigi Scarcella - s267537
 * Esonero Programmazione Distribuita I - Masala
 * Laboratorio 2 Esercizio 3
 * Server per trasferimento file TCP iterativo
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

#ifndef TRACE
#define trace(x) x
#else
#define trace(x)
#endif

#define BKLOG  2
#define BUFLEN 65535

/* FUNCTION PROTOTYPES */
void service(int s);
char *check_get_request(char *getreq);
int  send_file(int s, char *filename);
int  handle_error(int s, char *msg);

/* GLOBAL VARIABLES */
char *prog_name;

int main (int argc, char *argv[]) {

	int                ssock, csock;
	uint16_t           lport_n, lport_h;
	struct sockaddr_in saddr, caddr;
	socklen_t          saddrlen, caddrlen;
	

	prog_name = argv[0];

	if (argc != 2) {
		err_quit("ERROR: wrong number of parameters\nUSAGE: %s <port number>");
	}

	lport_h = atoi(argv[1]);
	if (lport_h == 0) {
		err_quit("ERROR: wrong <port number>");
	}
	lport_n = htons(lport_h);


	ssock = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //todo not exit in case of error

	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family      = AF_INET;
	saddr.sin_port        = lport_n;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	showAddr("Binding to address", &saddr);

	Bind(ssock, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in)); //todo not exit in case of error

	Listen(ssock, BKLOG); //todo not exit in case of error

	for (;;) {
		/* accept connection */
		caddrlen = sizeof(struct sockaddr_in);
		csock = Accept(ssock, (struct sockaddr *) &caddr, &caddrlen);
		showAddr("Accepted connetion from", &caddr);

		// TODO do something
		service(csock);		
		
	}

	// Close(ssock);

	return 0;
}

/*
 * receive get request
 */
void service(int s) {
	ssize_t nbytes;
	char    rbuf[BUFLEN];
	char    *filename;

	for (;;) {
		nbytes = recv(s, (void *) rbuf, BUFLEN - 1, 0);
		if (nbytes < 0) {
			handle_error(s, "READ ERROR");
			break;
 		} else if (nbytes == 0) {
			err_msg("(%s) Connection closed by party on socket %d", prog_name, s);
			Close(s);
			break;
		} else {
			//err_msg("(%s) get request %s", prog_name, rbuf);
			rbuf[nbytes] = '\0';
			filename = check_get_request(rbuf);
			if (filename != NULL) {
				err_msg("(%s) filename %s", prog_name, filename);
				if (send_file(s, filename) > 0) {
					err_msg("(%s) file has been sent", prog_name);
				} else {
					// err_msg("(%s) SEND FILE ERROR", prog_name);
					// Close(s);
					// err_msg("(%s) socket %d closed", prog_name, s);
					handle_error(s, "SEND FILE ERROR");
					break;
				}
			} else {
				// err_msg("(%s) FILE ERROR", prog_name);
				// Close(s);
				// err_msg("(%s) socket %d closed", prog_name, s);
				handle_error(s, "GET REQUEST ERROR");
				break;
			}
		}
	}
}
/*
 * if request is valid returns filename
 * otherwise returns NULL
 */
char *check_get_request(char *getreq) {
	char *filename = NULL;
	int  len = strlen(getreq);
	int  i, j;

	if (len >= 6) {
		if (getreq[0] == 'G' && 
		    getreq[1] == 'E' && 
			getreq[2] == 'T' && 
			getreq[3] == ' ' && 
			getreq[len-2] == '\r' && 
			getreq[len-1] == '\n'
			) {
			err_msg("(%s) get request %s", prog_name, getreq);
				
			
			filename = (char *) malloc((len - 6) * sizeof(char *)); // TODO free
			for (i = 0, j = 4; i < len - 6; i++, j++) {
				filename[i] = getreq[j];
			}
			filename[i] = '\0';
		}
	}

	return filename;
}

/*
 * send file. 
 * returns -1 in case of error
 */
int send_file(int s, char *filename) {
	
	unsigned char  *tbuf;
	ssize_t        nbytes;

	FILE          *fp;
	long          fp_size;
	struct stat   filestat;
	int           file_sz;
	int           timestamp;

	char          *cmd = "+OK\r\n\0";

	/* OPEN FILE */
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		err_msg("(%s) FILE ERROR", prog_name);
		return -1;
	}
	if (stat(filename, &filestat) < 0) {
		err_msg("(%s) FILE ERROR", prog_name);
		return -1;
	}
	printf("(%s) --- file size %d\n", prog_name, (int) filestat.st_size);
	printf("(%s) --- timestamp %d\n", prog_name, (int) filestat.st_ctime);
	file_sz = htonl(filestat.st_size);
	timestamp = htonl(filestat.st_ctime);

	/* SEND COMMAND */
	if (writen(s, cmd, strlen(cmd)) != strlen(cmd)) {
			err_msg("(%s) WRITE SOCKET ERROR", prog_name);
			return -1;	
	}

	/* SEND FILE SIZE */
	if (writen(s, &file_sz, sizeof(int)) != sizeof(int)) {
			err_msg("(%s) WRITE SOCKET ERROR", prog_name);
			return -1;	
	}

	/* READ FILE AND STORE IT IN A BUFFER */
	fseek(fp, 0, SEEK_END);
	fp_size = ftell (fp);
	rewind(fp);

	tbuf = (char*) malloc(fp_size * sizeof(char*));
	if (tbuf == NULL) {
			err_msg("(%s) MEMORY ERROR", prog_name);
			return -1;	
	}

	nbytes = fread(tbuf, 1, fp_size, fp);
	if (nbytes != fp_size) {
			err_msg("(%s) READ FILE ERROR", prog_name);
			return -1;	
	}
	
	/* SEND FILE */
	if (writen(s, tbuf, nbytes) != nbytes) {
		err_msg("(%s) WRITE SOCKET ERROR", prog_name);
		return -1;	
	}

	/* SEND TIMESTAMP */
	if (writen(s, &timestamp, sizeof(timestamp)) != sizeof(timestamp)) {
		err_msg("(%s) WRITE SOCKET ERROR", prog_name);
		return -1;	
	}	
	
	free(tbuf);
	fclose(fp);

	return 1;
}

/*
 * error handler
 * send messagge error to client end close connection
 */
int handle_error(int s, char *msg) {

	char *cmd = "-ERR\r\n\0";
	
	err_msg("(%s) ERR: %s", prog_name, msg);

	if (writen(s, cmd, strlen(cmd)) != strlen(cmd)) {
			err_msg("(%s) WRITE SOCKET ERROR", prog_name);
			return -1;	
	}

	err_msg("(%s) messagge error sent", prog_name);
	
	Close(s);

	err_msg("(%s) socket %d closed", prog_name, s);

	return 1;
}