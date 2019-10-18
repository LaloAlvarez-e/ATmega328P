/*
 * ATmega328P_Scheduler.c
 *
 * Created: 12/10/2019 01:51:06 a. m.
 * Author : Lalo
 */ 

#include <avr/io.h>
#include <os.h>
#include <ILI9163.h>
#include <Colors.h>

void Task1 (void);
void Task2 (void);
void Task3 (void);
void Task4 (void);
void Task5 (void);
void Task6 (void);


int main(void)
{
	
	GPIO__vInitPort();
	ILI9163__vInit();
	OS__enAddPeriodicThreads(&Task5,250,&Task6,100);
	OS__enAddMainThreads(&Task1, &Task2, &Task3, &Task4);
	OS__vLaunch();
}

uint8_t u8Flag=0;
void Task1(void)
{	
	uint8_t u8Status=0;
	static uint16_t u16Color=0;
	uint16_t u16I=0;

	while(1)
	{
		u8Status = OS__u8StartCriticalSection();
		if(u8Flag==1)
		{
			ILI9163__vClear(COLORS_u16Values[u16Color]);
			if(u16Color<COLORS_MAX)
				u16Color++;
			else
				u16Color=0;
			u8Flag=0;
			
		}
		OS__vEndCriticalSection(u8Status);	
	}
}

void Task2 (void)
{
	while(1)
	{
	}
}

void Task3 (void)
{
	while(1)
	{		
	}
}

void Task4 (void)
{
	while(1)
	{
	}
}
void Task5 (void)
{
} 
void Task6 (void)
{
	static uint8_t u8Previous=PBUTTON1_READPIN;
	static uint8_t u8Actual=PBUTTON1_READPIN;
	u8Actual=PBUTTON1_READPORT & PBUTTON1_READPIN;
	
	LEDBLUE_OUT|=LEDBLUE_PIN;
	if(u8Previous!=u8Actual)
	{
		if(u8Actual==0)
		{
			LEDBLUE_OUT&=~LEDBLUE_PIN;
			u8Flag=1;
		}
		
	}
	u8Previous=u8Actual;
}