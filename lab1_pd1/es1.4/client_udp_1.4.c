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

#define BUFLEN 31

char *prog_name;

int main (int argc, char *argv[]) {
    
    int                s;
    uint16_t           tport_n;
    uint32_t           taddr_n;
    struct sockaddr_in saddr;
    socklen_t          addrlen;

    char               *buf;
    size_t             nbytes;
    int                n;
    fd_set             cset;

    /* timeout */
    struct timeval     tval;
    int                t = 1; 
    tval.tv_sec  = t;
    tval.tv_usec = 0;

    prog_name = argv[0];

    if (argc != 4) {
        err_quit("USAGE: %s <address> <port> <string>", prog_name);
    }

    if (inet_aton(argv[1], (struct in_addr *) &taddr_n) == 0) {
        err_quit("USAGE: %s <address> <port> <string>\n<addres> should be an IPv4 address", prog_name);
    }

    tport_n = atoi(argv[2]);
    if (tport_n == 0) {
        err_quit("USAGE: %s <address> <port> <string>\n<port> should be a number", prog_name);
    }

    buf = argv[3];
    if (strlen(buf) > BUFLEN) {
        err_quit("USAGE: %s <address> <port> <string>\n<string> lenght can not be higher than 31", prog_name);
    }

    s = Socket(AF_INET, SOCK_DGRAM, 0);
    printf("(%s) socket created\n", prog_name);

    saddr.sin_family      = AF_INET;
    saddr.sin_port        = htons(tport_n);
    saddr.sin_addr.s_addr = htonl(taddr_n);

    addrlen = sizeof(struct sockaddr_in);
    Sendto(s, (void *) buf, strlen(buf), 0, (struct sockaddr *) &saddr, addrlen);
    printf("(%s) - data has been sent\n", prog_name);

    FD_ZERO(&cset);
    FD_SET(s, &cset);

    if ((n = select(FD_SETSIZE, &cset, NULL, NULL, &tval)) == 0) {
        err_quit("select() failed");
    }
    if (n > 0) {
        nbytes = Recvfrom(s, (void *) buf, BUFLEN, 0, (struct sockaddr *) &saddr, &addrlen);
        if (nbytes < BUFLEN)
            buf[nbytes] = '\0';
        printf("(%s) Received: %s\n", prog_name, buf);
    } else {
        printf("Timeout.\n");
    }
        
    Close(s);
    
    return 0;
}