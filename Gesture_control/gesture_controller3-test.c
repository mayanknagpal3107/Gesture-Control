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
	_delay_ms(20);
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
	unsigned int A=0,str1[6]={0};
	_delay_ms(100);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	uart_puts("\nhi\n");
	sei();
\

	
	while(1)
	{
		unsigned int t=100;
		Obstacle_detect();
		itoa(ob1,str1,10);
		uart_puts(str1);
		uart_puts("\n");
		
		itoa(ob2,str1,10);
		uart_puts(str1);
		uart_puts("\n");
		
		itoa(ob3,str1,10);
		uart_puts(str1);
		uart_puts("\n");
		
		itoa(ob4,str1,10);
		uart_puts(str1);
		uart_puts("\n");
		uart_puts("\n");
		uart_puts("\n");
		ob1=ob2=ob3=ob4=0;
		_delay_ms(200);
	}
	
}



































































































































































































































