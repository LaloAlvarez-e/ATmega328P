/*
 * ATmega328P_Timer0_NormalMode.c
 *
 * Created: 11/10/2019 12:19:43 p. m.
 * Author : Lalo
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <GPIO.h> /* Driver for GPIO*/
#include <Timer0.h> /* Driver for Timer0*/

int main(void)
{
	/*Variable use to modified phase between OC0A and OC0B*/
	uint8_t u8Phase=0;
	uint16_t u16ValueOV=0;
	uint16_t u16ValuePreviousOV=0;
	volatile uint8_t u8CountInputPCINT2=0;
	uint8_t u8CountInputINT0=0;
	/*Port Init PB5, PC4, PC5 as output and PD2, PB1 and PB1 as Input*/
	GPIO__vInitPort(); 
	/*Enable interrut in Input (PD2, BP1 and PB2)*/
	GPIO__vInitPortInterrupt();
	
	/*Set Inmediate Compare value on  OC0A*/
	Timer0__vSetCompareValue(Timer0_enModuleA,0x0);
	/*Set Inmediate Compare value on  OC0B*/
	Timer0__vSetCompareValue(Timer0_enModuleB,u8Phase);
	/* Set Mode for OC0A and OC0B as Toggle every Compare event*/
	Timer0__vSetOutputMode(Timer0_enModuleA|Timer0_enModuleB,Timer0_enCompareToggle);
	/*Pin port initialization for Timer Peripheral*/
	Timer0__vInitPin(Timer0_enModuleA|Timer0_enModuleB);
	
	/*Clear pending Interrupt of Timer Overflow*/
	Timer0__vClearInterrupt(Timer0_enInterruptTOIE);
	/*Enable Interrupt of Timer Overflow*/
	Timer0__vEnableInterrupt(Timer0_enInterruptTOIE);
	
	/*Intialization of Timer: Normal Mode and CLK div64 ~~ 1.024ms*/
	Timer0__vInit(Timer0_enModeNormal_MAX,Timer0_enClockDiv64,0);
	/*Enable Global Interrupt*/
	sei();
    while (1) 
    {
		/*Temp variables for Shared Information*/
		u16ValueOV=(uint16_t)Timer0__u16GetCounterOV();
		u8CountInputPCINT2=GPIO__u8GetCounterRisingPCINT2();
		u8CountInputINT0=GPIO__u8GetCounterRisingINT0();
		
		/*Wait until another interrupt occur in timer*/
		if(u16ValueOV!=u16ValuePreviousOV)
		{
			
			/*This task1 is executed approximately every 1ms*u8CountInputPCINT2 */
			if((u16ValueOV%(u8CountInputPCINT2+1))==0)
			{
				LEDRED_OUT^=LEDRED_PIN;
			}
			/*This task2 is executed approximately every 500ms */
			if((u16ValueOV%(uint16_t)500)==0)
			{
				LEDAMBER_OUT^=LEDAMBER_PIN;
				
			}
			/*This task3 is executed approximately every 100ms */
			if(((u16ValueOV)%(100))==0)
			{
				LEDGREEN_OUT^=LEDGREEN_PIN;
			}			
			/*This task4 is executed approximately every 10ms */
			if(((u16ValueOV)%(10))==0)
			{
				/*Task to change pahse of OC0B*/
				if(u8CountInputINT0>0)
				{
					u8Phase+=4;
					GPIO__vClearCounterRisingINT0();
					Timer0__vSetCompareValueInterrupt(Timer0_enModuleB,u8Phase);
				}
			}
		}
		u16ValuePreviousOV=u16ValueOV;
    }
}
