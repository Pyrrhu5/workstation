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

#include <Wire.h>
#include <U8g2lib.h>

// OLED 128x32 I2C
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// Rotary encoder
#define CLK 2
#define DT 3

// Menu options
const char* menu_options[] = { "first option", "second option", "third option", "fourth option", "fifth option" };
const int menu_size = sizeof(menu_options) / sizeof(menu_options[0]);
const int detentSensitivity = 2; // how sensitive is the rotary encoder

// Control variables
int shift = 0;
int lastCLKState = 0;
int lastDTState = 0;
int pulseCounter = 0;

void setup_encoder() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  lastCLKState = digitalRead(CLK);
  lastDTState = digitalRead(DT);
}

void setup() {
  u8g2.begin();
  setup_encoder();
  show_menu(shift);
}

void show_menu(int center_index) {
  u8g2.clearBuffer();

  // Previous item
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 10, menu_options[(center_index - 1 + menu_size) % menu_size]);

  // Selected item
  u8g2.setFont(u8g2_font_9x15_tr);
  u8g2.drawStr(0, 23, menu_options[center_index]);

  // Next item
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 32, menu_options[(center_index + 1) % menu_size]);

  u8g2.sendBuffer();
}

void loop() {
  int currentCLKState = digitalRead(CLK);
  int currentDTState = digitalRead(DT);

  if (currentCLKState != lastCLKState) {
    if (currentCLKState == LOW) {
      if (currentDTState != currentCLKState) {
        pulseCounter++;
      } else {
        pulseCounter--;
      }

      if (pulseCounter >= detentSensitivity) {
        shift++;
        pulseCounter = 0;
        shift = (shift % menu_size + menu_size) % menu_size;
        show_menu(shift);
      }
      else if (pulseCounter <= -detentSensitivity) {
        shift--;
        pulseCounter = 0;
        shift = (shift % menu_size + menu_size) % menu_size;
        show_menu(shift);
      }
    }
  }
  lastCLKState = currentCLKState;
}
