#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "uart.c"

#define ForWard PORTD = 0xB4;
#define Reverse PORTD = 0x78;
#define Stop	PORTD = 0x30;
#define Left	PORTD = 0x34;
#define Right	PORTD = 0xB0;

unsigned char c=0;
unsigned char ob1=0,ob2=0,ob3=0,ob4=0;

unsigned char suart_receive()
{
	while(!(c=uart_getc()));
	//while(!(c=uart_getc()));
	//while(!(c=uart_getc()));
	//buzzer();
	return c;
}

void init_motors(void)
{
	sbi(DDRD,4);
	sbi(DDRD,5);
	sbi(DDRD,6);
	sbi(DDRD,7);
	sbi(DDRD,2);
	sbi(DDRD,3);
	
	cbi(PORTD,6);
	cbi(PORTD,7);
	cbi(PORTD,2);
	cbi(PORTD,3);
	//cbi(PORTD,5);	-
}

void main()
{
	_delay_ms(300);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	sei();
	DDRC = 0xFF; // out LED for debugging
	init_motors(); // motors DDR setup
	uart_puts("\nhi\n");
	while(1)
	{
		c=suart_receive();
	if(c=='s') 
		{
			PORTC = 0xFF;
			Stop;
		}
	if(c=='f') 
		{
			PORTC = 0x08;
			ForWard;
		}
		
	if(c=='b') 
		{
			PORTC = 0x04;
			Reverse;
		}
		
	if(c=='r') 
		{
			PORTC = 0x02;
			Right;
		}
	
	if(c=='l') 
		{
			PORTC = 0x01;
			Left;
		}
		_delay_ms(50);
	}
	
}



































































































































































































































