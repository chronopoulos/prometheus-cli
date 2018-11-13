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

int connectToNode(const char *hostname, uint16_t portno) {

    // create a socket
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        fprintf(stderr, "ERROR: could not create sockets\n");
        return -1;
    }

    // fill out sockaddr_in
    struct sockaddr_in addr;
    struct hostent *he;
    struct in_addr **addr_list;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(NODE0_PORTNO);
    he = gethostbyname(NODE0_HOSTNAME);
    if (he == NULL) {
        fprintf(stderr, "ERROR: invalid hostname: %s\n", NODE0_HOSTNAME);
        return -1;
    } else {
        addr.sin_family = he->h_addrtype;
        addr_list = (struct in_addr **)he->h_addr_list;
        if(inet_pton(he->h_addrtype, inet_ntoa(*addr_list[0]), &addr.sin_addr) <= 0) {
            fprintf(stderr, "ERROR: inet_pton() failed\n");
            return -1;
        }
    }

    // connect
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        fprintf(stderr, "ERROR: connect() failed\n");
        return -1;
    }

    return sock;
}

void sendMessage(int sock, int argc, char **argv) {

    // prepare a message for the server
    char msgBuf[256];
    int i,j;

    j = 0; // char index
    for (i=1; i<argc; i++) {
        strcpy(msgBuf + j, argv[i]);
        j += strlen(argv[i]);
        msgBuf[j] = 0x20; // space
        j += 1;
    }
    msgBuf[j] = 0x00; // null

    send(sock, msgBuf, strlen(msgBuf), MSG_NOSIGNAL);

}

void readResponse_lengthPrefixed(int sock) {

    uint32_t responseLength;
    unsigned char *responseBuf;

    // read length prefix
    recv(sock, &responseLength, 4, 0);

    // read response
    responseBuf = (unsigned char *) malloc(responseLength);
    recv(sock, responseBuf, responseLength, 0);

    // free memory
    free(responseBuf);

}

int main(int argc, char **argv) {

    int sock0 = connectToNode(NODE0_HOSTNAME, NODE0_PORTNO);

    sendMessage(sock0, argc, argv);
    readResponse_lengthPrefixed(sock0);

    close(sock0);

    return 0;

}
