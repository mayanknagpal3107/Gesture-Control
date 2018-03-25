#include <avr/io.h>
#include <compat/deprecated.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "uart.c"
#include "lcd.h"
#include "lcd.c"

#define trg_on 	cbi(PORTA, 7);
#define trg_off 	sbi(PORTA, 7);

#define stopall Obs_PORT=0xFF;

volatile char flag_trg=0,count=0;

void Obstacle_init()
{
		PORTA = 0xFF;
		sbi(DDRA,7);
		cbi(DDRA,0);
		cbi(DDRA,1);
		cbi(DDRA,2);
		cbi(DDRA,3);
}

void Timer_init()
{
	TCNT0 = 0x70;
	TCCR0=0x05;
	TIMSK |= (1<<TOIE0);
	sei();
}


void main()
{
		unsigned int str[5]={0};
		unsigned int val=0,Arr[4]={0};
		unsigned int index=0;
		uart_init(UART_BAUD_SELECT(9600,F_CPU));
		Obstacle_init();
		Timer_init();
		sei();
		DDRC = 0xFF;
		PORTC = 0;
		//PORTC = 0xFF;
		
		uart_puts("hello");
		//PORTA = 0xFF;
		
		while(1)
		{
			//uart_puts("\nhello\n");
			
			val = PINA&0x0F;
			PORTC = 0;
			//itoa(val, str, 10);
			//uart_puts(str);
			
		///*	
			if(val!=0x0F)
				{
				cli();
					if(index!=0)
					{
						if(val!=(Arr[index-1])) Arr[index++]=val;
					}
					else Arr[index++]=val;
				sei();
				}
			if(index>2)
				{
					PORTC = 0xFF;
					_delay_ms(100);
									
					if((Arr[0]==0x07)&&((Arr[2]==0x0D)||(Arr[3]==0x0D))) { uart_putc('r');	index=0; }
					if((Arr[0]==0x0D)&&((Arr[2]==0x07)||(Arr[3]==0x07))) { uart_putc('l'); 	index=0; }
					if((Arr[0]==0x0B)&&((Arr[2]==0x0E)||(Arr[3]==0x0E))) { uart_putc('f'); 	index=0; }
					if((Arr[0]==0x0E)&&((Arr[2]==0x0B)||(Arr[3]==0x0B))) { uart_putc('b'); 	index=0; }
					else index=0;
					
				}
			//_delay_ms(20);
		//*/
			 
			 
		}
}



ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0x70;
	count++;
	if(count==2)
	{
		//flag_trg++;
		//uart_puts("hello2\n");
		if(flag_trg==0)
		{
			trg_on;
			//PORTC = 0xFF;
			flag_trg = 1;
		}
		else if(flag_trg==1)
		{
			trg_off;
			//PORTC = 0;
			flag_trg = 0;
		}
		
		count = 0;
	}
}


























































































































































































































