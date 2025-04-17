#include "ec11.h"

u8 EC11_Num1 = 50;

//EC11_KEY1���º�ִ���¼�
void EC11_KEY1_click_do(){

}
 
//��ʱ��1����
void TIM1_Int_Init(u16 arr, u16 psc)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//TIM2ʱ��ʹ��    
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //ʹ��ָ����TIM7�ж�,��������ж�
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
 
	TIM_Cmd(TIM1, ENABLE);//������ʱ��4
}
 
//��ʱ��1�жϷ������		    
void TIM1_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{
		EC11_Hander1(Encoder_EC11_Scan1());
 
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);  //���TIM4�����жϱ�־    
	}
}
 
//*******************************************************************/
//���ܣ���ʼ��EC11��ת��������ز���
//�βΣ�EC11��ת������������-->>  unsigned char Set_EC11_TYPE  <<--  ��0----һ��λ��Ӧһ���壻1�����0��----����λ��Ӧһ���塣
//���أ���
//��⣺��EC11��ת������������IO����IO��ģʽ���á��Լ�����صı������г�ʼ��
//*******************************************************************/
void EC11_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	//EC11AB���������ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9|GPIO_Pin_11;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//EC11������ʼ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
 
	GPIO_SetBits(GPIOE, GPIO_Pin_9|GPIO_Pin_11);
 
	//�����ϵ�ʱEC11��ťλ�ò�ȷ������һ�ζ�������
	EC11_A1_Last = EC11_A1;
	EC11_B1_Last = EC11_B1;
	
	TIM1_Int_Init(9,8399);	//��ʼ����ʱ��1 1ms�ж�
}
//*******************************************************************/
//���ܣ����ݶ�Ӧ�β�EC11_Valueʵ�ֶ�Ӧ����
//�βΣ�EC11_Value
//���أ���
//��⣺��ת�������Ĺ��ܷ�װ���������Ը����Լ����뷨�����Ӧʵ�ֵĹ���
//*******************************************************************/
void EC11_Hander1(u8 EC11_Value)
{
	if (EC11_Value == 1) //��ת
	{
		//--------��������ת��������--------//
		EC11_Num1++;
	}
	else if (EC11_Value == 2)    //��ת
	{
		//--------��������ת��������--------//
		EC11_Num1--;
	}
	else if (EC11_Value == 3)    //��ѹһ��
	{
		//--------������������ѹһ�δ���--------//
		EC11_KEY1_click_do();
	}	
}
 
//*******************************************************************/
//���ܣ�ɨ��EC11��ת�������Ķ��������������ظ�������������ʹ��
//�βΣ�EC11��ת������������-->>  unsigned char Set_EC11_TYPE  <<--  ��0----һ��λ��Ӧһ���壻1�����0��----����λ��Ӧһ����
//���أ�EC11��ת��������ɨ����-->>  char ScanResult  -->>  0���޶�����1����ת�� -1����ת��2��ֻ���°�����3�����Ű�����ת��-3�����Ű�����ת
//��⣺ֻɨ��EC11��ת��������û�ж������������ǵڼ��ΰ��°����򳤰���˫��������ֱֵ����Ϊ�βδ��� [ void Encoder_EC11_Analyze(char EC11_Value); ] ����ʹ��
//*******************************************************************/
char Encoder_EC11_Scan1(void)
{
	//���´���A��B��һ��ֵ�ı�������Ϊ��̬ȫ�ֱ����������EC11��Ӧ��IO������ʼ��
	//  static char EC11_A_Last = 0;
	//  static char EC11_B_Last = 0;
	char ScanResult = 0;    //���ر�����ɨ���������ڷ����������Ķ���
	
	//����ֵ��ȡֵ��   0���޶�����      1����ת��   2����ת��  
	//                 3��ֻ���°�����  4��˫����   5������
	//======================================================//
              
	if (EC11_A1 != EC11_A1_Last)   //��AΪʱ�ӣ�BΪ���ݡ���תʱAB���࣬��תʱABͬ��
	{
		if (EC11_A1 == 0)
		{
			if (EC11_B1 == 1)      //ֻ��Ҫ�ɼ�A�������ػ��½��ص�����һ��״̬����A�½���ʱBΪ1����ת                    
				 ScanResult = 1;     //��ת
			else                    //��ת
				 ScanResult = 2;
			}
			EC11_A1_Last = EC11_A1;   //���±�������һ��״̬�ݴ����
			EC11_B1_Last = EC11_B1;   //���±�������һ��״̬�ݴ����
	}
	
	//EC11��������
	if(0==EC11_KEY1){
		delay_ms(10);
		if(0==EC11_KEY1 && 1==EC11_KEY1_Last){
		ScanResult = 3;
		EC11_KEY1_Last = 0;
		}
	}
	return ScanResult;
}

