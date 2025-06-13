#ifndef REMOTES_H
#define REMOTES_H

#include <Arduino.h>

class ButtonRemote{
    /* Represents a remote control manipulated by physical buttons. 
     * 
     * Set the BUTTON_PINS to the correct arduino pins.
     * 
     * Each button on the remote is connected to the arduino on a digital pin
     * The ground of the arduino should go to a/all buttons' ground of the remote.
     * Check with a voltmeter which pad of the circuit board is which:
     * Ground indicates 0, the control should up/down when a button is pressed
     * 
     */
private:
    // This assumes that the first item is button 1, the second, 2, etc.
    static constexpr uint8_t BUTTON_PINS[] = {A0, A1, A2, A3};
    static constexpr size_t PIN_COUNT = sizeof(BUTTON_PINS) / sizeof(BUTTON_PINS[0]);
    // delay between press and release key, increase it up to 255
    // if press_button does not affect the remote controller
    static constexpr uint8_t DELAY_MS = 100;
public:
    static void begin();
    static void press_button(uint8_t button_number);
};

class IRRemote{
    /* Represents a remote control manipulated by infrared.
     *
     * This has been tailored for Aten's vs481b, the IR codes might be different.
     *
     */
private:
    static constexpr uint8_t IR_COMMANDS[] = {0x4, 0x5, 0x6, 0x1E};
    static constexpr size_t CMD_COUNT = sizeof(IR_COMMANDS) / sizeof(IR_COMMANDS[0]);
    // The address of the target device
    static constexpr uint8_t DEVICE_ADDRESS = 0x0;
    // How many times a command should be sent
    static constexpr uint8_t COMMAND_REPEAT = 0;
    static constexpr uint8_t IR_PIN = 11;
public:
    static void begin();
    static void press_button(uint8_t button_number);
};


#endif