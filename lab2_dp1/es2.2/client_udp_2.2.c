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

#define BUFLEN  128
#define TIMEOUT 15

char *prog_name;

int main(int argc, char *argv[]) {
    
    int                sock;
    uint16_t           tport_n;
    uint32_t           taddr_n;
    struct sockaddr_in saddr;
    struct sockaddr_in from;
    socklen_t          fromlen;
    ssize_t            nbytes;

    fd_set             cset;
    struct timeval     tval;

    unsigned int       tbuf[BUFLEN];
    unsigned int       rbuf[BUFLEN];
    unsigned int       tm;

    int                res;

    prog_name = argv[0];

    if (argc != 3) {
        err_quit("USAGE: %s <addres> <port>", prog_name);
    }

    taddr_n = inet_addr(argv[1]);
    if (taddr_n == INADDR_NONE) {
        err_quit("USAGE: %s <port>\n<port> should be an IP address", prog_name);
    }

    tport_n = atoi(argv[2]);
    if (tport_n == 0) {
        err_quit("USAGE: %s <port>\n<port> should be a number", prog_name);
    }

    sock = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    trace( err_msg("(%s) socket created. socket number %d", prog_name, sock) );

    memset(&saddr, 0, sizeof(struct sockaddr));
    saddr.sin_family      = AF_INET;
    saddr.sin_port        = htons(tport_n);
    saddr.sin_addr.s_addr = htonl(taddr_n);


    tm = time(NULL);
    trace( err_msg("(%s) time now %u", prog_name, tm) );
    tbuf[0] = htonl(tm);

    Sendto(sock, (void *) tbuf, sizeof(unsigned int), 0, (struct sockaddr *) &saddr, sizeof(struct sockaddr));
    trace( err_msg("(%s) data has been sent", prog_name) );

    FD_ZERO(&cset);
    FD_SET(sock, &cset);
    tval.tv_sec  = TIMEOUT;
    tval.tv_usec = 0;

    if ((res = Select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == -1) {   
        err_sys ("(%s) error - select() failed", prog_name);
    } else if (res > 0) {
        nbytes = Recvfrom(sock, (void *) rbuf, BUFLEN - 1, 0, (struct sockaddr *) &from, &fromlen);
        if (nbytes == 2 * sizeof(unsigned int)) {
            trace( err_msg("(%s) data has been reached: %u %u", prog_name, ntohl(rbuf[0]), ntohl(rbuf[1])) );
        } else {
            // error if datagram is bigger than 64 bits
            trace( err_msg("(%s) error in response packet", prog_name) );
            printf("ERR: WRONG PACKET DIMENSION\n");    
        }
    } else {  
        // TIMEOUT
        trace( err_msg("(%s) timeout", prog_name) );
        printf("ERR: TIMEOUT\n");        
    }

    Close(sock);
    
    return 0;
}