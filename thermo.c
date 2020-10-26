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

//00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 00000000
void setDisplay(uint8_t *ram_bytes) {
    /* Test show element */
    LCD_RAM0 = 0b11111111;
    LCD_RAM1 = 0b11111111;
    LCD_RAM2 = 0b01111011;
    LCD_RAM3 = 0b11100000;
    LCD_RAM4 = 0b11111111;
    LCD_RAM5 = 0b10111111;
    LCD_RAM6 = 0b00000111;
    LCD_RAM7 = 0b11111110;
    LCD_RAM8 = 0b11111111;
    LCD_RAM9 = 0b01111011;
    LCD_RAM10 = 0b11100000;
    LCD_RAM11 = 0b11111111;
    LCD_RAM12 = 0b10111111;
    LCD_RAM13 = 0b00000111;
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

        int x = 1;
        setDisplay(&x);

        printf("Thermostat: Startup complete\n");

        while(true) {
            uint16_t adc, t;

            delay_ms(1000);

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
