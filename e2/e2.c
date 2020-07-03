/*-----------------------程序信息----------------
文件名：e2.c

版本号：v2

版本信息：v2020.7.3 20:54 release

当前版本功能：8位全显示，加减乘除平方开根号六种运算,小数、负数的显示。

当前版本问题：1.无清零、退位键 2.//all_digital_tube_display(3.1415926535);//显示结果是3.1415927，咋自动四舍五入了

下一新版本功能：1.添加退位、清零、小数点、负号按键 2.加入中断。【matrixkeyboard库整体重构】

历史版本：
v0【单独成立了显示和矩阵键盘两个库，实现了正整数的加减乘除平方根号运算的整数显示】
v1【在上个版本基础上，实现了小数的显示】
v2【在上个版本基础上，实现了负数显示】

曾出现过问题：
1.//all_digital_tube_display_v1出现开机默认显示8.0000000的情况【已解决】。 问题原因：忘了....
2.小数点的前一位，即个位为2的情况下，显示出错【已解决】。 问题原因：位码错误.
3.显示小于1的小数时出现的个位0显示为除数错误的问题【已解决】。 问题原因：char int_part_array[8];未在初始化时全元素幅值0，导致垃圾/残留指被访问if (i == 0) {i++;} display((int_part_array[--i])+10,bits--);
4.

总结/教训/想法：
1.耦合度还是太高。
2.写代码之前先构建系统框架，确定模块、封装、接口的设计（我觉得我需要读一些软件工程的书籍，尤其是大规模程序开发相关的）。
3.仿真真好用，代码转C的exe程序后用软件仿真也蛮香的，不过还是没有直接在单片机上仿真香。一按按键就仿真断开出错，淦。
4.代码还是越规范越好，声明后第一件事就是，先置零了再说。
5.版本控制太棒了，git真香，github真好用，吹爆，两个版本代码对比清晰明显，爱了。
6.下次得记把程序错误、解决方法、问题原因都记下来。
7.记得建好工程后就把程序信息框加了，记录好版本什么的。
8.有时候编程碰到实在解决不了的问题就暂时跳过？等转一圈回来也许就突然想通了。
-----------------------------------------*/


#include <STC15F2K60S2.h>
#include <nixietube.h>
#include <matrixkeyboard.h>
#include <math.h>	//用于处理根号

unsigned char fun_state;//函数按键计数
double keynum,now_display_num,last_display_num; 


void cls_buzz_and_leds(void);
double add(double n1,double n2);
double subtract(double n1,double n2);
double multiply(double n1,double n2);
double divide(double n1,double n2);
double square(double n1);
double square_root(double n1);

/*
//------------------------------------------测试用----------------------------------------------------------------------
double a=1,l=3;

void main(void){

	
	while(1){
		all_digital_tube_display_v1(divide(a,l));//result:0.66666   正常
		

	}
}
//-----------------------------------------------------------------------------------------------------------------------
*/



void main(void){
	fun_state=0;//初始化置零
	keynum=0;
	now_display_num=0;
	last_display_num=0;
	cls_buzz_and_leds();

	
	
	//all_digital_tube_display_v1(now_display_num);delay_ms(500);//成功显示0
	
	while(1){
		
		if(check_press()!=0){
			
			keynum=check_press();	//键盘返回值缓存
			delay_ms(100);	//用于避免按键按下后取值太快，取到不想要的重复值
			
			if(keynum<14){	//按下的是数字部分
				now_display_num=now_display_num*10+(keynum-4);
			}
			
			else{	//按下的是功能部分按键，记录按下按键号，若按下两次相同的功能按键，则等价为=操作(两个数运算)，若是只有一个数的运算，则直接出结果
				if(keynum<18){	//需要两串数字参与的运算
					
					if(fun_state==0){	//功能按键之前没有按下的状态，则执行按下对应功能的操作
						last_display_num=now_display_num;	//当前显示数字备份
						now_display_num=0;//当前显示清零
						fun_state=keynum;	//按下的功能按键记录
						keynum=0;
					}
					
					else{	//若功能按键之前执行过操作，则直接执行=求结果操作
						//all_digital_tube_display_v1(0);	没能解决1/3=3.3333的问题
						switch(fun_state){
							case 14: now_display_num=add(last_display_num,now_display_num);break;
							case 15: now_display_num=subtract(last_display_num,now_display_num);break;
							case 16: now_display_num=multiply(last_display_num,now_display_num);break;
							case 17: now_display_num=divide(last_display_num,now_display_num);break;
							default:all_digital_tube_display(9999);break;	//错误提示
						}
					}
					
				}
				
				else{	//只需要一串数字的运算
					if(keynum==18){now_display_num=square(now_display_num);}
					else{now_display_num=square_root(now_display_num);}
				}
				
			}
			
		}
		all_digital_tube_display(now_display_num);
		
	}	//while(1)}
}//main(void)}


void cls_buzz_and_leds(void) //关掉蜂鸣器和板载leds
{
	P2 = (P2&0x1F|0xA0);	//适用环境实验配置：J3跳线配置为IO方式，J5配置为KBD、J2配置为1-3和2-4
	P0 = 0x00;
	P2 &= 0x1F;
	delay_ms(10);
	P2 = ((P2&0x1f)|0x80);
	P0 = 0xff;  //LED关
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
double square_root(double n1){	//√
	return (double)sqrt(n1);
}






