/*
 * ATmega328P_ExternalInterrupt.c
 *
 * Created: 10/10/2019 01:58:42 p. m.
 * Author : Lalo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>


void vInitPort(void);
void vInitPortInterrupt(void);

#define LEDRED_PIN	(1<<PORTB5)
#define LEDRED_DIR	(DDRB)
#define LEDRED_OUT	(PORTB)

#define LEDGREEN_PIN	(1<<PORTC4)
#define LEDGREEN_DIR	(DDRC)
#define LEDGREEN_OUT	(PORTC)

#define LEDAMBER_PIN	(1<<PORTC5)
#define LEDAMBER_DIR	(DDRC)
#define LEDAMBER_OUT	(PORTC)

#define PBUTTON1_READPIN	(1<<PIND2)
#define PBUTTON1_READPORT	(PIND)
#define PBUTTON1_DIR		(DDRD)
#define PBUTTON1_PULLUP		(PORTD)

#define PBUTTON2_READPIN	(1<<PINB2)
#define PBUTTON2_READPORT	(PINB)
#define PBUTTON2_DIR		(DDRB)
#define PBUTTON2_PULLUP		(PORTB)

#define PBUTTON3_READPIN	(1<<PINB1)
#define PBUTTON3_READPORT	(PINB)
#define PBUTTON3_DIR		(DDRB)
#define PBUTTON3_PULLUP		(PORTB)

typedef enum
{
	PBUTTON1_enPRESS = 0,
	PBUTTON1_enRELEASE = PBUTTON1_READPIN, 
	
}PBUTTON1_nState;

typedef enum
{
	PBUTTON2_enPRESS = 0,
	PBUTTON2_enRELEASE = PBUTTON2_READPIN,
	
}PBUTTON2_nState;

typedef enum
{
	PBUTTON3_enPRESS = 0,
	PBUTTON3_enRELEASE = PBUTTON3_READPIN,
	
}PBUTTON3_nState;

#define PBUTTON1_READSTATE  (PBUTTON1_READPORT & PBUTTON1_READPIN)
#define PBUTTON2_READSTATE  (PBUTTON2_READPORT & PBUTTON2_READPIN)
#define PBUTTON3_READSTATE  (PBUTTON3_READPORT & PBUTTON3_READPIN)


volatile uint8_t main_u8Count=0;
int main(void)
{
    /* Replace with your application code */
	vInitPort();
	vInitPortInterrupt();
	sei();
    while (1) 
    {
		if(main_u8Count>(uint8_t)10)
		{
			LEDRED_OUT|=LEDRED_PIN;
			main_u8Count=0;
		}
    }
}



void vInitPort(void)
{
	MCUCR&=~(1<<PUD);    /*Enable global Pull-Up*/
	PBUTTON1_DIR   &=~PBUTTON1_READPIN;   /*PD.2 (Push Button1) as Input*/
	PBUTTON1_PULLUP|= PBUTTON1_READPIN;   /*PD.2 (Push Button1) with Pull-Up*/
	
	PBUTTON2_DIR   &=~PBUTTON2_READPIN;   /*PB.2 (Push Button2) as Input*/
	PBUTTON2_PULLUP|= PBUTTON2_READPIN;   /*PB.2 (Push Button2) with Pull-Up*/
	
	PBUTTON3_DIR   &=~PBUTTON3_READPIN;   /*PB.1 (Push Button2) as Input*/
	PBUTTON3_PULLUP|= PBUTTON3_READPIN;   /*PB.1 (Push Button2) with Pull-Up*/
	
	LEDRED_DIR   |= LEDRED_PIN;		/*PB.5 (Led RED) as Output*/
	LEDGREEN_DIR |= LEDGREEN_PIN;		/*PC.5 (Led GREEN) as Output*/
	LEDAMBER_DIR |= LEDAMBER_PIN;		/*PC.4 (Led AMBER) as Output*/
	
	LEDRED_OUT  &=~LEDRED_PIN;		/*PC.5 (Led RED) Output Low*/
	LEDGREEN_OUT&=~LEDGREEN_PIN;		/*PC.5 (Led GREEN) Output Low*/
	LEDAMBER_OUT&=~LEDAMBER_PIN;		/*PC.4 (Led AMBER) Output Low*/
	
}

void vInitPortInterrupt(void)
{
	/* External Interupt EINT0 (PD2) o EINT1 (PD3)*/
	
	/*
	*  EICRA = External Interrupt Control Register A
	*  Register used for configure sensing level of Interrupts
	*  ISC11  ISC10   Description
	*   0       0     The low level of INT1 generates an interrupt request.
	*   0       1     Any logical change on INT1 generates an interrupt request
	*   1       0     The falling edge of INT1 generates an interrupt request
	*   1       1     The rising edge of INT1 generates an interrupt request.
	*	Same For INT0 (ISC01, ISC00)
	*/
	EICRA=(1<<ISC00); /* Any logical change on INT1 generates an interrupt request*/
	
	/*
	*  EIMSK = External Interrupt Mask Register
	*  Register used for enable EXT Interrupts
	*  INT0: enable EINT0
	*  INT1: enable EINT1
	*/	
	EIMSK=(1<<INT0);/*Enable EINT0 (PD.2)*/ 
	
	/* Pin Change Interupt PCINT[0-23]
	*	PCINT0= PCINT[0-7]
	*	PCINT1= PCINT[8-15]
	*	PCINT2= PCINT[16-23]
	*/
	
	/*
	*  PCICR = Pin Change Interrupt Control Register
	*  Register used to enable Pin change Interrupts
	*  PCIE0: Enable PCINT0
	*  PCIE1: Enable PCINT1
	*  PCIE2: Enable PCINT2
	*/	
	PCICR=(1<<PCIE0); /*Enable PCINT0 because program use PB2 and PB1 (PCINT[1,2])*/
	
	/*PCMSKn Pin Change Mask Register n
	*
	* PCMSK2: Enable PCINT[16-23]
	* PCMSK1: Enable PCINT[8-15]
	* PCMSK0: Enable PCINT[0-7]
	*
	*/
	PCMSK0= (1<<PCINT2)|(1<<PCINT1); /*Enable PCINT[1,2]*/
	
	
}

/*Interrupt for INT0 PD2*/
ISR(INT0_vect)
{
	uint8_t u8IntValue=PIND& (1<<PIND2);
	if(u8IntValue==0) /*Pin change from 5v to 0v Falling edge*/
	{
		LEDRED_OUT|=LEDRED_PIN;
	}
	else/*Pin change from 0v to 5v Rising edge*/
	{
		LEDRED_OUT&=~LEDRED_PIN;
	}
}

ISR(PCINT0_vect)
{
	static uint8_t u8PreviousValuePB1=(1<<PINB1);
	static uint8_t u8PreviousValuePB2=(1<<PINB2);
	
	uint8_t u8ActualValuePB1=(PINB & (1<<PINB1));
	uint8_t u8ActualValuePB2=(PINB & (1<<PINB2));
	if(u8ActualValuePB1 != u8PreviousValuePB1 )
	{
		if( u8ActualValuePB1==0)/*Pin change from 5v to 0v Falling edge*/
		{
			LEDAMBER_OUT|=LEDAMBER_PIN;
			
		}
		else/*Pin change from 0v to 5v Falling edge*/
		{
			LEDAMBER_OUT&=~LEDAMBER_PIN;
		}
	}
	if(u8ActualValuePB2 != u8PreviousValuePB2 )
	{
		if( u8ActualValuePB2==0)/*Pin change from 5v to 0v Falling edge*/
		{
			LEDGREEN_OUT|=LEDGREEN_PIN;
				
		}
		else/*Pin change from 0v to 5v Falling edge*/
		{
			LEDGREEN_OUT&=~LEDGREEN_PIN;
			main_u8Count++;
		}
	}
	u8PreviousValuePB1=u8ActualValuePB1;
	u8PreviousValuePB2=u8ActualValuePB2;
}