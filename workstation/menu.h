#ifndef MENU_H
#define MENU_H

#include <Wire.h>
#include <U8g2lib.h>

struct OptionPair {
    uint8_t first;
    uint8_t second;
};

class Menu{
    private:
        static constexpr const char* menuText[] = {"Desktop", "Laptop", "No screen"};
        // Items to show in the menu, indexes of menuText
        // 255 means unset, can only be used for the second item
        static constexpr uint8_t menuOptions[][2] = {
            {0, 255},
            {1, 255},
            {0, 1},
            {1, 0},
            {2, 255}
        };
        static U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2;
        static void Menu::format_menu_option(uint8_t index, char* buffer, size_t bufferSize);

    public:
        static void  show(int center_index);
        static void begin();
        static void clear();
        static constexpr uint8_t menuSize = sizeof(menuOptions) / sizeof(menuOptions[0]);
        static OptionPair get_selected(uint8_t center_index);

};


#endif