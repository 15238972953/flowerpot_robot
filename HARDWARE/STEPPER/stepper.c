#include "stepper.h"

//步进电机配置
void STEPPER_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//上拉
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化
	
	TIM2_Init();
}

void TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE );
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE );
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);	
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_Period=2000;
	TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;//2*10^4 / 1*10^6==2*10^-2s==20ms
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up ;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low ;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC3Init(TIM2,&TIM_OCInitStruct);

	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable );

	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
}

//测试步进电机
void Stepper_Move(int speed,int pulse){
	TIM_SetCompare3(TIM2,speed);
	
}

//机械臂步进电机的运动控制
void Stepper_Arm_Move(u32 step,u8 dir,u8 speed){
	if(0==dir){
		dir3=1;
		dir4=0;
	}else{
		dir3=0;
		dir4=1;
	}
	for(int i=0;i<step;++i){
		step3=1;
		step4=1;
		delay_us(speed);
		step3=0;
		step4=0;
		delay_us(speed);
	}
}

//机械爪步进电机的运动控制
void Stepper_Claw_Move(u32 step,u8 dir,u8 speed){
		dir2=dir;	
	for(int i=0;i<step;++i){
		step2=1;
		delay_us(speed);
		step2=0;
		delay_us(speed);
	}
}