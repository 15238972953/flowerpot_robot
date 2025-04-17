#ifndef Key_H
#define Key_H
#include "sys.h"

extern u8 key_value;

#define KEY1 		PEin(8)   	
#define KEY2 		PEin(12)		
#define KEY3		PEin(13)		
#define KEY4	  PEin(14)	
#define KEY5 		PEin(15)   	


void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
