#include "motor.h"

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

void initMotor() {

    initADC();

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