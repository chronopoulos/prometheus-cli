#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char **argv) {

    // create socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("ERROR: could not create socket\n");
        return 1;
    }

    // define connection address
    struct sockaddr_in node_addr;
    memset(&node_addr, '\0', sizeof(node_addr));
    node_addr.sin_family = AF_INET;
    node_addr.sin_port = htons(50660);
    if(inet_pton(AF_INET, "10.0.5.253", &node_addr.sin_addr) <= 0) {
        printf("ERROR: invalid address\n");
        return 1;
    }

    // make a connection
    if(connect(sockfd, (struct sockaddr *)&node_addr, sizeof(node_addr)) < 0) {
        printf("ERROR: connect() failed\n");
        return 1;
    }

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
    printf("debug: %s\n", msgBuf);

    // send the message
    send(sockfd, msgBuf, strlen(msgBuf), MSG_NOSIGNAL);

    // close the socket
    close(sockfd);

    return 0;

}
