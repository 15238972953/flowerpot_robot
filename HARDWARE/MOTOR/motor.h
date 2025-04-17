#ifndef MOTOR_H
#define MOTOR_H

#include "sys.h"

#define  AIN1 PDout(14)
#define  AIN2 PDout(4)
#define  BIN1 PDout(2)
#define  BIN2 PDout(0)

void MOTOR_Init(void);
void TIM9_PWM_AB_Init(void);
int value_limit(int data,int limit);
void Motor_Move(int PWMA,int PWMB);

#endif
