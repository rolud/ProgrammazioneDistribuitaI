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
    s_server = Socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    trace( err_msg("(%s) socket created", prog_name) );


    memset(&server_addr, 0, sizeof(server_addr));
    //memset(&client_addr, 0, sizeof(client_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(lport_n);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* 0.0.0.0 */

    // bind
    saddrlen = sizeof(server_addr);
    Bind(s_server, (struct sockaddr *) &server_addr, saddrlen);
    trace( err_msg("(%s) listening for UDP packets on %s:%d", prog_name, inet_ntoa(server_addr.sin_addr), (int) lport_n) );

    // receive dgram and send response
    for (;;) {
        trace( err_msg("(%s) waiting for packet ...", prog_name) );
        nbytes = Recvfrom(s_server, (void *) buf, (size_t) BUFLEN, 0, (struct sockaddr *) &client_addr, &caddrlen);
        if (nbytes < BUFLEN)
            buf[nbytes] = '\0';
        trace( err_msg("(%s) --- received string %s", prog_name, buf) );

        printf("--- client sin_family %d\n", client_addr.sin_family);
        printf("--- client sin_port %d\n", client_addr.sin_port);
        printf("--- client sin_addr %s\n", inet_ntoa(client_addr.sin_addr));
        //client_addr.sin_family = AF_INET;

        printf("--- buffer -> %s\n", buf);
        printf("--- buf size -> %d\n", (int) strlen(buf));

        Sendto(s_server, (void *) buf, strlen(buf), 0, (struct sockaddr *) &client_addr, caddrlen);
        trace ( err_msg("(%s) --- sent string %s", prog_name, buf) );
    }

    Close(s_server);

    return 0;
}