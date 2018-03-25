#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
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

#define stopall Obs_PORT=0xFF;//Obs_PORT=0x2A;

unsigned char c[4]={0},i=0;

void transmitt(unsigned char);
unsigned char trans=0;
unsigned int count=0,speed=0;
unsigned long f;
float x,y;

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

unsigned char Obstacle_detect(unsigned char i)
{
	//_delay_ms(30);
	Obs_PORT = 0xFE;
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

}

unsigned char detect_all()
{
	//_delay_ms(30);
	Obs_PORT = 0xFE;
	sbi(Obs_PORT_DIR,Obs1_trg);
	sbi(Obs_PORT_DIR,Obs2_trg);
	sbi(Obs_PORT_DIR,Obs3_trg);
	sbi(Obs_PORT_DIR,Obs4_trg);
	
	cbi(Obs_PORT_DIR,Obs1_sense);
	cbi(Obs_PORT_DIR,Obs2_sense);
	cbi(Obs_PORT_DIR,Obs3_sense);
	cbi(Obs_PORT_DIR,Obs4_sense);
	Obs_PORT &= ~((1<<Obs1_trg)|(1<<Obs2_trg)|(1<<Obs3_trg)|(1<<Obs4_trg));//|(1<<Obs2_trg)|(1<<Obs3_trg);
	_delay_ms(10);
	//if((!(PINA&(1<<Obs1_sense)))&&(!(PINA&(1<<Obs2_sense)))) {stopall; return 1;}
	if((!(PINA&(1<<Obs3_sense)))&&(!(PINA&(1<<Obs4_sense)))) {stopall; return 2;}
	//if((!(PINA&(1<<Obs3_sense)))&&(!(PINA&(1<<Obs4_sense)))) {stopall; return 2;}
	/*
	if(!(PINA&(1<<Obs1_sense))) {stopall; return 1;}
	if(!(PINA&(1<<Obs2_sense))) {stopall; return 2;}
	if(!(PINA&(1<<Obs3_sense))) {stopall; return 3;}
	*/
	else return 0;	
}

void main()
{
	unsigned char x=0,str[3]={0};
	_delay_ms(300);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	uart_puts("\nhi\n");
	sei();
	
	while(1)
	{
		x=detect_all();
		itoa(x,str,10);
		uart_puts(str);
		_delay_ms(300);
		uart_puts("\n");
	}
	
}









/*

void main()
{
	//unsigned char x=0;
	unsigned int tr[5],speed=0;
	_delay_ms(300);
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	
	uart_puts("\nhi\n");
	while(1)
	{
		//uart_putc(c[3]);
		buzzer_off();
		PORTC = 0;
		TIMSK |= (1<<TOIE0);//|(1<<TOIE2);
		TCNT0 = 0;
		sei();
		if(Obstacle_detect(1))
		{
			uart_puts("\nstart\n");
			TCCR0 = 0x05;
			//TCCR2 = 0x03;
			buzzer_on();
			
			while(!(Obstacle_detect(2)));
			TCCR0 = 0x00;
			cli();
			f = (count*256)+TCNT0;
			//x=f;
			x=((float)f*0.0069)/100;
			speed=(distance*60)/x;
			if(speed>25) transmitt('f');
			else transmitt('1');
			
			//uart_puts(dtostrf(y,3,5,tr));
			itoa((unsigned int)speed,tr,10);
			uart_puts(tr);
			uart_puts(" meter/minuite");
			uart_puts("\n\r");
			
			count=0;
			speed=0;
		}
		uart_puts("\nend\n");
		_delay_ms(300);
	}
} 


ISR(TIMER0_OVF_vect)
{
	count++;
}

void transmitt(unsigned char t)
{
	unsigned int p=3;
	while(p)
	{
		uart_putc(t);
		_delay_ms(20);
		p--;
	}
}



ISR(SIG_USART_RECV)
{
	uart_puts("\nok");
	c[i++]=UDR;
	//i++;
	if(i==4) i=0;
}
*/



































































































































































































































