#include <Arduino.h>
#include "remotes.h"


void ButtonRemote::press_button(uint8_t button_number) {
    if (button_number < PIN_COUNT) {
        digitalWrite(BUTTON_PINS[button_number], LOW);
        delay(DELAY_MS);
        digitalWrite(BUTTON_PINS[button_number], HIGH);
    } // Error handling is too mainstream
}