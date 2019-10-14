/*
 * ATmega328P_Scheduler.c
 *
 * Created: 12/10/2019 01:51:06 a. m.
 * Author : Lalo
 */ 

#include <avr/io.h>
#include <os.h>

void Task1 (void);
void Task2 (void);
void Task3 (void);
void Task4 (void);
void Task5 (void);
void Task6 (void);



int main(void)
{
	GPIO__vInitPort();
	OS__enAddPeriodicThreads(&Task5,250,&Task6,500);
	OS__enAddMainThreads(&Task1, &Task2, &Task3, &Task4);
	OS__vLaunch();
}


void Task1(void)
{	uint8_t u8Status=0;
	uint16_t u16I=0;
	while(1)
	{
		u8Status = OS__u8StartCriticalSection();
		PORTC|=(1<<PORTC3);
		for(u16I=0; u16I<1; u16I++);
		PORTC&=~(1<<PORTC3);
		for(u16I=0; u16I<1; u16I++);
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
		PORTB^=(1<<PORTB5);
	}
}
void Task5 (void)
{
	PORTC^=(1<<PORTC5);
} 
void Task6 (void)
{
	PORTC^=(1<<PORTC4);
}