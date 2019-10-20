/*
 * ATmega328P_Scheduler.c
 *
 * Created: 12/10/2019 01:51:06 a. m.
 * Author : Lalo
 */ 

#include <avr/io.h>
#include <os.h>
#include <ILI9163.h>
#include <NOKIA5110.h>
#include <Colors.h>

void Task1 (void);
void Task2 (void);
void Task3 (void);
void Task4 (void);
void Task5 (void);
void Task6 (void);

int8_t MAIN_s8SemaphoreSPI=0;
uint8_t MAIN_u8CountBUTTON1=0;
uint8_t MAIN_u8CountBUTTON2=0;

int main(void)
{
	uint8_t u8Column=0, u8Row=0;
	GPIO__vInitPort();
	NOKIA5110__vInit();
	NOKIA5110__vSetCursor(0,0);
	NOKIA5110__vClear();
	NOKIA5110__u16Print("InDev Mutex\n\rBoton 1:\n\rBoton 2:",&u8Column,&u8Row);
	OS__vInitSemaphore(&MAIN_s8SemaphoreSPI,SEMAPHORE_enInitMUTEX);
	OS__enAddPeriodicThreads(&Task5,250,&Task6,100);
	OS__enAddMainThreads(&Task1, &Task2);
	OS__vLaunch();
}
void Task1(void)
{
	char TASK1_cConv[10]="Hola";
	uint8_t u8Column=9, u8Row=1,u8Status=0;
	uint16_t u16ValueBoton=0;
	uint16_t i=0;

	while(1)
	{
		u8Status=OS__u8StartCriticalSection();
		u16ValueBoton=MAIN_u8CountBUTTON1;
		OS__vEndCriticalSection(u8Status);
		u8Column=9;
		u8Row=1;
		//CONV__u8UIntToString(10,&TASK1_cConv[0]);
		OS__vWaitSemaphore(&MAIN_s8SemaphoreSPI);
		NOKIA5110__u8SendString((char*)TASK1_cConv,&u8Column,&u8Row);
		LEDGREEN_OUT^=LEDGREEN_PIN;
		OS__vSignalSemaphore(&MAIN_s8SemaphoreSPI);
		for(i=0;i<50000ul;i++);
		for(i=0;i<50000ul;i++);
		
	}
}

void Task2 (void)
{
	char TASK1_cConv[10];
	uint8_t u8Column=9, u8Row=2,u8Status=0;
	uint16_t u16ValueBoton=0;
	uint16_t i=0;

	while(1)
	{
		u8Status=OS__u8StartCriticalSection();
		u16ValueBoton=MAIN_u8CountBUTTON2;
		OS__vEndCriticalSection(u8Status);
		u8Column=9;
		u8Row=2;
		CONV__u8UIntToString(10,&TASK1_cConv[0]);
		OS__vWaitSemaphore(&MAIN_s8SemaphoreSPI);
		LEDRED_OUT^=LEDRED_PIN;
		NOKIA5110__vSetCursorChar(u8Column,u8Row);
		NOKIA5110__vSendChar((char)'O');
		OS__vSignalSemaphore(&MAIN_s8SemaphoreSPI);
		for(i=0;i<50000ul;i++);
		for(i=0;i<50000ul;i++);
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
	static uint8_t u8Previous=PBUTTON2_READPIN;
	static uint8_t u8Actual=PBUTTON2_READPIN;
	u8Actual=PBUTTON2_READPORT & PBUTTON2_READPIN;
	
	LEDAMBER_OUT|=LEDAMBER_PIN;
	if(u8Previous!=u8Actual)
	{
		if(u8Actual==0)
		{
			LEDAMBER_OUT&=~LEDAMBER_PIN;
			//MAIN_u8CountBUTTON2++;
		}
		
	}
	u8Previous=u8Actual;
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
			MAIN_u8CountBUTTON1++;
		}
		
	}
	u8Previous=u8Actual;
}