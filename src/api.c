#include "api.h"

void handleApiCall(char *cmd) {

    int sock0 = connectToNode(NODE0_HOSTNAME, NODE0_PORTNO);

    sendMessage(sock0, cmd);

    uint32_t responseLength;
    unsigned char* response = NULL;
    responseLength = recv_lengthPrefixed(sock0, &response);

    write(STDOUT_FILENO, response, responseLength);

    free(response);
    close(sock0);

}
