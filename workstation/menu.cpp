#include <Arduino.h>

#include <Wire.h>
#include <U8g2lib.h>

#include "menu.h"

constexpr const char* Menu::menuText[];
constexpr uint8_t Menu::menuSize;
constexpr uint8_t Menu::menuOptions[][2];

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C Menu::u8g2(U8G2_R0);

void Menu::format_menu_option(uint8_t index, char* buffer, size_t bufferSize) {
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
  format_menu_option(prev_index, prevBuffer, sizeof(prevBuffer));
  u8g2.drawStr(0, 10, prevBuffer);

  // Selected item
  u8g2.setFont(u8g2_font_9x15_tr);
  char currBuffer[32];
  format_menu_option(center_index, currBuffer, sizeof(currBuffer));
  u8g2.drawStr(0, 23, currBuffer);

  // Next item
  u8g2.setFont(u8g2_font_6x10_tr);
  uint8_t next_index = (center_index + 1) % menuSize;
  char nextBuffer[32];
  format_menu_option(next_index, nextBuffer, sizeof(nextBuffer));
  u8g2.drawStr(0, 32, nextBuffer);

  u8g2.sendBuffer();
}


OptionPair Menu::get_selected(uint8_t center_index) {
    uint8_t first = menuOptions[center_index][0];
    uint8_t second = menuOptions[center_index][1];

    if (second == 255) {
        return {first, first};
    }

    return {first, second};
}


void Menu::begin() {
  // OLED 128x32 I2C
  u8g2.begin();
  show(0);
}


void Menu::clear() {
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}

