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

    int                s_server/*, s_client*/;
    uint16_t           lport_n;
    struct sockaddr_in server_addr, client_addr;
    socklen_t          saddrlen, caddrlen;

    char               buf[BUFLEN];
    size_t             nbytes;

    prog_name = argv[0];

    if (argc != 2) {
        err_quit("USAGE: %s <port>", prog_name);
    }

    lport_n = atoi(argv[1]);
    if (lport_n == 0) {
        err_quit("USAGE: %s <port>\n<port> should be a number", prog_name);
    }

    // socket creation
    s_server = Socket(AF_INET, SOCK_DGRAM, 0);
    printf("(%s) socket created\n", prog_name);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(lport_n);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* 0.0.0.0 */


    // bind
    saddrlen = sizeof(struct sockaddr_in);
    Bind(s_server, (struct sockaddr *) &server_addr, saddrlen);
    printf("(%s) listening for UDP packets on %s:%d\n", prog_name, inet_ntoa(server_addr.sin_addr), (int) lport_n);

    // receive dgram and send response
    for (;;) {
        printf("(%s) waiting for packet ...\n", prog_name);
        nbytes = Recvfrom(s_server, (void *) buf, (size_t) BUFLEN, 0, (struct sockaddr *) &client_addr, &caddrlen);
        if (nbytes < BUFLEN)
            buf[nbytes] = '\0';
        printf("(%s) --- received string %s\n", prog_name, buf);

        printf("---  sin_family %d\n", client_addr.sin_family);

        Sendto(s_server, (void *) buf, (size_t) strlen(buf), 0, (struct sockaddr *) &client_addr, caddrlen);
    }

    Close(s_server);

    return 0;
}