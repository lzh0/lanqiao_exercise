/*---------------------------------------
文件名：nixietube.c

版本信息：v2020.7.3 21:26 release

版本号：v2

当前版本功能：整数、小数和负数的数码管8位显示

当前版本问题：

下一新版本功能：

-----------------------------------------*/


#include <nixietube.h>
#include <STC15F2K60S2.h>

sbit P2_5=P2^5;
sbit P2_6=P2^6;
sbit P2_7=P2^7;

void delay_ms(unsigned int t)		//@11.0592MHz
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

/*
unsigned long e(unsigned char n){	//用于求10的N次方函数，目前最高8次方
	switch(n){
		case 0: return 1 ;
		case 1: return 10 ;
		case 2: return 100 ;
		case 3: return 1000 ;
		case 4: return 10000 ;
		case 5: return 100000 ;
		case 6: return 1000000 ;
		case 7: return 10000000 ;
		case 8: return 100000000 ;
	}
	return 0;
}
*/

void display(unsigned char inn,unsigned char bit_){	//位码段码整合后版本
	P2_5=1;//y7
	P2_6=1;
	P2_7=1;
	switch(inn){//位码
		//以下为不带小数点
		case 0:P0=0xc0;break;
		case 1:P0=0xf9;break;
		case 2:P0=0xa4;break;
		case 3:P0=0xb0;break;
		case 4:P0=0x99;break;
		case 5:P0=0x92;break;
		case 6:P0=0x82;break;
		case 7:P0=0xf8;break;
		case 8:P0=0x80;break;
		case 9:P0=0x90;break;
		
		//小数点模式
		//如果嫌速度慢可以把带小数点显示单独拿出来写个函数。此处待优化。
		case 10:P0=0x40;break;
		case 11:P0=0x79;break;
		case 12:P0=0x24;break;
		case 13:P0=0x30;break;
		case 14:P0=0x19;break;
		case 15:P0=0x12;break;
		case 16:P0=0x02;break;
		case 17:P0=0x78;break;
		case 18:P0=0x00;break;
		case 19:P0=0x10;break;
		
		case 20:P0=0xbf;break;	//负数符号显示
		
		default:P0=0xff;break;	//默认全灭
		
	}
	P2_5=0;	//y6
	P2_6=1;
	P2_7=1;
	switch(bit_){//段码
		case 8:P0=0x01;break;
		case 7:P0=0x02;break;
		case 6:P0=0x04;break;
		case 5:P0=0x08;break;
		case 4:P0=0x10;break;
		case 3:P0=0x20;break;
		case 2:P0=0x40;break;
		case 1:P0=0x80;break;
		default:P0=0;break;
	}
	delay_ms(1);
}

void all_digital_tube_display(double number){
	//1.确定整数位数，并将至从最左侧数码管8开始显示，最后一位启用小数点。
	long   int_part=(long)number;
	double dec_part=number-int_part;
	
	char i=0,bits=8;	//获取整数上每位的数字及整数位数
	char int_part_array[8]={0};	//用于每位暂存//添加全元素置零={0}解决了显示小于1的小数时出现的个位0显示为除数错误的问题

	
	
	if (number<0){	//负数处理
		display(20,bits--);
		number = -(number);
		int_part = -(int_part);
		dec_part = -(dec_part);
    }
	
	
	
	
	//小数及整数部分显示
	while(int_part>0){	
		int_part_array[i++]=(int_part%10);	//从低位到高位获取
		int_part=int_part/10;
	}	//注意结束时i为实际整数部分长度+1，因为从0开始计数。
	
	
	//打印整数部分，注意最后一位加上小数点。
	while(i>1){	//只打印到小数点前一位，最后一位带小数点特殊处理
		display(int_part_array[--i],bits--);	//在第8位上打印整数最高位
		
	}
	
	if (i == 0) {i++;}//数字0的显示补丁，防止显示0时访问超出数组下界
	
	display((int_part_array[--i])+10,bits--);	//打印最后一位整数，带小数点，并让bits所指向下一个空位
	
	//2.剩下8-整数位数，的地方全用来打印小数点后数字
	while(bits>0){
		display((char)(dec_part=dec_part*10),bits--);
		dec_part=dec_part-(char)dec_part;
		
	}
}
	


//旧版显示方法（不含小数）
/*
void all_digital_tube_display_v0(unsigned long number){
	display( (number/10000000),8);
	display(((number%10000000)/1000000),7);
	display(((number%1000000)/100000),6);
	display(((number%100000)/10000),5);
	display(((number%10000)/1000),4);
	display(((number%1000)/100),3);
	display(((number%100)/10),2);
	display( (number%10),1);
}*/


