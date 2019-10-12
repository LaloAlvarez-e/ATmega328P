/*
 * Timer0.h
 *
 * Created: 11/10/2019 12:39:08 p. m.
 *  Author: Lalo
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <GPIO.h>
typedef enum
{
	Timer0_enModeNormal_MAX   =0,
	Timer0_enModePWMPhase_MAX ,
	Timer0_enModeNormal_OCRA,
	Timer0_enModePWM_MAX,
	Timer0_enModeReserved0,
	Timer0_enModePWMPhase_OCRA,
	Timer0_enModeReserved1,
	Timer0_enModePWM_OCRA,
}Timer0_nMode;

typedef enum
{
	Timer0_enCompareDisable   =0,
	Timer0_enCompareToggle=1, 
	Timer0_enCompareClear=2, 
	Timer0_enCompareSet=3,
}Timer0_nCompareOutput;

typedef enum
{
	Timer0_enModuleA  =1,
	Timer0_enModuleB=2,
}Timer0_nCompareModule;

typedef enum
{
	Timer0_enClockDisable   =0,
	Timer0_enClockDiv1,
	Timer0_enClockDiv8,
	Timer0_enClockDiv64,
	Timer0_enClockDiv256,
	Timer0_enClockDiv1024,
	Timer0_enClockExtFalling,
	Timer0_enClockExtRising,
}Timer0_nClock;

typedef enum
{
	Timer0_enInterruptTOIE   =(1<<TOIE0),
	Timer0_enInterruptOCIEA	 =(1<<OCIE0A),
	Timer0_enInterruptOCIEB  =(1<<OCIE0B),
}Timer0_nInterrupt;

void Timer0__vInit(Timer0_nMode enMode, Timer0_nClock enClockSource, uint8_t u8Tick );

void Timer0__vInitPin(Timer0_nCompareModule enModule);
void Timer0__vDeInitPin(Timer0_nCompareModule enModule);

void Timer0__vSetOutputMode(Timer0_nCompareModule enModule,Timer0_nCompareOutput enOutMode);
void Timer0__vSetCompareValue(Timer0_nCompareModule enModule,uint8_t u8Value);
void Timer0__vSetCompareValueInterrupt(Timer0_nCompareModule enModule,uint8_t u8Value);

void Timer0__vSetCount(uint8_t u8Count);
void Timer0__vClearCount(void);

void Timer0__vEnableInterrupt(Timer0_nInterrupt enInterrupt);
void Timer0__vDisableInterrupt(Timer0_nInterrupt enInterrupt);
void Timer0__vSetInterrupt(Timer0_nInterrupt enInterrupt);
void Timer0__vClearInterrupt(Timer0_nInterrupt enInterrupt);


void Timer0__vClearCounterOV(void);
uint16_t Timer0__u16GetCounterOV(void);

#endif /* TIMER0_H_ */