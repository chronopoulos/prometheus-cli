#include <pigpio.h>
#include <stdio.h>

#define SHUTTER_GPIO 21 // raspberry pi pin 40
#define SHUTTER_PULSELEN_US 100

void handleCapture(char*);
