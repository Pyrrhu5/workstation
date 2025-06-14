#include <Arduino.h>
#include <Wire.h>

#include <U8g2lib.h>
#include "menu.h"

constexpr const char* Menu::menuOptions[];
constexpr uint8_t Menu::menuSize;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Menu::u8g2(U8G2_R0);
void Menu::show(int center_index) {
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


void Menu::begin() {
  // OLED 128x32 I2C
  u8g2.begin();
  show(0);
}


