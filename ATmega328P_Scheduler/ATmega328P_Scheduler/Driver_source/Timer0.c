/*
 * Timer0.c
 *
 * Created: 11/10/2019 12:39:23 p. m.
 *  Author: Lalo
 */ 

#include <Timer0.h>

uint16_t Timer0_u16CounterOV=0;
uint8_t Timer0_u8CompareValueOCA=0;
uint8_t Timer0_u8CompareValueOCB=0;
void Timer0__vInit(Timer0_nMode enMode, Timer0_nClock enClockSource, uint8_t u8Tick )
{
	TCCR0B&=~0x7;
	TCCR0A&=~((1<<WGM01)|(1<<WGM00));
	TCCR0B&=~((1<<WGM02));
	switch (enMode)
	{
		case Timer0_enModePWMPhase_MAX:
			TCCR0A|=(1<<WGM00);
			break;
		case Timer0_enModeNormal_OCRA:
			TCCR0A|=(1<<WGM01);
			OCR0A=u8Tick;
			break;
		case Timer0_enModePWM_MAX:
			TCCR0A|=(1<<WGM01)|(1<<WGM00);
			break;
		case Timer0_enModePWMPhase_OCRA:
			TCCR0A|=(1<<WGM00);
			TCCR0B|=(1<<WGM02);
			OCR0A=u8Tick;
		case Timer0_enModePWM_OCRA:
			TCCR0A|=(1<<WGM01)|(1<<WGM00);
			TCCR0B|=(1<<WGM02);
			OCR0A=u8Tick;
			break;
		case Timer0_enModeNormal_MAX:
		case Timer0_enModeReserved0:
		case Timer0_enModeReserved1:
			break;
	}
	TCNT0=0;
	TCCR0B|=(uint8_t)enClockSource&0x7;
	
}

void Timer0__vInitPin(Timer0_nCompareModule enModule)
{
	if(enModule&Timer0_enModuleA)
	{
		DDRD|=(1<<DDD6);
		PORTD&=~(1<<PORTD6);
	}
	if(enModule&Timer0_enModuleB)
	{
		DDRD|=(1<<DDD5);
		PORTD&=~(1<<PORTD5);
	}	
}

void Timer0__vDeInitPin(Timer0_nCompareModule enModule)
{
	if(enModule&Timer0_enModuleA)
	{
		DDRD&=~(1<<DDD6);
	}
	if(enModule&Timer0_enModuleA)
	{
		DDRD&=~(1<<DDD5);
	}
}

void Timer0__vSetOutputMode(Timer0_nCompareModule enModule,Timer0_nCompareOutput enOutMode)
{
	if(enModule&Timer0_enModuleA)
	{
		TCCR0A&=~(3<<COM0A0);
		TCCR0A|=(((uint8_t)enOutMode&3)<<COM0A0);
	}
	if(enModule&Timer0_enModuleB)
	{
		TCCR0A&=~(3<<COM0B0);
		TCCR0A|=(((uint8_t)enOutMode&3)<<COM0B0);
	}
	
}

void Timer0__vSetCompareValue(Timer0_nCompareModule enModule,uint8_t u8Value)
{
	if((enModule&Timer0_enModuleA)==Timer0_enModuleA)
	{
		Timer0_u8CompareValueOCA=u8Value;
		OCR0A=u8Value;
	}
	if((enModule&Timer0_enModuleB)==Timer0_enModuleB)
	{
		Timer0_u8CompareValueOCB=u8Value;
		OCR0B=u8Value;
	}
	
}

void Timer0__vSetCompareValueInterrupt(Timer0_nCompareModule enModule,uint8_t u8Value)
{
	if((enModule&Timer0_enModuleA)==Timer0_enModuleA)
	{
		Timer0_u8CompareValueOCA=u8Value;
		TIMSK0|= ((uint8_t)Timer0_enInterruptOCIEA);
	}
	if((enModule&Timer0_enModuleB)==Timer0_enModuleB)
	{
		Timer0_u8CompareValueOCB=u8Value;
		TIMSK0|= ((uint8_t)Timer0_enInterruptOCIEB);
	}
	
}



void Timer0__vSetCount(uint8_t u8Count)
{	
	TCNT0=u8Count;	
}

void Timer0__vClearCount(void)
{
	TCNT0=0;	
}

void Timer0__vEnableInterrupt(Timer0_nInterrupt enInterrupt)
{
	TIMSK0= ((uint8_t)enInterrupt&0x07);
	
}void Timer0__vDisableInterrupt(Timer0_nInterrupt enInterrupt)
{
	TIMSK0&=~((uint8_t)enInterrupt&0x07);
}
void Timer0__vClearInterrupt(Timer0_nInterrupt enInterrupt)
{
	TIFR0&=~ ((uint8_t)enInterrupt&0x07);
	
}void Timer0__vSetInterrupt(Timer0_nInterrupt enInterrupt)
{
	TIFR0|=((uint8_t)enInterrupt&0x07);
}
void Timer0__vClearCounterOV(void)
{
	Timer0_u16CounterOV=0;
	
}
uint16_t Timer0__u16GetCounterOV(void)
{
	return (uint16_t)Timer0_u16CounterOV;
}
/*
ISR(TIMER0_OVF_vect)
{
	Timer0_u16CounterOV++;
	
	LEDRED_OUT&=~LEDRED_PIN;
	LEDAMBER_OUT&=~LEDAMBER_PIN;
	LEDGREEN_OUT&=~LEDGREEN_PIN;
	
}
ISR(TIMER0_COMPA_vect)
{
	OCR0A=Timer0_u8CompareValueOCA;
	TIMSK0&=~ ((uint8_t)Timer0_enInterruptOCIEA);
}
ISR(TIMER0_COMPB_vect)
{
	OCR0B=Timer0_u8CompareValueOCB;
	TIMSK0&=~ ((uint8_t)Timer0_enInterruptOCIEB);
	
}
*/