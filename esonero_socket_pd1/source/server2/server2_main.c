/*
 * Rocco Luigi Scarcella - s267537
 * Esonero Programmazione Distribuita I - Masala
 * Laboratorio 3 Esercizio 1
 * Server per trasferimento file TCP concorrente
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
#include <signal.h>

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

#define BKLOG   2
#define BUFLEN  65535 // 1024
#define TIMEOUT 15

/* FUNCTION PROTOTYPES */
void service(int s);
char *check_get_request(char *getreq);
int  send_file(int s, char *filename);
int  handle_error(int s, char *msg, int flag);
int  accept_connection(int listen_sockfd, SA *cliaddr, socklen_t *addrlenp);

/* GLOBAL VARIABLES */
char *prog_name;

int main (int argc, char *argv[]) {

	int                ssock, csock;
	uint16_t           lport_n, lport_h;
	struct sockaddr_in saddr, caddr;
	socklen_t          saddrlen, caddrlen;

	pid_t              pid;

	

	(void) signal(SIGCHLD, SIG_IGN); // avoid zombie child

	prog_name = argv[0];

	if (argc != 2) {
		err_quit("ERROR: wrong number of parameters\nUSAGE: %s <port number>");
	}

	lport_h = atoi(argv[1]);
	if (lport_h == 0) {
		err_quit("ERROR: wrong <port number>");
	}
	lport_n = htons(lport_h);


	ssock = Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 

	memset(&saddr, 0, sizeof(struct sockaddr_in));
	saddr.sin_family      = AF_INET;
	saddr.sin_port        = lport_n;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);

	showAddr("Binding to address", &saddr);

	Bind(ssock, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in)); 

	Listen(ssock, BKLOG); 

	for (;;) {
		/* accept connection */
		caddrlen = sizeof(struct sockaddr_in);
		csock = accept_connection(ssock, (struct sockaddr *) &caddr, &caddrlen);
		showAddr("Accepted connetion from", &caddr);

		if ((pid = fork()) < 0) {
			// fatal error
			err_sys("fork() failed");
		} else if (pid > 0) {
			/* FATHER */
			err_msg("(%s) connection handled by process %d", prog_name, pid);

			// close connection on father
			Close(csock);

		} else {
			/* CHILD */
			sprintf(prog_name, "%s [CHILD-%d]", argv[0], getpid());

			service(csock);

			exit(0);
		}

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
	
	fd_set         cset;
	struct timeval tval;
	int            res_sf, res_sel;

	for (;;) {
		FD_ZERO(&cset);
		FD_SET(s, &cset);
		tval.tv_sec  = TIMEOUT;
		tval.tv_usec = 0;

		if ((res_sel = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {
			err_sys ("(%s) error - select() failed", prog_name);
		} else if (res_sel > 0) {
			// wait for +OK\r\n
			nbytes = recv(s, (void *) rbuf, BUFLEN - 1, 0);
			if (nbytes < 0) {
				handle_error(s, "READ ERROR", 0);
				break;
			} else if (nbytes == 0) {
				err_msg("(%s) Connection closed by party on socket %d", prog_name, s);
				handle_error(s, "Connection closed by party", 0);
				break;
			} else {
				rbuf[nbytes] = '\0';
				filename = check_get_request(rbuf);
				if (filename != NULL) {
					trace( err_msg("(%s) --- filename %s", prog_name, filename) );
					if ( (res_sf = send_file(s, filename)) > 0) {
						// file sent
						trace( err_msg("(%s) file has been sent", prog_name) );
						free(filename);
					} else if (res_sf == -2) {
						// file error
						handle_error(s, "FILE ERROR", 1);
						free(filename);
						break;
					} else {
						// send file error
						handle_error(s, "SEND FILE ERROR", 0);
						free(filename);
						break;
					}
				} else {
					// get error
					handle_error(s, "GET REQUEST ERROR", 1);
					free(filename);
					break;
				}
			}
		} else {
			// TIMEOUT
			err_msg("(%s) - timeout waiting for data from client, connection will be closed", prog_name);
			handle_error(s, "TIMEOUT", 1);
			break;
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
			// err_msg("(%s) get request %s", prog_name, getreq);


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

	// unsigned char  *tbuf;
	unsigned char tbuf[BUFLEN]; 
	ssize_t       nbytes;

	FILE          *fp;
	long          fp_size;
	struct stat   filestat;
	int           file_sz;
	int           timestamp;

	char          *cmd = "+OK\r\n\0";

	/* OPEN FILE */
	fp = fopen(filename, "rb");
	if (fp == NULL) {
		trace( err_msg("(%s) FILE ERROR", prog_name) );
		return -2;
	}
	if (stat(filename, &filestat) < 0) {
		trace( err_msg("(%s) FILE ERROR", prog_name) );
		return -2;
	}
	trace( printf("(%s) --- file size %d\n", prog_name, (int) filestat.st_size) );
	trace( printf("(%s) --- timestamp %d\n", prog_name, (int) filestat.st_ctime) );
	file_sz = htonl(filestat.st_size);
	timestamp = htonl(filestat.st_ctime);
	
	/* SEND COMMAND */
	if (sendn(s, cmd, strlen(cmd), MSG_NOSIGNAL) != strlen(cmd)) {
			trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
			return -1;
	}

	/* SEND FILE SIZE */
	if (sendn(s, &file_sz, sizeof(int), MSG_NOSIGNAL) != sizeof(int)) {
			trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
			return -1;
	}

	/* READ FILE AND STORE IT IN A BUFFER */
	fseek(fp, 0, SEEK_END);
	fp_size = ftell (fp);
	rewind(fp);

	int sent = 0;
	while (!sent) {
		nbytes = fread(tbuf, 1, sizeof(tbuf), fp);
		if(nbytes != sizeof(tbuf)) {
			
			if (feof(fp)) {
				// end of file
				/* SEND DATA */
				if (sendn(s, tbuf, nbytes, MSG_NOSIGNAL) != nbytes) {
					trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
					fclose(fp);
					return -1;
				}
				sent = 1;
				// break;
			}

			if (ferror(fp))	{
				// error
				trace( err_msg("(%s) READ ERROR", prog_name) );
				fclose(fp);
				return -1;
			}

		} else {
			/* SEND DATA */
			if (sendn(s, tbuf, nbytes, MSG_NOSIGNAL) != nbytes) {
				trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
				fclose(fp);
				return -1;
			}
		}
	}


	/* SEND TIMESTAMP */
	if (sendn(s, &timestamp, sizeof(timestamp), MSG_NOSIGNAL) != sizeof(timestamp)) {
		trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
		return -1;
	}

	fclose(fp);

	return 1;
}

/*
 * error handler
 * send messagge error to client if flag==1
 * and close connection
 */
int handle_error(int s, char *msg, int flag) {

	char *cmd = "-ERR\r\n\0";

	if (flag) {
		if (sendn(s, cmd, strlen(cmd), MSG_NOSIGNAL) != strlen(cmd)) {
				trace( err_msg("(%s) WRITE SOCKET ERROR", prog_name) );
				return -1;
		}
		trace( err_msg("(%s) messagge error sent", prog_name) );
	}

	Close(s);

	trace( err_msg("(%s) socket %d closed", prog_name, s) );

	return 1;
}

int accept_connection (int listen_sockfd, SA *cliaddr, socklen_t *addrlenp) {
	int conn_sockfd;
	int retry = 1;
	while (retry) {
		retry = 0;
		if ( (conn_sockfd = accept(listen_sockfd, cliaddr, addrlenp)) < 0) {
			if (INTERRUPTED_BY_SIGNAL ||
				errno == EPROTO || errno == ECONNABORTED ||
				errno == EMFILE || errno == ENFILE ||
				errno == ENOBUFS || errno == ENOMEM			
				) {
				retry = 1;
				trace( err_msg ("(%s) error - accept() failed, now try again", prog_name); );
			}
			else {
				trace( err_msg ("(%s) error - accept() failed", prog_name) );
				continue;
			}
		} else {
			// accepted
			retry = 0;
		}
	}
	return conn_sockfd;
}