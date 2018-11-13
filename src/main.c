#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>

#define NODE0_HOSTNAME "prometheusBone0.local"
#define NODE0_PORTNO 50660

#define NODE1_HOSTNAME "prometheusBone1.local"
#define NODE1_PORTNO 50660


int main(int argc, char **argv) {

    // create sockets
    int sock0, sock1;
    sock0 = socket(AF_INET, SOCK_STREAM, 0);
    sock1 = socket(AF_INET, SOCK_STREAM, 0);
    if ((sock0 < 0) || (sock1 < 0)) {
        fprintf(stderr, "ERROR: could not create sockets\n");
        return 1;
    }

    // connect to node 0
    struct sockaddr_in addr;
    struct hostent *he;
    struct in_addr **addr_list;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(NODE0_PORTNO);
    he = gethostbyname(NODE0_HOSTNAME);
    if (he == NULL) {
        fprintf(stderr, "ERROR: invalid hostname: %s\n", NODE0_HOSTNAME);
        return 1;
    } else {
        addr.sin_family = he->h_addrtype;
        addr_list = (struct in_addr **)he->h_addr_list;
        if(inet_pton(he->h_addrtype, inet_ntoa(*addr_list[0]), &addr.sin_addr) <= 0) {
            fprintf(stderr, "ERROR: inet_pton() failed\n");
            return 1;
        }
    }
    if(connect(sock0, (struct sockaddr *)&addr, sizeof(addr)) <= 0) {
        fprintf(stderr, "ERROR: connect() failed\n");
        return 1;
    }

    // connect to node 1
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(NODE1_PORTNO);
    he = gethostbyname(NODE1_HOSTNAME);
    if (he == NULL) {
        fprintf(stderr, "ERROR: invalid hostname: %s\n", NODE1_HOSTNAME);
        return 1;
    } else {
        addr.sin_family = he->h_addrtype;
        addr_list = (struct in_addr **)he->h_addr_list;
        if(inet_pton(he->h_addrtype, inet_ntoa(*addr_list[0]), &addr.sin_addr) <= 0) {
            fprintf(stderr, "ERROR: inet_pton() failed\n");
            return 1;
        }
    }
    if(connect(sock0, (struct sockaddr *)&addr, sizeof(addr)) <= 0) {
        fprintf(stderr, "ERROR: connect() failed\n");
        return 1;
    }

    // prepare a message for the server
    char msgBuf[256];
    j = 0; // char index
    for (i=1; i<argc; i++) {
        strcpy(msgBuf + j, argv[i]);
        j += strlen(argv[i]);
        msgBuf[j] = 0x20; // space
        j += 1;
    }
    msgBuf[j] = 0x00; // null

    // send the message
    send(sock0, msgBuf, strlen(msgBuf), MSG_NOSIGNAL);

    // read length prefix
    uint32_t responseLength;
    recv(sock0, &responseLength, 4, 0);

    // read response
    unsigned char *responseBuf = (unsigned char *) malloc(responseLength);
    recv(sock0, responseBuf, responseLength, 0);

    // write binary data to stdout
    write(STDOUT_FILENO, responseBuf, responseLength);

    // clean up
    free(responseBuf);
    close(sock0);

    return 0;

}
