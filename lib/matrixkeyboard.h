#ifndef _MATRIXKEYBOARD_H_
#define _MATRIXKEYBOARD_H_

char check_press(void);
void x_control(char state);
void y_control(char state);
int check_x_state(void);
int check_y_state(void);
void delay__ms(unsigned int t);

#endif