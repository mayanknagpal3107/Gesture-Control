#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "uart.c"
#include "lcd.h"
#include "lcd.c"


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

volatile char ob1=0,ob2=0,ob3=0,ob4=0;


unsigned char Obstacle_detectin(unsigned char i)
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
	
	if(i==1)
	{
		cbi(Obs_PORT,Obs1_trg);
		_delay_ms(10);
		if(!(Obs_PORT_PIN&(1<<Obs1_sense))) { stopall; return 1;}
		else return 0;
	}
	if(i==2)
	{
		cbi(Obs_PORT,Obs2_trg);
		_delay_ms(10);
		if(!(Obs_PORT_PIN&(1<<Obs2_sense))) { stopall; return 1;}
		else return 0;		
	}
	if(i==3)
	{
		cbi(Obs_PORT,Obs3_trg);
		_delay_ms(10);
		if(!(Obs_PORT_PIN&(1<<Obs3_sense))) { stopall; return 1;}
		else return 0;		
	}
	if(i==4)
	{
		cbi(Obs_PORT,Obs4_trg);
		_delay_ms(10);
		if(!(Obs_PORT_PIN&(1<<Obs4_sense))) { stopall; return 1;}
		else return 0;		
	}
	if(i==5)
	{
		cbi(Obs_PORT,Obs2_trg);
		cbi(Obs_PORT,Obs4_trg);
		_delay_ms(10);
		if((!(Obs_PORT_PIN&(1<<Obs2_sense)))&&(!(Obs_PORT_PIN&(1<<Obs4_sense)))) { stopall; return 2;}
		else return 0;		
	}

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
	unsigned char x=0;
	_delay_ms(100);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	uart_puts("\nhi\n");
	sei();
	
	printf("hello");
	
	lcd_init(LCD_DISP_ON_BLINK);
	lcd_clrscr();
	lcd_home();
	lcd_puts("   Edubotix");
	lcd_gotoxy(0,1);
	lcd_puts("Innovation Labs");
	_delay_ms(3000);
	lcd_clrscr();
	lcd_home();
	lcd_puts("   Gesture");
	lcd_gotoxy(0,1);
	lcd_puts("  Controller");
	_delay_ms(3000);
	
	
	while(1)
	{
		unsigned int t=0;
	reset:	
		stopall;
		_delay_ms(40);
		DDRC=0;
	/*
	if(Obstacle_detectin(1))
		{
			t=200;
			while(t)
			{	
				if(Obstacle_detectin(3))
				{
					PORTC = 0x02;
					uart_putc('b');
					lcd_clrscr();
					lcd_home();
					lcd_puts("  Backward");
					_delay_ms(20);
					goto reset;
				}
				t--;
				_delay_ms(10);
			}
		}
	
	while(Obstacle_detectin(1)&&Obstacle_detectin(2)&&Obstacle_detectin(3)&&Obstacle_detectin(4))) 
		{
			
			PORTC=0xFF;
		}
		*/
	
	if(Obstacle_detectin(2))
		{
			t=80;
			while(t)
			{	
				if(Obstacle_detectin(4))
				{
					PORTC = 0x02;
					uart_putc('l');
					lcd_clrscr();
					lcd_home();
					lcd_puts("  Left");
					_delay_ms(20);
					goto reset;
				}
				t--;
				_delay_ms(10);
			}
		}

	if(Obstacle_detectin(4))
		{
			t=80;
			while(t)
			{	
				if(Obstacle_detectin(2))
				{
					PORTC = 0x02;
					uart_putc('r');
					lcd_clrscr();
					lcd_home();
					lcd_puts("  right");
					_delay_ms(20);
					goto reset;
				}
				t--;
				_delay_ms(10);
			}
		}
		
	if(Obstacle_detectin(1))
		{
			PORTC = 0x08;
			uart_putc('f');
			lcd_clrscr();
			lcd_home();
			lcd_puts("  Forward");
			goto reset;
				
		}
		
	if(Obstacle_detectin(3))
		{
			PORTC = 0x01;
			uart_putc('b');
			lcd_clrscr();
			lcd_home();
			lcd_puts("  Backward");
			_delay_ms(200);
			if(Obstacle_detectin(3)) 
			{
				uart_putc('s');
				lcd_clrscr();
				lcd_home();
				lcd_puts("  stop");
				_delay_ms(600);
			}
			goto reset;
		}
		//else stopall;
		\
	}
}


































































































































































































































