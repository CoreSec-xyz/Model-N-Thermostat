#include "STM8L052C6.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UART_BUFFER_SIZE 32

#define MP1 (1 << 2)

#define MOTO_E7 (1 << 7)
#define MOTO_E6 (1 << 6)
#define SEN_C3 (1 << 3)
#define MOTO_C4 (1 << 4)
#define MOTO_C7 (1 << 7)

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

uint16_t count = 0;
uint8_t uartBufferPos = 0;
char uartBuffer[UART_BUFFER_SIZE];
bool motorDir = false;
volatile uint32_t tim2_millis = 0;

uint32_t millis() {
  return tim2_millis;
}

void delay_ms(uint32_t ms) {
    uint32_t start = millis();
    while ((millis() - start) < ms);
}

void initTIM2() {
    // 16000 ticks
    TIM2_ARRH = 0x3E;
    TIM2_ARRL = 0x80;
    //TIM2_PSCR = 0b010;

    TIM2_IER |= 0x1; // Update interrupt
    TIM2_CR1 = 0x1; // enable timer
}

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

void initMotor() {
        // 1. H-Bridge
    PE_DDR |= MOTO_E7 | MOTO_E6;
    PE_CR1 |= MOTO_E7 | MOTO_E6;
    PE_ODR |= MOTO_E7 | MOTO_E6;

        // 2. H-Bridge
    PC_DDR |= MOTO_C4 | MOTO_C7;
    PC_CR1 |= MOTO_C4 | MOTO_C7;
    PC_ODR |= MOTO_C4 | MOTO_C7;

}

void setMotor(bool st1, bool st2) {
    if (st1) {
        PE_ODR &= ~MOTO_E7 & ~MOTO_E6; // 3.3V
    } else {
        PE_ODR |= MOTO_E7 | MOTO_E6; // 0V
    }
    if (st2) {
        PC_ODR &= ~MOTO_C4 & ~MOTO_C7; // 3.3V
    } else {
        PC_ODR |= MOTO_C4 | MOTO_C7; // 0V
    }

}


void initUSART() {
    SYSCFG_RMPCR1 |= 0x10; // TX: PA2, RX: PA3
    PA_DDR |= MP1;
    PA_CR1 |= MP1;

    USART1_CR2 = USART_CR2_TEN | USART_CR2_REN | USART_CR2_RIEN; // Transmit, receive, interrrupt enable
    USART1_CR3 &= ~(USART_CR3_STOP1 | USART_CR3_STOP2); // 1 stop bit
    USART1_BRR1 = 0x11; USART1_BRR2 = 0x6; // 57600 baud (use 8 B for 115200)
}

int uartWrite(const char *str) {
	char i;
	for(i = 0; i < strlen(str); i++) {
		while(!(USART1_SR & USART_SR_TXE));
		USART1_DR = str[i];
	}
	return(i); // Bytes sent
}

int putchar(int data) {
    USART1_DR = data;
    while (!(USART1_SR & USART_SR_TC));
    return 0;
}

char uartRead() {
    if(USART1_SR & USART_SR_RXNE) {
        return USART1_DR;
    } else {
        return '\0';
    }
}

void clearUartBuffer() {
    uartBufferPos = 0;
    memset(uartBuffer,0,UART_BUFFER_SIZE);
}


void initADC() {
    ADC1_SQR1 |= ADC1_SQR1_DMAOFF; // disable DMA
    ADC1_SQR4 |= (1 << 5); // Select ADC 5 (PC3)
    ADC1_CR1 |= ADC1_CR1_ADON; // wake up
    // ADC1_CR1 &= ~ADC1_CR1_ADON; // off
}

uint16_t readADC() {
    uint8_t adcH, adcL;
    ADC1_CR1 |= ADC1_CR1_START; // start
    while (!(ADC1_SR & ADC1_SR_EOC));
    adcH = ADC1_DRH;
    adcL = ADC1_DRL;
    //ADC1_CSR &= ~(1 << ADC1_CSR_EOC); // Clear EOC flag
    return (adcL | (adcH << 8));
}


void initClock() {
    CLK_CKDIVR = 0; // Set the frequency to 16 MHz
    CLK_PCKENR1 = 0xFF; // Enable peripherals
    CLK_PCKENR2 = 0xFF;
}


int main() {
        initClock();

        initTIM2();

        enableInterrupts()

        initADC();

        initUSART();

        initDisplay();

        initMotor();

        struct DisplayData display = {0};
        display.timegrid = 1;
        display.sun = 1;
        display.moon = 1;
        display.window = 1;
        display.vacation = 1;
        display.degrees = 1;
        display.percent = 1;
        display.battery = 1;
        display.automatic = 1;
        display.manual = 1;
        display.colon = 1;
        display.point1 = 1;
        display.point2 = 1;
        display.point3 = 1;
        display.weekdays = 1;
        display.num1segments = 0x3FF;
        display.num2segments = 0x3FF;
        display.num3segments = 0x3FF;
        display.num4segments = 0x3FF;
        display.bargraph = 0x1;
        setDisplay(&display);

        printf("Thermostat: Startup complete\n");

        while(true) {
            uint16_t adc, t;

            delay_ms(1000);

            if(display.bargraph == ((uint32_t)1 << 23))
                display.bargraph = 1;
            else
                display.bargraph = (display.bargraph << 1);

            if(display.weekdays == (1 << 6))
                display.weekdays = 1;
            else
                display.weekdays = (display.weekdays << 1);
            setDisplay(&display);

            if (uartBuffer[0] == 'b') {
              motorDir = false;
              memmove(uartBuffer, uartBuffer+1, strlen(uartBuffer));
              count = atoi(uartBuffer);
            } else if (uartBuffer[0] == 'f') {
              motorDir = true;
              memmove(uartBuffer, uartBuffer+1, strlen(uartBuffer));
              count = atoi(uartBuffer);
            }
            clearUartBuffer();

            adc = readADC();
            t = tim2_millis/100;
            printf("ADC value: %d, Time: %u\n", readADC(), (uint16_t)(millis()/100));

            if (count > 0) {
              printf("Running %s for %d.%d sec\n", (motorDir? "forward" : "backward"), count/10, count%10);
              setMotor(motorDir, !motorDir);
              count--;
            } else {
              setMotor(0, 0);
            }
        }
    }

    #define UART_RECV_ISR 28
    #define TIM2_OVF_ISR 19

    void uart_isr() __interrupt(UART_RECV_ISR) {
        uint8_t i;
        uartBufferPos %= UART_BUFFER_SIZE-1;
        for(i = uartBufferPos; i < UART_BUFFER_SIZE; i++) {
            uartBuffer[i] = uartRead();
        }
        uartBufferPos++;
    }

    void tim2_isr() __interrupt(TIM2_OVF_ISR) {
        TIM2_SR1 = 0;
        tim2_millis++;
    }
