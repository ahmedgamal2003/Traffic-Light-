/*
 * traffic_light.c
 *
 * Created: 10/23/2024 3:05:03 PM
 *  Author: AHMED GAMAL
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 800000UL
#include <util/delay.h>
#include "LCD.h"
#include "LED.h"
#include "timer.h"

volatile unsigned char counter=0;
unsigned char green=10;
unsigned char red=7;
unsigned char yellow=5;

int main(void)
{
	LCD_vInit();
	LED_vInit('B',5);
	LED_vInit('B',6);
	LED_vInit('B',7);
	LCD_vSend_string("AHMED");
	timer_CTC_init_interrupt();
	
	while(1)
	{
		unsigned char green=10;
		unsigned char red=7;
		unsigned char yellow=5;
		LCD_clearscreen();
		LCD_vSend_string("remaining 10 sec");
		LED_vTurnOn('B',5);
		_delay_ms(1000);
		while(green>0)
		{
			if(counter>=100)
			{
				counter=0;
				green--;
				LCD_movecursor(1,11);
				LCD_vSend_char(' ');
				LCD_vSend_char((green%10)+48);
			}
		}
		_delay_ms(1000);
		LED_vTurnOff('B',5);
		LED_vTurnOn('B',6);
		LCD_clearscreen();
		LCD_vSend_string("Stop 7 sec");
		_delay_ms(1000);
		while(red>0)
		{
			if (counter>=100)
			{
				counter=0;
				red--;
				LCD_movecursor(1,6);
				LCD_vSend_char((red%10)+48);
			}
			
		}
		_delay_ms(1000);
		LED_vTurnOff('B',6);
		LED_vTurnOn('B',7);
		LCD_clearscreen();
		LCD_vSend_string("Wait 5 sec");
		_delay_ms(1000);
		while(yellow>0)
		{
			if (counter>=100)
			{
				counter=0;
				yellow--;
				LCD_movecursor(1,6);
				LCD_vSend_char((yellow%10)+48);
			}
		}
		_delay_ms(1000);
		LED_vTurnOff('B',7);
	}
}

ISR(TIMER0_COMP_vect)
{
	counter++;
}