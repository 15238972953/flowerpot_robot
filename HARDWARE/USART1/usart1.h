#ifndef __USART1_H
#define __USART1_H

#include "sys.h"
#include "delay.h"
#include "24l01.h"

#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

extern u8 res;

void USART1_Init(unsigned long baudrate);

#endif

