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

const char* menu_options[3] = { "first option", "second option", "third option" };

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

void show_menu(const char* items[3]) {
  /* Shows a menu of three items where items[1] is bigger (show as "selected") */
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 10, items[0]);

  u8g2.setFont(u8g2_font_9x15_tr);
  u8g2.drawStr(0, 23, items[1]);

  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 32, items[2]);

  u8g2.sendBuffer();
}

void update_menu(int local_shift) {
  /* Menu display loop */
  const char* menu[3] = {
    menu_options[(local_shift + 0) % 3],
    menu_options[(local_shift + 1) % 3],
    menu_options[(local_shift + 2) % 3]
  };
  show_menu(menu);
}

void update_shift() {
  /* Increment and decrement the shift control variable */
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

    local_shift = (local_shift % 3 + 3) % 3;

    if (local_shift != displayed_shift) {
      update_menu(local_shift);
      displayed_shift = local_shift;
    }
  }
}
