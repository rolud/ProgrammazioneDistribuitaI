/* s267537
   Programmazione Distribuita I
   Laboratorio 1 - Esercizio 1.3 - 28/03/19 */

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

#define BFF_LEN 3

char *prog_name;

int send_buffer(int s, char* ptr, size_t nbytes, int flags) {
    size_t  nleft;
    ssize_t nwritten;

    for (nleft = nbytes; nleft > 0; ) {
        nwritten = send(s, (void*) ptr, nleft, 0);
        if (nwritten <= 0) { // error
            //return nwritten;
            err_quit ("(%s) error - sendto() failed", prog_name);
        } else {
            nleft -= (size_t) nwritten;
            ptr += nwritten;
        }
    }

    return (nbytes - nleft);
}

int isnumber(char *str) {
    int i;
    for (i = 0; i < strlen(str) - 2; i++) {
        if (!isdigit(str[i]) ) {
            return 0; // is not a number
        }
    }
    return 1; // is a number
}

int main (int argc, char *argv[]) {

    int                s;
    uint32_t           taddr_n;
    uint16_t           tport_n;
    struct sockaddr_in saddr;

    char               data1[64], data2[64];
    char*              buffer;
    int                buffer_size;

    char               str_res[100];

    prog_name = argv[0];

    if (argc != 3) {
        err_quit("usage: %s <address> <port>", prog_name);
    }


    // taddr_n = atoi(argv[1]); => no buono su indirizzo
    if (inet_aton(argv[1], (struct in_addr*) &taddr_n) == 0) {
        err_quit("usage: %s <address> <port>\n<address> should be xxx.xxx.xxx.xxx", prog_name);
    }
    
    tport_n = atoi(argv[2]);
    if (tport_n == 0) {
        err_quit("usage: %s <address> <port>\n<port> should be an integer", prog_name);
    }

    s = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family         = AF_INET;
    saddr.sin_port           = htons(tport_n);
    saddr.sin_addr.s_addr    = htonl(taddr_n);

    // connessione
    printf("Connecting to ...\n");
    Connect(s, (struct sockaddr*) &saddr, sizeof(saddr));
    printf("Connected to %s:%d\n", argv[1], tport_n);

    // acquisizione interi
    printf("Insert two integer separeted by a space\n");
    scanf("%s%s", data1, data2);

    // calcolo dimensione buffer
    buffer_size = strlen(data1) + strlen(data2) + 3;
    //printf(" buffer size --> %d\n", buffer_size);

    // allocazione buffer    
    buffer = (char*) malloc(buffer_size * sizeof(char));

    // costruzione stringa
    memcpy(buffer, data1, strlen(data1));
    memcpy(buffer + strlen(data1), " ", 1);
    memcpy(buffer + strlen(data1) + 1, data2, strlen(data2));
    memcpy(buffer + strlen(data1) + strlen(data2) + 1, "\r\n", 2);
    //memcpy(buffer + strlen(data1) + strlen(data2) + 3, "\0", 1);

    //printf(" buffer --> %s \n", buffer);

    if (send_buffer(s, buffer, buffer_size, 0) == 0) {
        printf("Error\n");
    }

    //recv_response(s, buffer_res);
    readline(s, (void*) str_res, 100);
    //printf("res --> %s\n", buffer_res);
    if (str_res != NULL) {
        if (isnumber(str_res)) {
            printf("The result is: %s", str_res);
        } else {
            printf("ERR: %s", str_res);
        }
    }


    Close(s);
    
    printf("Connection closed\n");

    //free(&saddr);
    //free(buffer);

    return 0;
}

