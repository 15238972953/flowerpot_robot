#include "main.h"

u16 MAX_Motor_Speed=0;
int Motor_Speed_Left=0; //��
int Motor_Speed_Right=0; //��
int RemoteControl_KeyValue=0;  //

int main(void)																																																																																																																																																																																																
{
	//��ʼ��
	
	delay_init(168);		   //��ʼ����ʱ����
	LED_Init();				    //��ʼ��LED�˿�
	BEEP_Init();
	OLED_Init();
	EC11_Init();
	STEPPER_Init();
	MOTOR_Init();
	NRF24L01_Init();
	USART1_Init(9600);
	POWER_Init();
	TIM6_init(100-1,8400-1); //0.001s��ʱ�ж�
	TIM7_init(100-1,8400-1); //0.001s��ʱ�ж�
	
//	Stepper_Claw_Move(55000,1,5);//0Ϊ�պϣ�1Ϊ�ſ�
//	Stepper_Arm_Move(350000,0,5); //0Ϊ��ȥ  ����350000
//	Stepper_Claw_Move(55000,0,5);//0Ϊ�պϣ�1Ϊ�ſ�
//	Stepper_Arm_Move(350000,1,5); //0Ϊ��ȥ  ����350000
//	while(1){
		
		
//		u8 kk=KEY_Scan(0);
//		
//		if(1==kk){
//			Stepper_Arm_Move(390000,1,5); //1Ϊ����
//		//Stepper_Claw_Move(55000,0,5);//�պ�
//		}else if(2==kk){
//			Stepper_Arm_Move(390000,0,5); //0Ϊ��ȥ
//			//Stepper_Claw_Move(55000,0,5);//�պ�
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
//		for(int i=0; i < 1000; i++)             	// ���3200�������ź�
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
	//������
//		Stepper_Claw_Move(55000,1,5);//0Ϊ�պϣ�1Ϊ�ſ�
//	Stepper_Arm_Move(350000,0,5); //0Ϊ��ȥ  ����350000
//	Stepper_Claw_Move(55000,0,5);//0Ϊ�պϣ�1Ϊ�ſ�
//	Stepper_Arm_Move(350000,1,5); //0Ϊ��ȥ  ����350000
	while(1){
		if(NRF24L01_RxPacket(tmp_buf)==0){
			MAX_Motor_Speed = 4*tmp_buf[1];
			Motor_Speed_Left=4*(tmp_buf[2]+tmp_buf[3]-256);
			Motor_Speed_Right=4*(tmp_buf[2]-tmp_buf[3]);
			Motor_Move(Motor_Speed_Left,Motor_Speed_Right);
			RemoteControl_KeyValue=tmp_buf[6];
			switch(RemoteControl_KeyValue){
				case 1:
					Stepper_Claw_Move(55000,1,5);//0Ϊ�պϣ�1Ϊ�ſ�
					break;
				case 2:
					Stepper_Arm_Move(350000,0,5); //0Ϊ��ȥ  ����350000
					break;
				case 3:
					Stepper_Claw_Move(55000,0,5);//0Ϊ�պϣ�1Ϊ�ſ�
					break;
				case 4:
					Stepper_Arm_Move(350000,1,5); //0Ϊ��ȥ  ����350000
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
