//����ñJ5��1��2������4*4�������,P30~P33Ϊ����P34,P35,P42,P44Ϊ��������
//P36,P37δ�����κ�Ԫ�������������ţ����������

#include <STC15F2K60S2.h>
#include <matrixkeyboard.h>


sbit p30=P3^0;
sbit p31=P3^1;
sbit p32=P3^2;
sbit p33=P3^3;

sbit p34=P3^4;
sbit p35=P3^5;
sbit p42=P4^2;
sbit p44=P4^4;

char check_press(void){ //���ذ�����S4~19������
	unsigned char x_num=0,y_num=0;
	
	x_control(1);
	y_control(0);
	if(check_x_state()!=1111){
		delay__ms(10);	//����
		if(check_x_state()!=1111){
			switch(check_x_state()){
				case 1110:x_num=0;break;
				case 1101:x_num=1;break;
				case 1011:x_num=2;break;
				case 111:x_num=3;break;
				default: break;
			}
			
	x_control(0);
	y_control(1);
			switch(check_y_state()){
				case 1110:y_num=4;break;
				case 1101:y_num=8;break;
				case 1011:y_num=12;break;
				case 111:y_num=16;break;
				default: break;
			}
			return (x_num+y_num);
		}
		return 0;
	}
	return 0;
}




void x_control(char state){	//�������stateֻ��0��1����
	p30=state;
	p31=state;
	p32=state;
	p33=state;
}

void y_control(char state){	//�������stateֻ��0��1����
	p34=state;
	p35=state;
	p42=state;
	p44=state;
}

int check_x_state(void){
	return ((char)p30*1000+(char)p31*100+(char)p32*10+(char)p33);
}

int check_y_state(void){
	return ((char)p34*1000+(char)p35*100+(char)p42*10+(char)p44);
}



void delay__ms(unsigned int t)		//@11.0592MHz
{	
	unsigned int z;
	unsigned char i, j;
	for(z=0;z<t;z++){
		i = 15;
		j = 90;
		do
		{
			while (--j);
		} while (--i);	
	}
}