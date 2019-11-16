#include "init.h"	 //��ʼ���⺯��
#include "D1602.h"	 //�Լ�д��1602�Ŀ⺯��

sbit speaker=P1^3;//������

sbit key_next=P3^6;		//��һ��
sbit key_last=P3^5;		//��һ��
sbit key_pause=P3^7;	//��ͣ/����

uchar a,b;
uchar number=0;		//��¼������һ�׸�ı�־λ
uchar pause=0;		//��ͣ/���ű�־λ


uchar code by_title[]="By:------         ";	   
uchar code shengri_title[]="   ShengRiGe     ";    //���ո����
uchar code laohu_title[]="  LiangZhiLaoHu  ";	   //��ֻ�ϻ�����
uchar code yishan_title[]="  XingXingZhiGe  ";     //����������
uchar code hudie_title[]="  LiangZhiHuDie  ";	   //��ֻ��������
uchar code qinghua_title[]="    QingHuaCi     ";   //�໨�ɱ���
uchar code pause_title[]="pause";

uchar code yinfu[]={0xfb,0xe9,      //Do
                   0xfc,0x5c,      //Re
                   0xfc,0xc1,      //Mi
                   0xfc,0xef,      //Fa
                   0xfd,0x45,      //So
                   0xfd,0x92,      //La
                   0xfd,0xd0,      //Si
                   0xfd,0xee,      //Do#
				   0x00,0x00,	   //���
};
uchar code shengri_tone[]={1,0,1,2,1,4,3,0, //���տ�������
                           1,0,1,2,1,5,4,0,
                           1,0,1,8,6,4,3,2,0,7,0,7,6,4,5,4,0       //0������������ͣ�٣����ּ�Ϊ����
};
uchar code shengri_beat[]={24,1,24,48,48,48,72,5,//����
                           24,1,24,48,48,48,72,5,
                           24,1,24,48,48,48,48,72,5,24,1,24,48,48,48,72,5    //���ģ���tone�����������ʱ
};
uchar code laohu_tone[]={1,2,3,1,0,1,2,	//��ֻ�ϻ����� 40������
						3,1,0,3,4,5,0,3,4,5,0,5,6,5,4,3,
						1,0,5,6,5,4,3,1,0,3,2,1,0,3,2,1,0
};
uchar code laohu_beat[]={24,24,24,48,5,24,24,//����
						24,48,5,24,24,48,5,24,24,72,5,24,24,24,24,//����
						24,48,5,24,24,24,24,24,72, 5,24,24,48,5,24,24,//����
						72,5//����  //���ģ���tone���������
};
uchar code yishan_tone[]={1,1,5,5,6,6,5,	//��������  54������
						0,4,4,3,3,2,2,1,0,5,5,4,4,3,
						3,2,0,5,5,4,4,3,3,2,0,1,1,5,5,
						6,6,5,0,4,4,3,3,2,2,1,0
}; 
uchar code yishan_beat[]={24,24,24,24,24,24,48,//����
						5,24,24,24,24,24,24,72,5,24,24,24,24,24,24,//����
						48,5,24,24,24,24,24,24,72,5,24,24,24,24,24,24,//����
						48,5,24,24,24,24,24,24,72,5//��ģ��tone���������ʱ
};
uchar code yinlv[][2]={
	{0,1},{1,1},{3,1},{5,1},{6,1},{8,1},{10,1},{12,1},{13,1},//��ʾ�������˶� 123457671
	{0,1},{13,1},{15,1},{17,1},{18,1},{20,1},{22,1},{24,1},{25,1},//��ʾ�����˶�12345671
	{0,1},{25,1},{27,1},{29,1},{30,1},{32,1},{34,1},{36,1},{37,1},//��ʾ�����˶�12345671
	{0,1},{37,1},{39,1},{41,1},{42,1},{44,1},{46,1},{48,2},//��ʾ�����˶� 1234567
}; 
//�໨��
uchar code qing_tone[49][2]={{0,0},//��������49����ά����
{0xF9,0x1F},{0xF9,0x82},{0xF9,0xDF},{0xFA,0x37},{0xFA,0x8A},{0xFA,0xD8},{0xFB,0x23},{0xFB,0x68},{0xFB,0xAA},{0xFB,0xE9},{0xFC,0x24},{0xFC,0x5B},
{0xFC,0x8F},{0xFC,0xC1},{0xFC,0xEF},{0xFD,0x1B},{0xFD,0x45},{0xFD,0x6C},{0xFD,0x91},{0xFD,0xB4},{0xFD,0xD5},{0xFD,0xF4},{0xFE,0x12},{0xFE,0x2D},
{0xFE,0x48},{0xFE,0x60},{0xFE,0x78},{0xFE,0x86},{0xFE,0xA3},{0xFE,0xB6},{0xFE,0xC9},{0xFE,0xDA},{0xFF,0xEB},{0xFE,0xFA},{0xFF,0x09},{0xFF,0x17},
{0xFF,0x24},{0xFF,0x30},{0xFF,0x3C},{0xFF,0x47},{0xFF,0x51},{0xFF,0x5B},{0xFF,0x64},{0xFF,0x6D},{0xFF,0x75},{0xFF,0x7D},{0xFF,0x84},{0xFF,0x8B}
};
uchar code qing_beat[][2]={//�����������飬ǰ��Ϊ���ɣ�����Ϊ�������� ��Ҫ����ı���׶�Ӧ�����ɺż���
{24,4},{24,4},{21,4},{19,4},{21,4},{14,8},{19,4},{21,4},{24,4},{21,4},{19,16},//��¼�ջ�̨���׸�ʣ�0553236 23532 ����ɫ������ �����ڵ���
{24,4},{24,4},{21,4},{19,4},{21,4},{12,8},{19,4},{21,4},{24,4},{19,4},{17,16},//���׸�ʣ�0553235 23521 ������������ ����ǧ����
{17,4},{19,4},{21,4},{24,4},{26,4},{24,4},{22,4},{24,4},{21,4},{21,4},{19,4},{19,16},//���׸�ʣ�01235654 53322 ��ƽ������㷿���ϵ�ƮӰ
{17,4},{19,4},{17,4},{17,4},{19,4},{17,4},{19,4},{19,4},{21,8},{24,4},{21,4},{21,12},//���׸�ʣ��͵���Ϊ���������
{24,4},{24,4},{21,4},{19,4},{21,4},{14,8},{19,4},{21,4},{24,4},{21,4},{19,16}, //���׸�ʣ�0553236 23532 ����ɫ������ �����ڵ���
{24,4},{24,4},{21,4},{19,4},{21,4},{12,8},{19,4},{21,4},{24,4},{19,4},{17,16}, //���׸�ʣ�0553235 23521 ��ɫ�������� �ڸ��˽��
{17,4},{19,4},{21,4},{24,4},{26,4},{24,4},{22,4},{24,4},{21,4},{21,4},{19,4},{19,12},//���׸�ʣ�0123 5654 5332 25 322 11 �紫�����໨���ڶ�������
{12,4},{21,8},{19,8},{19,4},{17,20}, //���׸�ʣ����۴�Ц��
{0xFF,0xFF}}; //������β��ʶ
//��ֻ����
uchar code hudie_tone[49][2]={{0,0},
	{0xF8,0x8B},{0xF8,0xF2},{0xF9,0x5B},{0xF9,0xB7},{0xFA,0x14},
	{0xFA,0x66},{0xFA,0xB9},{0xFB,0x03},{0xFB,0x4A},{0xFB,0x8F},
	{0xFB,0xCF},{0xFC,0x0B},{0xFC,0x43},{0xFC,0x78},{0xFC,0xAB},
	{0xFC,0xDB},{0xFD,0x08},{0xFD,0x33},{0xFD,0x5B},{0xFD,0x81},
	{0xFD,0xA5},{0xFD,0xC7},{0xFD,0xE7},{0xFE,0x05},{0xFE,0x21},
	{0xFE,0x3C},{0xFE,0x55},{0xFE,0x6D},{0xFE,0x84},{0xFE,0x99},
	{0xFE,0xAD},{0xFE,0xC0},{0xFE,0x02},{0xFE,0xE3},{0xFE,0xF3},
	{0xFF,0x02},{0xFF,0x10},{0xFF,0x1D},{0xFF,0x2A},{0xFF,0x36},
	{0xFF,0x42},{0xFF,0x4C},{0xFF,0x56},{0xFF,0x60},{0xFF,0x69},
	{0xFF,0x71},{0xFF,0x79},{0xFF,0x81}
	};
uchar code hudie_beat[][2]={{0,4},
	{23,4},{21,4},{23,16},{23,4},{21,4},{23,4},{21,4},{19,16},{16,4},
	{19,4},{21,8},{21,4},{23,4},{21,4},{19,4},{16,4},{19,4},{14,24},
	{23,4},{21,4},{23,16},{23,4},{21,4},{23,4},{21,4},{19,24},{16,4},
	{19,4},{21,8},{21,4},{23,4},{21,4},{19,4},{16,4},{19,4},{21,24},
	{23,4},{21,4},{23,16},{23,4},{21,4},{23,4},{21,4},{19,16},{16,4},
	{19,4},{21,8},{21,4},{23,4},{21,4},{19,4},{16,4},{19,4},{14,24},
	{23,4},{26,4},{26,16},{26,4},{28,4},{26,4},{23,24},{21,4},{23,4},
	{21,8},{21,4},{23,4},{21,4},{19,4},{16,4},{16,2},{19,2},{19,24},{0,20},
	{26,4},{26,4},{28,4},{31,4},{30,4},{30,4},{28,4},{23,4},{21,4},{21,4},
	{23,16},{23,4},{23,4},{26,4},{28,8},{28,12},{16,4},{23,4},{21,4},
	{21,24},{23,4},{26,4},{26,4},{23,4},{26,8},{31,8},{30,4},{28,4},
	{30,4},{23,8},{28,4},{28,4},{30,4},{28,4},{26,4},{23,4},{21,8},
	{23,4},{21,4},{23,4},{26,16},
	{0xFF,0xFF}};
//��������
void play(void);   //���ֲ��ſ��ƺ���
void key();		   //�жϰ�������
void stop();	   //��ͣ/���ź���
void display();	   //Һ����ʾ����
void delay(uchar p); //������ʱ����
void pause1();		 //������ʾ����

void main(){
	TMOD=0x01;
	TH0=a;
	TL0=b;
	ET0=1;//�򿪶�ʱ��������δ�����ж�
	TR0=1;

	number = 4;		  //���Ȳ����໨��
	init();
	while(1){
		play();
	}
}

void key(){
	if(key_next==0){
		number++;
		if(number>6){
			number=1;	  //���number>6����ʾ���һ�׸裬���ص�һ�׸貥��
		}
		while(!key_next);	
	}
	if(key_last==0){	  
		number--;
		if(number<1){	  //���number<1����ʾ��һ�׸裬�������һ�׸貥��
			number=6;
		}
		while(!key_last);
	}
	if(key_pause==0){	   //��ͣ������
		if(pause==1){
			pause=0;
		}else{
			pause=1;
		}
		while(!key_pause);
	}
}

void stop(){
	uchar i;
	key();
	if(pause==1){ 
		speaker=0;
		EA=0;				//��ͬ�ǶϿ���ʱ���ж�
		while(1){
			key();
			xzl(0x8b);		 
			for(i=0;i<5;i++){
				xsj(pause_title[i]);	  //��ͣʱ����ʾpause
			}
			if(pause==0){
				EA=1;
				xzl(0x8b);
				for(i=0;i<5;i++){
					xsj(' ');xsj(' ');xsj(' ');xsj(' ');xsj(' ');
				}
				break;
			}
		}
	}
}

void play(void){
	uchar m=0;
	char s;
	uchar flag=1;     
	uchar c=1;
	if(number==1){
		display();				 //��ʾ����
		while(flag){ 
			EA=0;
			c=shengri_tone[m];                       //ȡ����
			s=shengri_beat[m];                      //ȡ����
			a=yinfu[2*c-2];                            
			b=yinfu[2*c-1];                            
			EA=1;
			while(s--){
				delay1();
				stop();
				if(number!=1){
					s=0;
					flag=0;
					break;
				}	
			}
			P2=b;
			m++;
			if(m>=33){
				number=2;
				flag=0;
			} 
		} 
	}else if(number==2){
		display();
		while(flag){
			EA=0;
			c=laohu_tone[m];                            //ȡ����
			s=laohu_beat[m];                      //ȡ����
			a=yinfu[2*c-2];                            
			b=yinfu[2*c-1];                            
			EA=1;
			while(s--){
			     delay1();
				 stop();
				 if(number!=2){
					s=0;
					flag=0;
					break;
				}
			}
			P2=b;
			m++;
			if(m>=40){
				number=3;
				flag=0;
			}                  
		} 
	}else if(number==3){
		display();
		while(flag){
			EA=0;
			c=yishan_tone[m];                            //ȡ����
			s=yishan_beat[m];                      //ȡ����
			a=yinfu[2*c-2];                            
			b=yinfu[2*c-1];                            
			EA=1;
			while(s--){
				delay1();
				stop();
				if(number!=3){
					s=0;
					flag=0;
					break;
				}
			}
			P2=b;
			m++;
			if(m>=48){
				number=4;
				flag=0;
			}                      
		} 
	}else if(number==4){		//���������׸���ǰ��Ĳ��ŷ�ʽһ������Ϊ�����������Ѽ����ϵ�
		display();
		while(flag){
			EA=0;
			c=qing_beat[m][0];                            //ȡ����
			s=qing_beat[m][1];                      //ȡ����
			a=qing_tone[c][0];                            
			b=qing_tone[c][1];                            
			EA=1;
			if(number!=4){
				c=0;
				s=0;
				flag=0;
				break;
			}
           	if(c==0xFF){
				number=5;
				flag=0;
				break;
			} 
           	else if(c==qing_beat[m+1][0]){
				TR0=1;
				delay(s);
				TR0=0;
				pause1();
				m++;
			}
           	else{
				TR0=1;
				delay(s);
				m++;
			}
			P2=b;                      
		} 
	}else if(number==5){
		display();
		while(flag){
			EA=0;
			c=hudie_beat[m][0];                            //ȡ����
			s=hudie_beat[m][1];                      //ȡ����
			a=hudie_tone[c][0];                            
			b=hudie_tone[c][1];                            
			EA=1;
			if(number!=5){
				s=0;
				flag=0;
				break;
			}
           	if(c==0xFF){
				number=6;
				flag=0;
				break;
			} 
           	else if(c==hudie_beat[m+1][0]){
				TR0=1;
				delay(s);
				TR0=0;
				pause1();
				m++;
			}
           	else{
				TR0=1;
				delay(s);
				m++;
			}
			P2=b;                      
		} 
	}else if(number==6){				   //���ŵ���������������
		display();
		while(flag){
			EA=0;
			c=yinlv[m][0];                            //ȡ����
			s=yinlv[m][1];                      //ȡ����
			a=qing_tone[c][0];                            
			b=qing_tone[c][1];                            
			EA=1;
			
			TR0=1;
			delay(s);
			m++;
			if(number!=6){
				s=0;
				flag=0;
				break;
			}	
			if(m>=36){
				number=1;
				flag=0;
			} 
			P2=b;                      
		} 
	}
}
 //��ʱ���ж�
void time0() interrupt 1{
	TH0=a;
	TL0=b;
	speaker=~speaker;
}
 //��ʾ����
void display(){
     uchar i;
	 xzl(0x80);		 
	 for(i=0;i<16;i++){
	   xsj(by_title[i]);
     }
	 xzl(0x8a);
	 xzl(0x80+0x40);
	 for(i=0;i<16;i++){	                
		switch(number){
			case 1:xsj(shengri_title[i]);break;
			case 2:xsj(laohu_title[i]);break;
			case 3:xsj(yishan_title[i]);break;
			case 4:xsj(qinghua_title[i]);break;
			case 5:xsj(hudie_title[i]);break;
		}
	 }
}

void delay(uchar p){
    uchar i,j; 
    for(;p>0;p--)
	    for(i=180;i>0;i--)
		    for(j=15;j>0;j--){
				stop();
			}
}
void pause1(){
    uchar i,j;
    for(i=150;i>0;i--)
    	for(j=10;j>0;j--){
			stop();
		}
}
