#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

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

#define BUFLEN 65563    /* MAX UDP DATAGRAM LENGTH */

char *prog_name;

int main(int argc, char *argv[]) {
    
    int                sock;
    struct sockaddr_in saddr, from;
    uint16_t           port;
    socklen_t          addrlen;

    ssize_t            nbytes;
    unsigned int       buffer[BUFLEN];
    unsigned int       tm;

    prog_name = argv[0];

    if (argc != 2) {
        err_quit("USAGE: %s <port>", prog_name);
    }

    port = atoi(argv[1]);
    if (port == 0) {
        err_quit("USAGE: %s <port>\n<port> should be a number", prog_name);
    }

    // socket creation
    sock = Socket(AF_INET, SOCK_DGRAM, 0);
    trace( err_msg("(%s) socket created", prog_name) );

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family      = AF_INET;
    saddr.sin_port        = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // socket binding
    Bind(sock, (struct sockaddr *) &saddr, sizeof(saddr));
    trace( err_msg("(%s) listening for UDP packets on %s:%d", prog_name, inet_ntoa(saddr.sin_addr), port) );

    // waiting packets
    for (;;) {
        trace( err_msg("(%s) waiting for packets ...", prog_name) );
        addrlen = sizeof(struct sockaddr_in);
        
        /* RECEIVE */
        nbytes = Recvfrom(sock, (void *) buffer, BUFLEN-1, 0, (struct sockaddr *) &from, &addrlen);
        
        sleep(1);

        if (nbytes == 4) { // ignores if reads more tha 32 bits
            trace( err_msg("(%s) received %u", prog_name, ntohl(buffer[0])) );
            
            tm = time(NULL);
            trace( err_msg("(%s) time now %u", prog_name, tm) );

            buffer[1] = htonl(tm);

            /* SEND */
            Sendto(sock, (void *) buffer, 2 * sizeof(unsigned int), 0, (struct sockaddr *) &from, addrlen);
            trace ( err_msg("(%s) --- sent data %u %u", prog_name, ntohl(buffer[0]), tm) );
        }
    }

    Close(sock);    
    return 0;
}