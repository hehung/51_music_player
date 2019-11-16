#include "init.h"

void delay1(void){
	uchar n=15;
	while(n--){
		uchar i;
		for(i=0;i<125;i++);
	}
}

void delay_ms(uint ms){
     uchar pp=110;
	 for(;ms>0;ms--)
	    for(;pp>0;pp--);
}

void delay_us(uint us){
     for(;us>0;us--);
}

