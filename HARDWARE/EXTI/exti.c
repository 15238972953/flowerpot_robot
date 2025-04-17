#include "exti.h"
#include "delay.h" 
#include "key.h"

//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4,PA0Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8);//PE2 ���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource12);//PE3 ���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource13);//PE4 ���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource14);//PA0 ���ӵ��ж���0
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource15);
	
  /* ����EXTI_Line8 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line8|EXTI_Line12|EXTI_Line13|EXTI_Line14|EXTI_Line15;//LINE8
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn|EXTI15_10_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
}

//�ⲿ�ж�9_5�������
void EXTI9_5_IRQHandler(void)
{
	delay_ms(10);	//����
	if (EXTI_GetITStatus(EXTI_Line8) != RESET){
		if(0==KEY1){
			key_value=1;
		}
	 EXTI_ClearITPendingBit(EXTI_Line8); //���LINE0�ϵ��жϱ�־λ 
	}
}	

//�ⲿ�ж�15_10�������
void EXTI15_10_IRQHandler(void)
{
	delay_ms(10);	//����
	if (EXTI_GetITStatus(EXTI_Line12) != RESET){
		if(0==KEY2){
			key_value=2;
		}	 
	 EXTI_ClearITPendingBit(EXTI_Line12);//���LINE2�ϵ��жϱ�־λ 
	}else if(EXTI_GetITStatus(EXTI_Line13) != RESET){
		if(0==KEY3){
			key_value=3;
		}	 
		EXTI_ClearITPendingBit(EXTI_Line13);//���LINE2�ϵ��жϱ�־λ 
	}else if(EXTI_GetITStatus(EXTI_Line14) != RESET){
		if(0==KEY4){
			key_value=4;
		}	 
		EXTI_ClearITPendingBit(EXTI_Line14);//���LINE2�ϵ��жϱ�־λ 
	}else if(EXTI_GetITStatus(EXTI_Line15) != RESET){
		if(0==KEY5){
			key_value=5;
		}	 
		EXTI_ClearITPendingBit(EXTI_Line15);//���LINE2�ϵ��жϱ�־λ 
	}
}














