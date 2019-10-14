/*
 * GPIO.c
 *
 * Created: 11/10/2019 12:26:54 p. m.
 *  Author: Lalo
 */ 

#include <GPIO.h>

volatile uint8_t GPIO_u8CountPCINT2=0;
volatile uint8_t GPIO_u8CountINT0=0;

void GPIO__vInitPort(void)
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
	LEDBLUE_DIR |= LEDBLUE_PIN;		/*PC.3 (Led BLUE) as Output*/
	
	LEDRED_OUT  &=~LEDRED_PIN;		/*PC.5 (Led RED) Output Low*/
	LEDGREEN_OUT&=~LEDGREEN_PIN;		/*PC.5 (Led GREEN) Output Low*/
	LEDAMBER_OUT&=~LEDAMBER_PIN;		/*PC.4 (Led AMBER) Output Low*/
	LEDBLUE_OUT&=~LEDBLUE_PIN;		/*PC.4 (Led BLUE) Output Low*/
	
}

void GPIO__vInitPortInterrupt(void)
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
	EICRA=(1<<ISC01); /* FallingEdge on INT0 generates an interrupt request*/
	
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

void GPIO__vClearCounterRisingPCINT2(void)
{
	GPIO_u8CountPCINT2=0;
	
}

void GPIO__vSetCounterRisingPCINT2(uint8_t u8Value)
{
	GPIO_u8CountPCINT2=u8Value;
	
}
uint8_t GPIO__u8GetCounterRisingPCINT2(void)
{
	return GPIO_u8CountPCINT2;
	
}

void GPIO__vClearCounterRisingINT0(void)
{
	GPIO_u8CountINT0=0;
	
}

void GPIO__vSetCounterRisingINT0(uint8_t u8Value)
{
	GPIO_u8CountINT0=u8Value;
	
}
uint8_t GPIO__u8GetCounterRisingINT0(void)
{
	return GPIO_u8CountINT0;
	
}

/*Interrupt for INT0 PD2*/
ISR(INT0_vect)
{
	GPIO_u8CountINT0++;
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
			GPIO_u8CountPCINT2=0;
		}
		else/*Pin change from 0v to 5v Rising edge*/
		{
		}
	}
	if(u8ActualValuePB2 != u8PreviousValuePB2 )
	{
		if( u8ActualValuePB2==0)/*Pin change from 5v to 0v Falling edge*/
		{
			GPIO_u8CountPCINT2++;	
		}
		else/*Pin change from 0v to 5v Rising edge*/
		{	
		}
	}
	u8PreviousValuePB1=u8ActualValuePB1;
	u8PreviousValuePB2=u8ActualValuePB2;
}
