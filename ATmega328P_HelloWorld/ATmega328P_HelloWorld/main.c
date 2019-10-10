/*
 * ATmega328P_HelloWorld.c
 *
 * Created: 09/10/2019 12:18:08 p. m.
 * Author : Lalo
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	uint32_t u32Count=0;
	MCUCR &=~ (1<<PUD); /* Enable Global Pull-Up*/
	DDRB|=(1<<DD5);		/* PB.5 as Output*/
	PORTB&=~(1<<PORT5); /* PB.5 Output Low*/
    while (1) 
    {
		for(u32Count=0;u32Count<0xFFFFF;u32Count++); /*Delay*/
		PORTB^=(1<<PORT5);	/* PB.5 Toogle*/
    }
}

