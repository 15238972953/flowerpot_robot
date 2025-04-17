#ifndef STEPPER_H
#define STEPPER_H
#include "sys.h"
#include "delay.h"

#define dir1 PBout(11)
#define step1 PBout(10)
#define dir2 PCout(5)
#define step2 PCout(4)
#define dir3 PDout(11)
#define step3 PDout(10)
#define dir4 PBout(1)
#define step4 PBout(0)

void STEPPER_Init(void);
void TIM2_Init(void);
void Stepper_Arm_Move(u32 step,u8 dir,u8 speed);
void Stepper_Claw_Move(u32 step,u8 dir,u8 speed);

#endif