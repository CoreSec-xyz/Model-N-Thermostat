#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include "STM8L052C6.h"
#include <stdbool.h>

#define MOTO_E7 (1 << 7)
#define MOTO_E6 (1 << 6)
#define SEN_C3 (1 << 3)
#define MOTO_C4 (1 << 4)
#define MOTO_C7 (1 << 7)

void initADC();
uint16_t readADC();
void initMotor();
void setMotor(bool st1, bool st2);

#endif //MOTOR_H