/*
 * Atmega328P_ReadPin.c
 *
 * Created: 09/10/2019 09:10:24 p. m.
 * Author : Lalo
 */ 

#include <avr/io.h>


#define LEDRED_PIN	(1<<PORTB5)
#define LEDRED_DIR	(DDRB)
#define LEDRED_OUT	(PORTB)

#define LEDGREEN_PIN	(1<<PORTC5)
#define LEDGREEN_DIR	(DDRC)
#define LEDGREEN_OUT	(PORTC)

#define PBUTTON_READPIN  (1<<PIND2)
#define PBUTTON_READPORT (PIND)
#define PBUTTON_DIR		 (DDRD)
#define PBUTTON_PULLUP	 (PORTD)

typedef enum
{
	PBUTTON_enPRESS = 0,
	PBUTTON_enRELEASE = PBUTTON_READPIN, 
	
}PBUTTON_nState;

#define PBUTTON_READSTATE  (PBUTTON_READPORT & PBUTTON_READPIN)

int main(void)
{
    /* Replace with your application code */
	MCUCR&=~(1<<PUD);    /*Enable global Pull-Up*/
	PBUTTON_DIR   &=~PBUTTON_READPIN;   /*PD.2 (Push Button) as Input*/
	PBUTTON_PULLUP|= PBUTTON_READPIN;   /*PD.2 (Push Button) with Pull-Up*/
	
	LEDRED_DIR   |= LEDRED_PIN;		/*PB.5 (Led RED) as Output*/
	LEDGREEN_DIR |= LEDGREEN_PIN;		/*PC.5 (Led GREEN) as Output*/
	
	LEDRED_OUT  &=~LEDRED_PIN;		/*PB.5 (Led RED) Output Low*/
	LEDGREEN_OUT&=~LEDGREEN_PIN;		/*PD.5 (Led GREEN) Output Low*/
	
    while (1) 
    {
		if(PBUTTON_READSTATE==PBUTTON_enRELEASE) /*Push Button released*/
		{
			LEDRED_OUT  |= LEDRED_PIN; /*PB.5 (Led RED) Output High*/
			LEDGREEN_OUT&=~LEDGREEN_PIN; /*PC.5 (Led GREEN) Output Low*/
		}
		else /*Push Button pressed PBUTTON_READSTATE=PBUTTON_enPRESS*/
		{
			LEDRED_OUT  &=~LEDRED_PIN; /*PB.5 (Led RED) Output Low*/
			LEDGREEN_OUT|= LEDGREEN_PIN; /*PC.5 (Led GREEN) Output High*/
		}
		
    }
}

