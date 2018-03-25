#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "uart.c"
//#include "lcd.h"
//#include "lcd.c"


#define Obs_PORT_DIR 	DDRA
#define Obs_PORT_PIN 	PINA
#define Obs_PORT	 	PORTA

#define Obs1_trg 		0
#define Obs1_sense 		1

#define Obs2_trg 		2
#define Obs2_sense 		3

#define Obs3_trg 		4
#define Obs3_sense 		5

#define Obs4_trg 		6
#define Obs4_sense 		7

#define stopall Obs_PORT=0xFF;

unsigned char ob1=0,ob2=0,ob3=0,ob4=0;

void Obstacle_detect()
{
	//_delay_ms(30);
	Obs_PORT = 0xFF;
	sbi(Obs_PORT_DIR,Obs1_trg);
	sbi(Obs_PORT_DIR,Obs2_trg);
	sbi(Obs_PORT_DIR,Obs3_trg);
	sbi(Obs_PORT_DIR,Obs4_trg);
	
	cbi(Obs_PORT_DIR,Obs1_sense);
	cbi(Obs_PORT_DIR,Obs2_sense);
	cbi(Obs_PORT_DIR,Obs3_sense);
	cbi(Obs_PORT_DIR,Obs4_sense);
	Obs_PORT = ~((1<<Obs1_trg)|(1<<Obs2_trg)|(1<<Obs3_trg)|(1<<Obs4_trg));
	_delay_ms(10);
	if(!(Obs_PORT_PIN&(1<<Obs1_sense))) ob1=1;
	if(!(Obs_PORT_PIN&(1<<Obs2_sense))) ob2=1;
	if(!(Obs_PORT_PIN&(1<<Obs3_sense))) ob3=1;
	if(!(Obs_PORT_PIN&(1<<Obs4_sense))) ob4=1;

}

void buzzer_off()
{
	sbi(DDRA,0);
	cbi(PORTA,0);
	//_delay_ms(40);
	//cbi(PORTA,0);
}

void buzzer_on()
{
	sbi(DDRA,0);
	sbi(PORTA,0);
	_delay_ms(20);
	//cbi(PORTA,0);
}

void main()
{
	unsigned int A=0,str[6]={0};
	_delay_ms(100);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	uart_puts("\nhi\n");
	sei();
	/*
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_clrscr();
	lcd_home();
	lcd_puts("   Edubotix");
	lcd_puts("Innovation Labs");
	lcd_clrscr();
	lcd_home();
	lcd_puts("   Gesture");
	lcd_puts("  Controller");
	*/
	
	
	while(1)
	{
		unsigned int t;
		Obstacle_detect();
		//Obstacle_detect();
	if(ob1==1)
		{
			ob2=ob3=ob4=0;
			uart_puts("\ntop side detected\n");
			t=80;
			while(t)
			{	
				//Obstacle_detect();
				Obstacle_detect();
				if(ob3==1)
				{
					uart_puts("\nbackward\n");
					//lcd_puts("  backward");
					ob3=0;
					goto out1;
				}
				t--;
				_delay_ms(10);
			}
			out1: ob1=0;
		}
		
		
	if(ob4==1)
		{
			ob1=ob2=ob3=0;
			uart_puts("\nleft side detected\n");
			t=80;
			while(t)
			{	
				//Obstacle_detect();
				Obstacle_detect();
				if(ob2==1)
				{
					uart_puts("\nroght\n");
					//lcd_puts("  Right");
					ob2=0;
					goto out2;
				}
				t--;
				_delay_ms(10);
			}
			out2: ob4=0;
		}
		
		
	if(ob2==1)
		{
			ob1=ob3=ob4=0;
			uart_puts("\nRight side detected\n");
			t=80;
			while(t)
			{	
				//Obstacle_detect();
				Obstacle_detect();
				if(ob4==1)
				{
					uart_puts("\nLeft\n");
					//lcd_puts("  Left");
					ob4=0;
					goto out3;
				}
				t--;
				_delay_ms(10);
			}
			out3: ob2=0;
		}
		
		
	if(ob3==1)
		{
			ob1=ob2=ob4=0;
			uart_puts("\nBottom side detected\n");
			t=80;
			while(t)
			{	
				//Obstacle_detect();
				Obstacle_detect();
				if(ob1==1)
				{
					uart_puts("\nForward\n");
					//lcd_puts("  Forward");
					ob1=0;
					goto out4;
				}
				t--;
				_delay_ms(10);
			}
			out4: ob3=0;
		}
		else uart_puts("\nNothing\n");
		_delay_ms(100);
	}
	
}



































































































































































































































