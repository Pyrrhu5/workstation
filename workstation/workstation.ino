/*
 * Pins layout:
 * - OLED display:
 *    + VCC --> 5v
 *    + SCL --> A5
 *    + SDA --> A4
 * - Rotary encoder:
 *    + VCC --> 5v
 *    + CLK --> D2
 *    + DT  --> D3
 *    + SW  --> D4
 *  * Can be changed in remotes.h:
 * - IR emitter
 *    + D11
 * - Physical remote
 *    +  A0 to A3
 */

#include <Arduino.h>

#include "rotary_encoder.h"
#include "menu.h"
#include "remotes.h"

void setup() {
  Menu::begin();
  setup_encoder();
  IRRemote::begin();
  ButtonRemote::begin();
  // Serial.begin(9600);
  // while (!Serial);
  // Serial.println("Ready");
}

void loop() {
  Rotation rotationEvent = rotation_event();
  if (rotationEvent != NO_ROTATION) {
    on_rotation(rotationEvent);
  }
  if (click_event()){
    on_click();
  }
}
