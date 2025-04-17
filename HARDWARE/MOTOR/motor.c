#include "motor.h"

void MOTOR_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_2| GPIO_Pin_4|GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	TIM9_PWM_AB_Init();
}

void TIM9_PWM_AB_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9 ,ENABLE);  	    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;           
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        
	GPIO_Init(GPIOE,&GPIO_InitStructure);              
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource6,GPIO_AF_TIM9);	
	TIM_TimeBaseStructure.TIM_Prescaler=84-1; 
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseStructure.TIM_Period=1000;   
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);
	
	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
	TIM_OC1Init(TIM9, &TIM_OCInitStructure); 
	TIM_OC2Init(TIM9, &TIM_OCInitStructure); 
	
	TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);  
  TIM_ARRPreloadConfig(TIM9,ENABLE);
	TIM_Cmd(TIM9, ENABLE);
}

//限幅函数
//data:需要被限幅的变量
//limit：限制的范围
int value_limit(int data,int limit){
	if(data>limit){
		return limit;
	}else if(data<-limit){
		return -limit;
	}else{
		return data;
	}
}

void Motor_Move(int PWMA,int PWMB){
	if(value_limit(PWMA,1000)>0){	
		AIN1=1;AIN2=0;TIM_SetCompare1(TIM9,PWMA);
	}
	else{
		AIN1=0;AIN2=1;TIM_SetCompare1(TIM9,-PWMA);
	}
	if(value_limit(PWMB,1000)>=0){
		BIN1=0;BIN2=1;TIM_SetCompare2(TIM9,PWMB);
	}else{
		BIN1=1;BIN2=0;TIM_SetCompare2(TIM9,-PWMB);
	}
}
