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
 */

#include <Arduino.h>
#include "rotary_encoder.h"
#include "menu.h"


void setup() {
  setup_menu();
  setup_encoder();
}

void loop() {
  Rotation rotationEvent = rotation_event();
  if (rotationEvent != NO_ROTATION) {
    on_rotation(rotationEvent);
  }
}
