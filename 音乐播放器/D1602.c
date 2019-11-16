#include "D1602.H"
#include "init.h"

sbit rw=P1^1;
sbit rs=P1^0;
sbit e=P1^2;

void xzl(uchar com){
     rw=0;
	 rs=0;
	 e=0;
	 P0=com; 
	 delay_ms(1);
     e=1;
	 delay_ms(2);
	 e=0;	 
}

void xsj(uchar dat){
     rw=0;
	 rs=1;
	 e=0;
	 P0=dat; 
	 delay_ms(1);
     e=1;
	 delay_ms(2); 
	 e=0;
}

void init(){
   	 delay_ms(1);
	 xzl(0x38);
	 delay_ms(1);
	 xzl(0x38);
	 delay_ms(1);
	 xzl(0x0f);
	 delay_ms(1);
	 xzl(0x08);
	 delay_ms(1);
	 xzl(0x01);
	 delay_ms(12);
	 xzl(0x06);
	 delay_us(50);
	 xzl(0x0c);
	 delay_us(50);
}

