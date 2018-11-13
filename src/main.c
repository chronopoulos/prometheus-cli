#include "network.h"

int main(int argc, char **argv) {

    int sock0 = connectToNode(NODE0_HOSTNAME, NODE0_PORTNO);

    sendMessage(sock0, argc, argv);

    uint32_t responseLength;
    unsigned char* response = NULL;
    responseLength = recv_lengthPrefixed(sock0, &response);

    write(STDOUT_FILENO, response, responseLength);

    close(sock0);
    free(response);

    return 0;

}
