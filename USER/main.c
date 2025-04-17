#include "main.h"

u16 MAX_Motor_Speed=0;
int Motor_Speed_Left=0; //左
int Motor_Speed_Right=0; //右
int RemoteControl_KeyValue=0;  //

int main(void)																																																																																																																																																																																																
{
	//初始化
	
	delay_init(168);		   //初始化延时函数
	LED_Init();				    //初始化LED端口
	BEEP_Init();
	OLED_Init();
	EC11_Init();
	STEPPER_Init();
	MOTOR_Init();
	NRF24L01_Init();
	USART1_Init(9600);
	POWER_Init();
	TIM6_init(100-1,8400-1); //0.001s定时中断
	TIM7_init(100-1,8400-1); //0.001s定时中断
	
//	Stepper_Claw_Move(55000,1,5);//0为闭合，1为张开
//	Stepper_Arm_Move(350000,0,5); //0为下去  脉冲350000
//	Stepper_Claw_Move(55000,0,5);//0为闭合，1为张开
//	Stepper_Arm_Move(350000,1,5); //0为下去  脉冲350000
//	while(1){
		
		
//		u8 kk=KEY_Scan(0);
//		
//		if(1==kk){
//			Stepper_Arm_Move(390000,1,5); //1为上来
//		//Stepper_Claw_Move(55000,0,5);//闭合
//		}else if(2==kk){
//			Stepper_Arm_Move(390000,0,5); //0为下去
//			//Stepper_Claw_Move(55000,0,5);//闭合
//		}else{}
//			if(last_kk!=kk){
//				OLED_ShowNum(80,50,kk,1,8,1);
//				OLED_Refresh();
//				delay_ms(15);
//			}
//			last_kk=kk;
//	}
//	while(1){}
//	
//	while(1)
//	{
//			dir3=1;
//			dir4=0;
//		for(int i=0; i < 1000; i++)             	// 输出3200个脉冲信号
//		{
//			step3=1;
//			step4=1;
//			delay_us(1);
//			step3=0;
//			step4=0;
//			delay_us(1);
//		}
//	}
//	
	//主程序
//		Stepper_Claw_Move(55000,1,5);//0为闭合，1为张开
//	Stepper_Arm_Move(350000,0,5); //0为下去  脉冲350000
//	Stepper_Claw_Move(55000,0,5);//0为闭合，1为张开
//	Stepper_Arm_Move(350000,1,5); //0为下去  脉冲350000
	while(1){
		if(NRF24L01_RxPacket(tmp_buf)==0){
			MAX_Motor_Speed = 4*tmp_buf[1];
			Motor_Speed_Left=4*(tmp_buf[2]+tmp_buf[3]-256);
			Motor_Speed_Right=4*(tmp_buf[2]-tmp_buf[3]);
			Motor_Move(Motor_Speed_Left,Motor_Speed_Right);
			RemoteControl_KeyValue=tmp_buf[6];
			switch(RemoteControl_KeyValue){
				case 1:
					Stepper_Claw_Move(55000,1,5);//0为闭合，1为张开
					break;
				case 2:
					Stepper_Arm_Move(350000,0,5); //0为下去  脉冲350000
					break;
				case 3:
					Stepper_Claw_Move(55000,0,5);//0为闭合，1为张开
					break;
				case 4:
					Stepper_Arm_Move(350000,1,5); //0为下去  脉冲350000
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				case 8:
					break;
				case 9:
					break;
				case 10:
					break;
				case 11:
					break;
				case 12:
					break;
			}
			
		}
	}
	return 0;
}		
