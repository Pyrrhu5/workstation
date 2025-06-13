#include <Arduino.h>
#include <IRremote.hpp>
#include "remotes.h"


constexpr uint8_t ButtonRemote::BUTTON_PINS[];

void ButtonRemote::begin() {
    for (int i = 0; i < PIN_COUNT; i++){
		pinMode(BUTTON_PINS[i], OUTPUT);
		digitalWrite(BUTTON_PINS[i], HIGH);
	}
}


void ButtonRemote::press_button(uint8_t button_number) {
    if (button_number < PIN_COUNT) {
        digitalWrite(BUTTON_PINS[button_number], LOW);
        delay(DELAY_MS);
        digitalWrite(BUTTON_PINS[button_number], HIGH);
    } // Error handling is too mainstream
}


constexpr uint8_t IRRemote::IR_COMMANDS[];

void IRRemote::begin() {
    IrSender.begin(IR_PIN);
}

void IRRemote::press_button(uint8_t button_number) {
	IrSender.sendNEC(DEVICE_ADDRESS, IR_COMMANDS[button_number], COMMAND_REPEAT);
}