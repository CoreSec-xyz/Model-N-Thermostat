#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "STM8L052C6.h"

#define LCD_TIMEGRID_MASK (1 << 0)
#define LCD_SUN_MASK (1 << 6)
#define LCD_MOON_MASK (1 << 7)
#define LCD_WINDOW_MASK (1 << 2)
#define LCD_VACATION_MASK (1 << 3)
#define LCD_DEGREES_MASK (1 << 5)
#define LCD_PERCENT_MASK (1 << 1)
#define LCD_BATT_MASK (1 << 5)
#define LCD_AUTO_MASK (1 << 3)
#define LCD_MANUAL_MASK (1 << 7)
#define LCD_COLON_MASK (1 << 1)
#define LCD_POINT1_MASK (1 << 4)
#define LCD_POINT2_MASK (1 << 1)
#define LCD_POINT3_MASK (1 << 6)

#define LCD_MONDAY_MASK (1 << 6)
#define LCD_TUESDAY_MASK (1 << 2)
#define LCD_WEDNESDAY_MASK (1 << 1)
#define LCD_THURSDAY_MASK (1 << 7)
#define LCD_FRIDAY_MASK (1 << 6)
#define LCD_SATURDAY_MASK (1 << 3)
#define LCD_SUNDAY_MASK (1 << 0)

#define LCD_NUM1SEGA_MASK (1 << 4)
#define LCD_NUM1SEGB_MASK (1 << 3)
#define LCD_NUM1SEGC_MASK (1 << 3)
#define LCD_NUM1SEGD_MASK (1 << 0)
#define LCD_NUM1SEGE_MASK (1 << 5)
#define LCD_NUM1SEGF_MASK (1 << 5)
#define LCD_NUM1SEGG_MASK (1 << 1)
#define LCD_NUM1SEGH_MASK (1 << 7)
#define LCD_NUM1SEGI_MASK (1 << 0)
#define LCD_NUM1SEGJ_MASK (1 << 4)

#define LCD_NUM2SEGA_MASK (1 << 1)
#define LCD_NUM2SEGB_MASK (1 << 0)
#define LCD_NUM2SEGC_MASK (1 << 0)
#define LCD_NUM2SEGD_MASK (1 << 5)
#define LCD_NUM2SEGE_MASK (1 << 2)
#define LCD_NUM2SEGF_MASK (1 << 2)
#define LCD_NUM2SEGG_MASK (1 << 6)
#define LCD_NUM2SEGH_MASK (1 << 4)
#define LCD_NUM2SEGI_MASK (1 << 5)
#define LCD_NUM2SEGJ_MASK (1 << 1)

#define LCD_NUM3SEGA_MASK (1 << 6)
#define LCD_NUM3SEGB_MASK (1 << 5)
#define LCD_NUM3SEGC_MASK (1 << 5)
#define LCD_NUM3SEGD_MASK (1 << 2)
#define LCD_NUM3SEGE_MASK (1 << 7)
#define LCD_NUM3SEGF_MASK (1 << 7)
#define LCD_NUM3SEGG_MASK (1 << 3)
#define LCD_NUM3SEGH_MASK (1 << 1)
#define LCD_NUM3SEGI_MASK (1 << 2)
#define LCD_NUM3SEGJ_MASK (1 << 6)

#define LCD_NUM4SEGA_MASK (1 << 3)
#define LCD_NUM4SEGB_MASK (1 << 2)
#define LCD_NUM4SEGC_MASK (1 << 2)
#define LCD_NUM4SEGD_MASK (1 << 7)
#define LCD_NUM4SEGE_MASK (1 << 4)
#define LCD_NUM4SEGF_MASK (1 << 4)
#define LCD_NUM4SEGG_MASK (1 << 0)
#define LCD_NUM4SEGH_MASK (1 << 6)
#define LCD_NUM4SEGI_MASK (1 << 7)
#define LCD_NUM4SEGJ_MASK (1 << 3)

#define LCD_BARGRAPH1_MASK (1 << 4)
#define LCD_BARGRAPH2_MASK (1 << 0)
#define LCD_BARGRAPH3_MASK (1 << 4)
#define LCD_BARGRAPH4_MASK (1 << 0)
#define LCD_BARGRAPH5_MASK (1 << 1)
#define LCD_BARGRAPH6_MASK (1 << 5)
#define LCD_BARGRAPH7_MASK (1 << 1)
#define LCD_BARGRAPH8_MASK (1 << 5)
#define LCD_BARGRAPH9_MASK (1 << 7)
#define LCD_BARGRAPH10_MASK (1 << 3)
#define LCD_BARGRAPH11_MASK (1 << 7)
#define LCD_BARGRAPH12_MASK (1 << 3)
#define LCD_BARGRAPH13_MASK (1 << 4)
#define LCD_BARGRAPH14_MASK (1 << 0)
#define LCD_BARGRAPH15_MASK (1 << 4)
#define LCD_BARGRAPH16_MASK (1 << 0)
#define LCD_BARGRAPH17_MASK (1 << 1)
#define LCD_BARGRAPH18_MASK (1 << 5)
#define LCD_BARGRAPH19_MASK (1 << 1)
#define LCD_BARGRAPH20_MASK (1 << 5)
#define LCD_BARGRAPH21_MASK (1 << 6)
#define LCD_BARGRAPH22_MASK (1 << 2)
#define LCD_BARGRAPH23_MASK (1 << 6)
#define LCD_BARGRAPH24_MASK (1 << 2)


#define LCD_TIMEGRID_ADDR LCD_RAM0
#define LCD_SUN_ADDR LCD_RAM1
#define LCD_MOON_ADDR LCD_RAM1
#define LCD_WINDOW_ADDR LCD_RAM5
#define LCD_VACATION_ADDR LCD_RAM12
#define LCD_DEGREES_ADDR LCD_RAM3
#define LCD_PERCENT_ADDR LCD_RAM7
#define LCD_BATT_ADDR LCD_RAM10
#define LCD_AUTO_ADDR LCD_RAM5
#define LCD_MANUAL_ADDR LCD_RAM8
#define LCD_COLON_ADDR LCD_RAM0
#define LCD_POINT1_ADDR LCD_RAM11
#define LCD_POINT2_ADDR LCD_RAM11
#define LCD_POINT3_ADDR LCD_RAM10

#define LCD_MONDAY_ADDR LCD_RAM8
#define LCD_TUESDAY_ADDR LCD_RAM12
#define LCD_WEDNESDAY_ADDR LCD_RAM12
#define LCD_THURSDAY_ADDR LCD_RAM11
#define LCD_FRIDAY_ADDR LCD_RAM11
#define LCD_SATURDAY_ADDR LCD_RAM11
#define LCD_SUNDAY_ADDR LCD_RAM11

#define LCD_NUM1SEGA_ADDR LCD_RAM1
#define LCD_NUM1SEGB_ADDR LCD_RAM1
#define LCD_NUM1SEGC_ADDR LCD_RAM8
#define LCD_NUM1SEGD_ADDR LCD_RAM12
#define LCD_NUM1SEGE_ADDR LCD_RAM8
#define LCD_NUM1SEGF_ADDR LCD_RAM1
#define LCD_NUM1SEGG_ADDR LCD_RAM5
#define LCD_NUM1SEGH_ADDR LCD_RAM4
#define LCD_NUM1SEGI_ADDR LCD_RAM5
#define LCD_NUM1SEGJ_ADDR LCD_RAM8

#define LCD_NUM2SEGA_ADDR LCD_RAM1
#define LCD_NUM2SEGB_ADDR LCD_RAM1
#define LCD_NUM2SEGC_ADDR LCD_RAM8
#define LCD_NUM2SEGD_ADDR LCD_RAM11
#define LCD_NUM2SEGE_ADDR LCD_RAM8
#define LCD_NUM2SEGF_ADDR LCD_RAM1
#define LCD_NUM2SEGG_ADDR LCD_RAM4
#define LCD_NUM2SEGH_ADDR LCD_RAM4
#define LCD_NUM2SEGI_ADDR LCD_RAM4
#define LCD_NUM2SEGJ_ADDR LCD_RAM8

#define LCD_NUM3SEGA_ADDR LCD_RAM0
#define LCD_NUM3SEGB_ADDR LCD_RAM0
#define LCD_NUM3SEGC_ADDR LCD_RAM7
#define LCD_NUM3SEGD_ADDR LCD_RAM11
#define LCD_NUM3SEGE_ADDR LCD_RAM7
#define LCD_NUM3SEGF_ADDR LCD_RAM0
#define LCD_NUM3SEGG_ADDR LCD_RAM4
#define LCD_NUM3SEGH_ADDR LCD_RAM4
#define LCD_NUM3SEGI_ADDR LCD_RAM4
#define LCD_NUM3SEGJ_ADDR LCD_RAM7

#define LCD_NUM4SEGA_ADDR LCD_RAM0
#define LCD_NUM4SEGB_ADDR LCD_RAM0
#define LCD_NUM4SEGC_ADDR LCD_RAM7
#define LCD_NUM4SEGD_ADDR LCD_RAM10
#define LCD_NUM4SEGE_ADDR LCD_RAM7
#define LCD_NUM4SEGF_ADDR LCD_RAM0
#define LCD_NUM4SEGG_ADDR LCD_RAM4
#define LCD_NUM4SEGH_ADDR LCD_RAM3
#define LCD_NUM4SEGI_ADDR LCD_RAM3
#define LCD_NUM4SEGJ_ADDR LCD_RAM7

#define LCD_BARGRAPH1_ADDR LCD_RAM12
#define LCD_BARGRAPH2_ADDR LCD_RAM9
#define LCD_BARGRAPH3_ADDR LCD_RAM5
#define LCD_BARGRAPH4_ADDR LCD_RAM2
#define LCD_BARGRAPH5_ADDR LCD_RAM2
#define LCD_BARGRAPH6_ADDR LCD_RAM5
#define LCD_BARGRAPH7_ADDR LCD_RAM9
#define LCD_BARGRAPH8_ADDR LCD_RAM12
#define LCD_BARGRAPH9_ADDR LCD_RAM12
#define LCD_BARGRAPH10_ADDR LCD_RAM9
#define LCD_BARGRAPH11_ADDR LCD_RAM5
#define LCD_BARGRAPH12_ADDR LCD_RAM2
#define LCD_BARGRAPH13_ADDR LCD_RAM2
#define LCD_BARGRAPH14_ADDR LCD_RAM6
#define LCD_BARGRAPH15_ADDR LCD_RAM9
#define LCD_BARGRAPH16_ADDR LCD_RAM13
#define LCD_BARGRAPH17_ADDR LCD_RAM13
#define LCD_BARGRAPH18_ADDR LCD_RAM9
#define LCD_BARGRAPH19_ADDR LCD_RAM6
#define LCD_BARGRAPH20_ADDR LCD_RAM2
#define LCD_BARGRAPH21_ADDR LCD_RAM2
#define LCD_BARGRAPH22_ADDR LCD_RAM6
#define LCD_BARGRAPH23_ADDR LCD_RAM9
#define LCD_BARGRAPH24_ADDR LCD_RAM13

struct DisplayData{
    uint8_t timegrid : 1; // Show time grid below bargraph
    uint8_t sun : 1;
    uint8_t moon : 1;
    uint8_t window : 1;
    uint8_t vacation : 1;
    uint8_t degrees : 1;
    uint8_t percent : 1;
    uint8_t battery : 1;
    uint8_t automatic : 1;
    uint8_t manual : 1;
    uint8_t colon : 1;
    uint8_t point1 : 1; // Show decimal point under colon
    uint8_t point2 : 1; // Show decimal point left to right number
    uint8_t point3 : 1; // Show deciaml point right to right number

    // Select Weekdays to show, bitencoded (LSB/Bit 0=Monday, MSB/Bit 6=Sunday)
    uint8_t weekdays : 7;

    uint16_t num1segments : 10; // Number on the left side, bitencoded
    uint16_t num2segments : 10; // Middle left number, bitencoded
    uint16_t num3segments : 10; // Middle right number, bitencoded
    uint16_t num4segments : 10; // Number on the right side, bitencoded

    uint32_t bargraph; // 24 Bit Bar on top, bitencoded
};

void initDisplay();
void setDisplay(const struct DisplayData * const data);

#endif //DISPLAY_H