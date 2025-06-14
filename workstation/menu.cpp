#include <Arduino.h>
#include <Wire.h>

#include <U8g2lib.h>
#include "menu.h"

constexpr const char* Menu::menuText[];
constexpr uint8_t Menu::menuSize;
constexpr uint8_t Menu::menuOptions[][2];

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Menu::u8g2(U8G2_R0);

void Menu::formatMenuOption(uint8_t index, char* buffer, size_t bufferSize) {
  uint8_t first = Menu::menuOptions[index][0];
  uint8_t second = Menu::menuOptions[index][1];

  if (second == 255) {
    snprintf(buffer, bufferSize, "%s", Menu::menuText[first]);
  } else {
    snprintf(buffer, bufferSize, "%s - %s", Menu::menuText[first], Menu::menuText[second]);
  }
}

void Menu::show(int center_index) {
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x10_tr);

  // Previous item
  uint8_t prev_index = (center_index - 1 + menuSize) % menuSize;
  char prevBuffer[32];
  formatMenuOption(prev_index, prevBuffer, sizeof(prevBuffer));
  u8g2.drawStr(0, 10, prevBuffer);

  // Selected item
  u8g2.setFont(u8g2_font_9x15_tr);
  char currBuffer[32];
  formatMenuOption(center_index, currBuffer, sizeof(currBuffer));
  u8g2.drawStr(0, 23, currBuffer);

  // Next item
  u8g2.setFont(u8g2_font_6x10_tr);
  uint8_t next_index = (center_index + 1) % menuSize;
  char nextBuffer[32];
  formatMenuOption(next_index, nextBuffer, sizeof(nextBuffer));
  u8g2.drawStr(0, 32, nextBuffer);

  u8g2.sendBuffer();
}


void Menu::begin() {
  // OLED 128x32 I2C
  u8g2.begin();
  show(0);
}


