#ifndef MENU_H
#define MENU_H
#include <Wire.h>
#include <U8g2lib.h>


class Menu{
    private:
        static constexpr const char* menuOptions[] = { "first option", "second option", "third option", "fourth option", "fifth option" };
        static constexpr uint8_t menuSize = sizeof(menuOptions) / sizeof(menuOptions[0]);
        static U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2;

    public:
        static void  show(int center_index);
        static void begin();
};


#endif