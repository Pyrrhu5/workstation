#include <Arduino.h>
#include <Wire.h>

#include <U8g2lib.h>

// OLED 128x32 I2C
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

// Menu options
const char* menuOptions[] = { "first option", "second option", "third option", "fourth option", "fifth option" };
const int menuSize = sizeof(menuOptions) / sizeof(menuOptions[0]);


void show_menu(int center_index) {
  u8g2.clearBuffer();

  // Previous item
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 10, menuOptions[(center_index - 1 + menuSize) % menuSize]);

  // Selected item
  u8g2.setFont(u8g2_font_9x15_tr);
  u8g2.drawStr(0, 23, menuOptions[center_index]);

  // Next item
  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(0, 32, menuOptions[(center_index + 1) % menuSize]);

  u8g2.sendBuffer();
}


void setup_menu() {
  u8g2.begin();
  show_menu(0);
}
