#ifndef MENU_H
#define MENU_H

#include <Wire.h>
#include <U8g2lib.h>


class Menu{
    private:
        static constexpr const char* menuText[] = {"Desktop", "Laptop", "No screen"};
        // Items to show in the menu, indexes of menuText
        // 255 means unset
        static constexpr uint8_t menuOptions[][2] = {
            {0, 255},
            {1, 255},
            {0, 1},
            {1, 0},
            {2, 255}
        };
        static U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2;
        static void Menu::formatMenuOption(uint8_t index, char* buffer, size_t bufferSize);

    public:
        static void  show(int center_index);
        static void begin();
        static constexpr uint8_t menuSize = sizeof(menuOptions) / sizeof(menuOptions[0]);
};


#endif