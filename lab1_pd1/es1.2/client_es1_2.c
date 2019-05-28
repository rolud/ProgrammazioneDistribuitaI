/* s267537
   Programmazione Distribuita 1 
   Laboratorio 1 - Esercizio 1.2 - 28/03/19 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <unistd.h>

#include "errlib.h"
#include "sockwrap.h"


#ifdef TRACE
#define trace(x) x
#else
#define trace(x)
#endif

char *prog_name;

int main (int argc, char *argv[]) {

	int                s;
	uint32_t           taddr_n; // uint32_t == int
	uint16_t           tport_n; // uint16_t == short
	struct sockaddr_in saddr;
	

	prog_name = argv[0];
	
	if (argc != 3) {
		err_quit("usage: %s <address> <port>", prog_name);
	}

	taddr_n = atoi(argv[1]);
	tport_n = atoi(argv[2]);

	s  = Socket(AF_INET, SOCK_STREAM, 0); // check inside

	memset(&saddr, 0, sizeof(saddr)); // alloco struct
	saddr.sin_family        = AF_INET;
	saddr.sin_port          = htons(tport_n);
	saddr.sin_addr.s_addr   = htonl(taddr_n);

	Connect(s, (struct sockaddr*) &saddr, sizeof(saddr)); // check inside

	//printf("Connessione riuscita\n");
	printf("Connected to %s:%d\n", argv[1], tport_n);

	Close(s);

	printf("Connessione chiusa\n");	

	return 0;
}

