#include "display.h"

void initDisplay() {
    // CLK_CRTCR- Clock RTC register
    CLK_CRTCR = 0x10; // Selects the source provided on to RTC and its divider

    // CLK_PCKENR2 - Peripheral clock gating register 2
    CLK_PCKENR2 |= (1 << 2); // Enable Clock for RTC
    CLK_PCKENR2 |= (1 << 3); // Enable Clock for LCD

    // LCD_FRQ - LCD frequency selection register
    LCD_FRQ  = 0x00;     // Clear prescaler and divider bits
    LCD_FRQ |= (1 << 4); // Set clock prescaler bits to prescaler 2 (clock input/2)
    LCD_FRQ |= (1 << 1); // Set divider bits to LCD_Divider_18 (clock prescaler/18)

    // LCD_CR1-3 LCD control registers
    LCD_CR1 &= ~0x07;   // Clear the duty bits and B2 bit
    LCD_CR1 |= 0x06;    // Set Duty cycle to LCD_Duty_1_4
    LCD_CR1 |= 0x00;    // Set Bias to LCD_Bias_1_3

    LCD_CR2 &= ~0xEF;   // Clear voltage source, contrast and pulses on duration bits.
    LCD_CR2 |= 0x00;    // Set Voltage Source for LCD to Internal
    LCD_CR2 |= 0x08;    // Configure LCD contrast. Select the maximum voltage Vlcd of 3.00V / 3.12V
    LCD_CR2 |= 0x20;    // Configure LCD Pulse on duration = 1/CLKprescaler

    LCD_CR3 &= ~0x07;   // Clear the dead time bits
    LCD_CR3 |= 0x00;    // Set to No dead Time

    // LCD_PM0-2 LCD Port mask registers
    // Configure pins that are not used for LCD as standard GPIOs.
    LCD_PM0 = 0xFF;
    LCD_PM1 = 0xFF;
    LCD_PM2 = 0x7B; //0b01111011;

    // Enable the LCD peripheral
    LCD_CR3 |= 0x40;
}

uint16_t numSegments(const uint8_t number) {
    uint16_t segments = 0x0000;
    switch (number) {
        case 0: segments = 0x003F; break;
        case 1: segments = 0x0006; break;
        case 2: segments = 0x00DB; break;
        case 3: segments = 0x00CF; break;
        case 4: segments = 0x00E6; break;
        case 5: segments = 0x00ED; break;
        case 6: segments = 0x00FD; break;
        case 7: segments = 0x0007; break;
        case 8: segments = 0x00FF; break;
        case 9: segments = 0x00EF; break;
    }
    return segments;
}

uint16_t charSegments(const uint8_t c) {
    uint16_t segments = 0x0000;
    switch (c) {
        case 'a': case 'A': segments = 0x00F7; break;
        case 'b': case 'B': segments = 0x00FC; break;
        case 'c': segments = 0x00D8; break;
        case 'C': segments = 0x0039; break;
        case 'd': segments = 0x00DE; break;
        case 'D': segments = 0x010F; break;
        case 'e': case 'E': segments = 0x00F9; break;
        case 'f': case 'F': segments = 0x00F1; break;
        case 'g': case 'G': segments = 0x00BD; break;
        case 'h': segments = 0x00F4; break;
        case 'H': segments = 0x00F6; break;
        case 'i': case 'I': segments = 0x0109; break;
        case 'j': case 'J': segments = 0x008C; break;
        case 'k': case 'K': segments = 0x0380; break;
        case 'l': case 'L': segments = 0x0038; break;
        case 'm': case 'M': segments = 0x0137; break;
        case 'n': segments = 0x00D4; break;
        case 'N': segments = 0x0037; break;
        case 'o': case 'O': segments = 0x00DC; break;
        case 'p': case 'P': segments = 0x00F3; break;
        case 'q': case 'Q': segments = 0x023F; break;
        case 'r': segments = 0x00D0; break;
        case 'R': segments = 0x02F3; break;
        case 's': case 'S': segments = 0x00ED; break;
        case 't': case 'T': segments = 0x0101; break;
        case 'u': segments = 0x001C; break;
        case 'U': segments = 0x003E; break;
        case 'v': case 'V': segments = 0x0204; break;
        case 'w': case 'W': segments = 0x013E; break;
        // x not possible
        case 'y': case 'Y': segments = 0x00EE; break;
        case 'z': case 'Z': segments = 0x00DB; break;
        case '0': case 0: segments = numSegments(0); break;
        case '1': case 1: segments = numSegments(1); break;
        case '2': case 2: segments = numSegments(2); break;
        case '3': case 3: segments = numSegments(3); break;
        case '4': case 4: segments = numSegments(4); break;
        case '5': case 5: segments = numSegments(5); break;
        case '6': case 6: segments = numSegments(6); break;
        case '7': case 7: segments = numSegments(7); break;
        case '8': case 8: segments = numSegments(8); break;
        case '9': case 9: segments = numSegments(9); break;
        case ' ': segments = 0x0000; break;
        case '+': segments = 0x01C0; break;
        case '-': segments = 0x00C0; break;
    }
    return segments;
}

void setDisplay(const struct DisplayData * const data) {
    data->timegrid ? (LCD_TIMEGRID_ADDR |= LCD_TIMEGRID_MASK) : (LCD_TIMEGRID_ADDR &= ~LCD_TIMEGRID_MASK);
    data->sun ? (LCD_SUN_ADDR |= LCD_SUN_MASK) : (LCD_SUN_ADDR &= ~LCD_SUN_MASK);
    data->moon ? (LCD_MOON_ADDR |= LCD_MOON_MASK) : (LCD_MOON_ADDR &= ~LCD_MOON_MASK);
    data->window ? (LCD_WINDOW_ADDR |= LCD_WINDOW_MASK) : (LCD_WINDOW_ADDR &= ~LCD_WINDOW_MASK);
    data->vacation ? (LCD_VACATION_ADDR |= LCD_VACATION_MASK) : (LCD_VACATION_ADDR &= ~LCD_VACATION_MASK);
    data->degrees ? (LCD_DEGREES_ADDR |= LCD_DEGREES_MASK) : (LCD_DEGREES_ADDR &= ~LCD_DEGREES_MASK);
    data->percent ? (LCD_PERCENT_ADDR |= LCD_PERCENT_MASK) : (LCD_PERCENT_ADDR &= ~LCD_PERCENT_MASK);
    data->battery ? (LCD_BATT_ADDR |= LCD_BATT_MASK) : (LCD_BATT_ADDR &= ~LCD_BATT_MASK);
    data->automatic ? (LCD_AUTO_ADDR |= LCD_AUTO_MASK) : (LCD_AUTO_ADDR &= ~LCD_AUTO_MASK);
    data->manual ? (LCD_MANUAL_ADDR |= LCD_MANUAL_MASK) : (LCD_MANUAL_ADDR &= ~LCD_MANUAL_MASK);
    data->colon ? (LCD_COLON_ADDR |= LCD_COLON_MASK) : (LCD_COLON_ADDR &= ~LCD_COLON_MASK);
    data->point1 ? (LCD_POINT1_ADDR |= LCD_POINT1_MASK) : (LCD_POINT1_ADDR &= ~LCD_POINT1_MASK);
    data->point2 ? (LCD_POINT2_ADDR |= LCD_POINT2_MASK) : (LCD_POINT2_ADDR &= ~LCD_POINT2_MASK);
    data->point3 ? (LCD_POINT3_ADDR |= LCD_POINT3_MASK) : (LCD_POINT3_ADDR &= ~LCD_POINT3_MASK);

    (data->weekdays & (1 << 0)) ?
        (LCD_MONDAY_ADDR |= LCD_MONDAY_MASK) : (LCD_MONDAY_ADDR &= ~LCD_MONDAY_MASK);
    (data->weekdays & (1 << 1)) ?
        (LCD_TUESDAY_ADDR |= LCD_TUESDAY_MASK) : (LCD_TUESDAY_ADDR &= ~LCD_TUESDAY_MASK);
    (data->weekdays & (1 << 2)) ?
        (LCD_WEDNESDAY_ADDR |= LCD_WEDNESDAY_MASK) : (LCD_WEDNESDAY_ADDR &= ~LCD_WEDNESDAY_MASK);
    (data->weekdays & (1 << 3)) ?
        (LCD_THURSDAY_ADDR |= LCD_THURSDAY_MASK) : (LCD_THURSDAY_ADDR &= ~LCD_THURSDAY_MASK);
    (data->weekdays & (1 << 4)) ?
        (LCD_FRIDAY_ADDR |= LCD_FRIDAY_MASK) : (LCD_FRIDAY_ADDR &= ~LCD_FRIDAY_MASK);
    (data->weekdays & (1 << 5)) ?
        (LCD_SATURDAY_ADDR |= LCD_SATURDAY_MASK) : (LCD_SATURDAY_ADDR &= ~LCD_SATURDAY_MASK);
    (data->weekdays & (1 << 6)) ?
        (LCD_SUNDAY_ADDR |= LCD_SUNDAY_MASK) : (LCD_SUNDAY_ADDR &= ~LCD_SUNDAY_MASK);

    (data->num1segments & (1 << 0)) ?
        (LCD_NUM1SEGA_ADDR |= LCD_NUM1SEGA_MASK) : (LCD_NUM1SEGA_ADDR &= ~LCD_NUM1SEGA_MASK);
    (data->num1segments & (1 << 1)) ?
        (LCD_NUM1SEGB_ADDR |= LCD_NUM1SEGB_MASK) : (LCD_NUM1SEGB_ADDR &= ~LCD_NUM1SEGB_MASK);
    (data->num1segments & (1 << 2)) ?
        (LCD_NUM1SEGC_ADDR |= LCD_NUM1SEGC_MASK) : (LCD_NUM1SEGC_ADDR &= ~LCD_NUM1SEGC_MASK);
    (data->num1segments & (1 << 3)) ?
        (LCD_NUM1SEGD_ADDR |= LCD_NUM1SEGD_MASK) : (LCD_NUM1SEGD_ADDR &= ~LCD_NUM1SEGD_MASK);
    (data->num1segments & (1 << 4)) ?
        (LCD_NUM1SEGE_ADDR |= LCD_NUM1SEGE_MASK) : (LCD_NUM1SEGE_ADDR &= ~LCD_NUM1SEGE_MASK);
    (data->num1segments & (1 << 5)) ?
        (LCD_NUM1SEGF_ADDR |= LCD_NUM1SEGF_MASK) : (LCD_NUM1SEGF_ADDR &= ~LCD_NUM1SEGF_MASK);
    (data->num1segments & (1 << 6)) ?
        (LCD_NUM1SEGG_ADDR |= LCD_NUM1SEGG_MASK) : (LCD_NUM1SEGG_ADDR &= ~LCD_NUM1SEGG_MASK);
    (data->num1segments & (1 << 7)) ?
        (LCD_NUM1SEGH_ADDR |= LCD_NUM1SEGH_MASK) : (LCD_NUM1SEGH_ADDR &= ~LCD_NUM1SEGH_MASK);
    (data->num1segments & (1 << 8)) ?
        (LCD_NUM1SEGI_ADDR |= LCD_NUM1SEGI_MASK) : (LCD_NUM1SEGI_ADDR &= ~LCD_NUM1SEGI_MASK);
    (data->num1segments & (1 << 9)) ?
        (LCD_NUM1SEGJ_ADDR |= LCD_NUM1SEGJ_MASK) : (LCD_NUM1SEGJ_ADDR &= ~LCD_NUM1SEGJ_MASK);

    (data->num2segments & (1 << 0)) ?
        (LCD_NUM2SEGA_ADDR |= LCD_NUM2SEGA_MASK) : (LCD_NUM2SEGA_ADDR &= ~LCD_NUM2SEGA_MASK);
    (data->num2segments & (1 << 1)) ?
        (LCD_NUM2SEGB_ADDR |= LCD_NUM2SEGB_MASK) : (LCD_NUM2SEGB_ADDR &= ~LCD_NUM2SEGB_MASK);
    (data->num2segments & (1 << 2)) ?
        (LCD_NUM2SEGC_ADDR |= LCD_NUM2SEGC_MASK) : (LCD_NUM2SEGC_ADDR &= ~LCD_NUM2SEGC_MASK);
    (data->num2segments & (1 << 3)) ?
        (LCD_NUM2SEGD_ADDR |= LCD_NUM2SEGD_MASK) : (LCD_NUM2SEGD_ADDR &= ~LCD_NUM2SEGD_MASK);
    (data->num2segments & (1 << 4)) ?
        (LCD_NUM2SEGE_ADDR |= LCD_NUM2SEGE_MASK) : (LCD_NUM2SEGE_ADDR &= ~LCD_NUM2SEGE_MASK);
    (data->num2segments & (1 << 5)) ?
        (LCD_NUM2SEGF_ADDR |= LCD_NUM2SEGF_MASK) : (LCD_NUM2SEGF_ADDR &= ~LCD_NUM2SEGF_MASK);
    (data->num2segments & (1 << 6)) ?
        (LCD_NUM2SEGG_ADDR |= LCD_NUM2SEGG_MASK) : (LCD_NUM2SEGG_ADDR &= ~LCD_NUM2SEGG_MASK);
    (data->num2segments & (1 << 7)) ?
        (LCD_NUM2SEGH_ADDR |= LCD_NUM2SEGH_MASK) : (LCD_NUM2SEGH_ADDR &= ~LCD_NUM2SEGH_MASK);
    (data->num2segments & (1 << 8)) ?
        (LCD_NUM2SEGI_ADDR |= LCD_NUM2SEGI_MASK) : (LCD_NUM2SEGI_ADDR &= ~LCD_NUM2SEGI_MASK);
    (data->num2segments & (1 << 9)) ?
        (LCD_NUM2SEGJ_ADDR |= LCD_NUM2SEGJ_MASK) : (LCD_NUM2SEGJ_ADDR &= ~LCD_NUM2SEGJ_MASK);

    (data->num3segments & (1 << 0)) ?
        (LCD_NUM3SEGA_ADDR |= LCD_NUM3SEGA_MASK) : (LCD_NUM3SEGA_ADDR &= ~LCD_NUM3SEGA_MASK);
    (data->num3segments & (1 << 1)) ?
        (LCD_NUM3SEGB_ADDR |= LCD_NUM3SEGB_MASK) : (LCD_NUM3SEGB_ADDR &= ~LCD_NUM3SEGB_MASK);
    (data->num3segments & (1 << 2)) ?
        (LCD_NUM3SEGC_ADDR |= LCD_NUM3SEGC_MASK) : (LCD_NUM3SEGC_ADDR &= ~LCD_NUM3SEGC_MASK);
    (data->num3segments & (1 << 3)) ?
        (LCD_NUM3SEGD_ADDR |= LCD_NUM3SEGD_MASK) : (LCD_NUM3SEGD_ADDR &= ~LCD_NUM3SEGD_MASK);
    (data->num3segments & (1 << 4)) ?
        (LCD_NUM3SEGE_ADDR |= LCD_NUM3SEGE_MASK) : (LCD_NUM3SEGE_ADDR &= ~LCD_NUM3SEGE_MASK);
    (data->num3segments & (1 << 5)) ?
        (LCD_NUM3SEGF_ADDR |= LCD_NUM3SEGF_MASK) : (LCD_NUM3SEGF_ADDR &= ~LCD_NUM3SEGF_MASK);
    (data->num3segments & (1 << 6)) ?
        (LCD_NUM3SEGG_ADDR |= LCD_NUM3SEGG_MASK) : (LCD_NUM3SEGG_ADDR &= ~LCD_NUM3SEGG_MASK);
    (data->num3segments & (1 << 7)) ?
        (LCD_NUM3SEGH_ADDR |= LCD_NUM3SEGH_MASK) : (LCD_NUM3SEGH_ADDR &= ~LCD_NUM3SEGH_MASK);
    (data->num3segments & (1 << 8)) ?
        (LCD_NUM3SEGI_ADDR |= LCD_NUM3SEGI_MASK) : (LCD_NUM3SEGI_ADDR &= ~LCD_NUM3SEGI_MASK);
    (data->num3segments & (1 << 9)) ?
        (LCD_NUM3SEGJ_ADDR |= LCD_NUM3SEGJ_MASK) : (LCD_NUM3SEGJ_ADDR &= ~LCD_NUM3SEGJ_MASK);

    (data->num4segments & (1 << 0)) ?
        (LCD_NUM4SEGA_ADDR |= LCD_NUM4SEGA_MASK) : (LCD_NUM4SEGA_ADDR &= ~LCD_NUM4SEGA_MASK);
    (data->num4segments & (1 << 1)) ?
        (LCD_NUM4SEGB_ADDR |= LCD_NUM4SEGB_MASK) : (LCD_NUM4SEGB_ADDR &= ~LCD_NUM4SEGB_MASK);
    (data->num4segments & (1 << 2)) ?
        (LCD_NUM4SEGC_ADDR |= LCD_NUM4SEGC_MASK) : (LCD_NUM4SEGC_ADDR &= ~LCD_NUM4SEGC_MASK);
    (data->num4segments & (1 << 3)) ?
        (LCD_NUM4SEGD_ADDR |= LCD_NUM4SEGD_MASK) : (LCD_NUM4SEGD_ADDR &= ~LCD_NUM4SEGD_MASK);
    (data->num4segments & (1 << 4)) ?
        (LCD_NUM4SEGE_ADDR |= LCD_NUM4SEGE_MASK) : (LCD_NUM4SEGE_ADDR &= ~LCD_NUM4SEGE_MASK);
    (data->num4segments & (1 << 5)) ?
        (LCD_NUM4SEGF_ADDR |= LCD_NUM4SEGF_MASK) : (LCD_NUM4SEGF_ADDR &= ~LCD_NUM4SEGF_MASK);
    (data->num4segments & (1 << 6)) ?
        (LCD_NUM4SEGG_ADDR |= LCD_NUM4SEGG_MASK) : (LCD_NUM4SEGG_ADDR &= ~LCD_NUM4SEGG_MASK);
    (data->num4segments & (1 << 7)) ?
        (LCD_NUM4SEGH_ADDR |= LCD_NUM4SEGH_MASK) : (LCD_NUM4SEGH_ADDR &= ~LCD_NUM4SEGH_MASK);
    (data->num4segments & (1 << 8)) ?
        (LCD_NUM4SEGI_ADDR |= LCD_NUM4SEGI_MASK) : (LCD_NUM4SEGI_ADDR &= ~LCD_NUM4SEGI_MASK);
    (data->num4segments & (1 << 9)) ?
        (LCD_NUM4SEGJ_ADDR |= LCD_NUM4SEGJ_MASK) : (LCD_NUM4SEGJ_ADDR &= ~LCD_NUM4SEGJ_MASK);

    (data->bargraph & ((uint32_t)1 << 0)) ?
        (LCD_BARGRAPH1_ADDR |= LCD_BARGRAPH1_MASK) : (LCD_BARGRAPH1_ADDR &= ~LCD_BARGRAPH1_MASK);
    (data->bargraph & ((uint32_t)1 << 1)) ?
        (LCD_BARGRAPH2_ADDR |= LCD_BARGRAPH2_MASK) : (LCD_BARGRAPH2_ADDR &= ~LCD_BARGRAPH2_MASK);
    (data->bargraph & ((uint32_t)1 << 2)) ?
        (LCD_BARGRAPH3_ADDR |= LCD_BARGRAPH3_MASK) : (LCD_BARGRAPH3_ADDR &= ~LCD_BARGRAPH3_MASK);
    (data->bargraph & ((uint32_t)1 << 3)) ?
        (LCD_BARGRAPH4_ADDR |= LCD_BARGRAPH4_MASK) : (LCD_BARGRAPH4_ADDR &= ~LCD_BARGRAPH4_MASK);
    (data->bargraph & ((uint32_t)1 << 4)) ?
        (LCD_BARGRAPH5_ADDR |= LCD_BARGRAPH5_MASK) : (LCD_BARGRAPH5_ADDR &= ~LCD_BARGRAPH5_MASK);
    (data->bargraph & ((uint32_t)1 << 5)) ?
        (LCD_BARGRAPH6_ADDR |= LCD_BARGRAPH6_MASK) : (LCD_BARGRAPH6_ADDR &= ~LCD_BARGRAPH6_MASK);
    (data->bargraph & ((uint32_t)1 << 6)) ?
        (LCD_BARGRAPH7_ADDR |= LCD_BARGRAPH7_MASK) : (LCD_BARGRAPH7_ADDR &= ~LCD_BARGRAPH7_MASK);
    (data->bargraph & ((uint32_t)1 << 7)) ?
        (LCD_BARGRAPH8_ADDR |= LCD_BARGRAPH8_MASK) : (LCD_BARGRAPH8_ADDR &= ~LCD_BARGRAPH8_MASK);
    (data->bargraph & ((uint32_t)1 << 8)) ?
        (LCD_BARGRAPH9_ADDR |= LCD_BARGRAPH9_MASK) : (LCD_BARGRAPH9_ADDR &= ~LCD_BARGRAPH9_MASK);
    (data->bargraph & ((uint32_t)1 << 9)) ?
        (LCD_BARGRAPH10_ADDR |= LCD_BARGRAPH10_MASK) : (LCD_BARGRAPH10_ADDR &= ~LCD_BARGRAPH10_MASK);
    (data->bargraph & ((uint32_t)1 << 10)) ?
        (LCD_BARGRAPH11_ADDR |= LCD_BARGRAPH11_MASK) : (LCD_BARGRAPH11_ADDR &= ~LCD_BARGRAPH11_MASK);
    (data->bargraph & ((uint32_t)1 << 11)) ?
        (LCD_BARGRAPH12_ADDR |= LCD_BARGRAPH12_MASK) : (LCD_BARGRAPH12_ADDR &= ~LCD_BARGRAPH12_MASK);
    (data->bargraph & ((uint32_t)1 << 12)) ?
        (LCD_BARGRAPH13_ADDR |= LCD_BARGRAPH13_MASK) : (LCD_BARGRAPH13_ADDR &= ~LCD_BARGRAPH13_MASK);
    (data->bargraph & ((uint32_t)1 << 13)) ?
        (LCD_BARGRAPH14_ADDR |= LCD_BARGRAPH14_MASK) : (LCD_BARGRAPH14_ADDR &= ~LCD_BARGRAPH14_MASK);
    (data->bargraph & ((uint32_t)1 << 14)) ?
        (LCD_BARGRAPH15_ADDR |= LCD_BARGRAPH15_MASK) : (LCD_BARGRAPH15_ADDR &= ~LCD_BARGRAPH15_MASK);
    (data->bargraph & ((uint32_t)1 << 15)) ?
        (LCD_BARGRAPH16_ADDR |= LCD_BARGRAPH16_MASK) : (LCD_BARGRAPH16_ADDR &= ~LCD_BARGRAPH16_MASK);
    (data->bargraph & ((uint32_t)1 << 16)) ?
        (LCD_BARGRAPH17_ADDR |= LCD_BARGRAPH17_MASK) : (LCD_BARGRAPH17_ADDR &= ~LCD_BARGRAPH17_MASK);
    (data->bargraph & ((uint32_t)1 << 17)) ?
        (LCD_BARGRAPH18_ADDR |= LCD_BARGRAPH18_MASK) : (LCD_BARGRAPH18_ADDR &= ~LCD_BARGRAPH18_MASK);
    (data->bargraph & ((uint32_t)1 << 18)) ?
        (LCD_BARGRAPH19_ADDR |= LCD_BARGRAPH19_MASK) : (LCD_BARGRAPH19_ADDR &= ~LCD_BARGRAPH19_MASK);
    (data->bargraph & ((uint32_t)1 << 19)) ?
        (LCD_BARGRAPH20_ADDR |= LCD_BARGRAPH20_MASK) : (LCD_BARGRAPH20_ADDR &= ~LCD_BARGRAPH20_MASK);
    (data->bargraph & ((uint32_t)1 << 20)) ?
        (LCD_BARGRAPH21_ADDR |= LCD_BARGRAPH21_MASK) : (LCD_BARGRAPH21_ADDR &= ~LCD_BARGRAPH21_MASK);
    (data->bargraph & ((uint32_t)1 << 21)) ?
        (LCD_BARGRAPH22_ADDR |= LCD_BARGRAPH22_MASK) : (LCD_BARGRAPH22_ADDR &= ~LCD_BARGRAPH22_MASK);
    (data->bargraph & ((uint32_t)1 << 22)) ?
        (LCD_BARGRAPH23_ADDR |= LCD_BARGRAPH23_MASK) : (LCD_BARGRAPH23_ADDR &= ~LCD_BARGRAPH23_MASK);
    (data->bargraph & ((uint32_t)1 << 23)) ?
        (LCD_BARGRAPH24_ADDR |= LCD_BARGRAPH24_MASK) : (LCD_BARGRAPH24_ADDR &= ~LCD_BARGRAPH24_MASK);
}