#ifndef __UART3_H
#define __UART3_H
#define USART3_REC_LEN  			3  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#include "sys.h"
void uart3_init(unsigned long baudrate);
extern volatile u8 USART3_RX_BUF[USART3_REC_LEN];
extern volatile u8 USART3_RX_completed;
#endif

//------------------End of File----------------------------

