#include "api.h"

int main(int argc, char **argv) {

    int c;
    int didSomething = 0;

    while((c = getopt(argc, argv, "a:m:c:")) != -1) {

        switch(c) {
            case 'a':
                handleApiCall(optarg);
                didSomething = 1;
                break;
            case 'm':
                printf("MODCLK command: %s\n", optarg); // todo
                didSomething = 1;
                break;
            case 'c':
                printf("CAPTURE command: %s\n", optarg); // todo
                didSomething = 1;
                break;
        }

    }

    if (!didSomething) {

        printf("Usage: \n");
        printf("  $ %s -a <api call>\n", argv[0]);
        printf("  $ %s -m <modclk cmd>\n", argv[0]);
        printf("  $ %s -c <capture cmd>\n", argv[0]);

    }

    return 0;

}
