#include "api.h"
#include "modclk.h"
#include "capture.h"

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
                handleModclk(optarg);
                didSomething = 1;
                break;
            case 'c':
                handleCapture(optarg);
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
