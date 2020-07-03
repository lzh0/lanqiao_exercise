/*-----------------------������Ϣ----------------
�ļ�����e2.c

�汾�ţ�v2

�汾��Ϣ��v2020.7.3 20:54 release

��ǰ�汾���ܣ�8λȫ��ʾ���Ӽ��˳�ƽ����������������,С������������ʾ��

��ǰ�汾���⣺1.�����㡢��λ�� 2.//all_digital_tube_display(3.1415926535);//��ʾ�����3.1415927��զ�Զ�����������

��һ�°汾���ܣ�1.�����λ�����㡢С���㡢���Ű��� 2.�����жϡ���matrixkeyboard�������ع���

��ʷ�汾��
v0��������������ʾ�;�����������⣬ʵ�����������ļӼ��˳�ƽ�����������������ʾ��
v1�����ϸ��汾�����ϣ�ʵ����С������ʾ��
v2�����ϸ��汾�����ϣ�ʵ���˸�����ʾ��

�����ֹ����⣺
1.//all_digital_tube_display_v1���ֿ���Ĭ����ʾ8.0000000��������ѽ������ ����ԭ������....
2.С�����ǰһλ������λΪ2������£���ʾ�����ѽ������ ����ԭ��λ�����.
3.��ʾС��1��С��ʱ���ֵĸ�λ0��ʾΪ������������⡾�ѽ������ ����ԭ��char int_part_array[8];δ�ڳ�ʼ��ʱȫԪ�ط�ֵ0����������/����ָ������if (i == 0) {i++;} display((int_part_array[--i])+10,bits--);
4.

�ܽ�/��ѵ/�뷨��
1.��϶Ȼ���̫�ߡ�
2.д����֮ǰ�ȹ���ϵͳ��ܣ�ȷ��ģ�顢��װ���ӿڵ���ƣ��Ҿ�������Ҫ��һЩ������̵��鼮�������Ǵ��ģ���򿪷���صģ���
3.��������ã�����תC��exe��������������Ҳ����ģ���������û��ֱ���ڵ�Ƭ���Ϸ����㡣һ�������ͷ���Ͽ������ơ�
4.���뻹��Խ�淶Խ�ã��������һ���¾��ǣ�����������˵��
5.�汾����̫���ˣ�git���㣬github����ã������������汾����Ա��������ԣ����ˡ�
6.�´εüǰѳ�����󡢽������������ԭ�򶼼�������
7.�ǵý��ù��̺�Ͱѳ�����Ϣ����ˣ���¼�ð汾ʲô�ġ�
8.��ʱ��������ʵ�ڽ�����˵��������ʱ��������תһȦ����Ҳ���ͻȻ��ͨ�ˡ�
-----------------------------------------*/


#include <STC15F2K60S2.h>
#include <nixietube.h>
#include <matrixkeyboard.h>
#include <math.h>	//���ڴ������

unsigned char fun_state;//������������
double keynum,now_display_num,last_display_num; 


void cls_buzz_and_leds(void);
double add(double n1,double n2);
double subtract(double n1,double n2);
double multiply(double n1,double n2);
double divide(double n1,double n2);
double square(double n1);
double square_root(double n1);

/*
//------------------------------------------������----------------------------------------------------------------------
double a=1,l=3;

void main(void){

	
	while(1){
		all_digital_tube_display_v1(divide(a,l));//result:0.66666   ����
		

	}
}
//-----------------------------------------------------------------------------------------------------------------------
*/



void main(void){
	fun_state=0;//��ʼ������
	keynum=0;
	now_display_num=0;
	last_display_num=0;
	cls_buzz_and_leds();

	
	
	//all_digital_tube_display_v1(now_display_num);delay_ms(500);//�ɹ���ʾ0
	
	while(1){
		
		if(check_press()!=0){
			
			keynum=check_press();	//���̷���ֵ����
			delay_ms(100);	//���ڱ��ⰴ�����º�ȡֵ̫�죬ȡ������Ҫ���ظ�ֵ
			
			if(keynum<14){	//���µ������ֲ���
				now_display_num=now_display_num*10+(keynum-4);
			}
			
			else{	//���µ��ǹ��ܲ��ְ�������¼���°����ţ�������������ͬ�Ĺ��ܰ�������ȼ�Ϊ=����(����������)������ֻ��һ���������㣬��ֱ�ӳ����
				if(keynum<18){	//��Ҫ�������ֲ��������
					
					if(fun_state==0){	//���ܰ���֮ǰû�а��µ�״̬����ִ�а��¶�Ӧ���ܵĲ���
						last_display_num=now_display_num;	//��ǰ��ʾ���ֱ���
						now_display_num=0;//��ǰ��ʾ����
						fun_state=keynum;	//���µĹ��ܰ�����¼
						keynum=0;
					}
					
					else{	//�����ܰ���֮ǰִ�й���������ֱ��ִ��=��������
						//all_digital_tube_display_v1(0);	û�ܽ��1/3=3.3333������
						switch(fun_state){
							case 14: now_display_num=add(last_display_num,now_display_num);break;
							case 15: now_display_num=subtract(last_display_num,now_display_num);break;
							case 16: now_display_num=multiply(last_display_num,now_display_num);break;
							case 17: now_display_num=divide(last_display_num,now_display_num);break;
							default:all_digital_tube_display(9999);break;	//������ʾ
						}
					}
					
				}
				
				else{	//ֻ��Ҫһ�����ֵ�����
					if(keynum==18){now_display_num=square(now_display_num);}
					else{now_display_num=square_root(now_display_num);}
				}
				
			}
			
		}
		all_digital_tube_display(now_display_num);
		
	}	//while(1)}
}//main(void)}


void cls_buzz_and_leds(void) //�ص��������Ͱ���leds
{
	P2 = (P2&0x1F|0xA0);	//���û���ʵ�����ã�J3��������ΪIO��ʽ��J5����ΪKBD��J2����Ϊ1-3��2-4
	P0 = 0x00;
	P2 &= 0x1F;
	delay_ms(10);
	P2 = ((P2&0x1f)|0x80);
	P0 = 0xff;  //LED��
	P2 &= 0x1f;
	delay_ms(10);
}

/*
*/

double add(double n1,double n2){	// +
	return (n1+n2);
}

double subtract(double n1,double n2){ // -
	return (n1-n2);
	
}
double multiply(double n1,double n2){	// x
	return (n1*n2);
}
double divide(double n1,double n2){	// /
	return (n1/n2);
}

double square(double n1){	//^2
	return (n1*n1);
}
double square_root(double n1){	//��
	return (double)sqrt(n1);
}






