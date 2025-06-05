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

// Control variables
volatile int shift = 0;
volatile bool rotated = false;
int lastCLK = 0;

void setup_encoder() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  lastCLK = digitalRead(CLK);
  // Register on rotary encoder rotation event
  attachInterrupt(digitalPinToInterrupt(CLK), update_shift, CHANGE);
}

void setup() {
  u8g2.begin();
  setup_encoder();
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

void update_shift() {
  int currentCLK = digitalRead(CLK);
  if (currentCLK != lastCLK) {
    if (digitalRead(DT) != currentCLK) {
      shift++;
    } else {
      shift--;
    }
    rotated = true;
  }
  lastCLK = currentCLK;
}

void loop() {
  static int displayed_shift = -1;

  // Bounce protection
  if (rotated) {
    noInterrupts();
    int local_shift = shift;
    rotated = false;
    interrupts();

    local_shift = (local_shift % menu_size + menu_size) % menu_size;

    if (local_shift != displayed_shift) {
      show_menu(local_shift);
      displayed_shift = local_shift;
    }
  }
}
