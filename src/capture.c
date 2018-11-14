#include "capture.h"

void handleCapture(char *cmd) {

    if(gpioInitialise() == PI_INIT_FAILED) {

        fprintf(stderr, "ERROR: gpioInitialise failed\n");

    } else {

        if (gpioSetMode(SHUTTER_GPIO, PI_OUTPUT)) {
            fprintf(stderr, "ERROR: gpioSetMode failed\n");
        }

        if (gpioTrigger(SHUTTER_GPIO, SHUTTER_PULSELEN_US, 1)) {
            fprintf(stderr, "ERROR: gpioTrigger failed\n");
        }

    }

}
