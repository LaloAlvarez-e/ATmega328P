/*
 * OS.c
 *
 * Created: 12/10/2019 09:06:50 a. m.
 *  Author: Lalo
 */ 
#include "os.h"

void OS_vStartOS(void);
void OS_vScheduler(void);
void OS_vSetInitialStack(uint8_t i);


TCB_TypeDef  OS_sTCBs[NUMTHREADS];
TCB_TypeDef* OS_psRunPt;
int8_t   OS_ps8Stacks[NUMTHREADS][STACKSIZE];


uint8_t OS__u8StartCriticalSection(void)
{
	uint8_t u8State=SREG&0x80;
	cli();
	return u8State;
}

void OS__vEndCriticalSection(uint8_t u8Status)
{
	SREG|=u8Status;
}

void OS_vSetInitialStack(uint8_t i){
	OS_sTCBs[i].sp = &OS_ps8Stacks[i][STACKSIZE-36]; // thread stack pointer
	OS_ps8Stacks[i][STACKSIZE-1] = 0x01; // Thumb bit (PC counter low)
	OS_ps8Stacks[i][STACKSIZE-2] = 0x02; // Thumb bit (PC counter hight)
	OS_ps8Stacks[i][STACKSIZE-3] = 0x80; // R31
	OS_ps8Stacks[i][STACKSIZE-4] = 0x80; // SREG
	OS_ps8Stacks[i][STACKSIZE-5] = 0x05; // R30
	OS_ps8Stacks[i][STACKSIZE-6] = 0x06; // R29
	OS_ps8Stacks[i][STACKSIZE-7] = 0x07; // R28
	OS_ps8Stacks[i][STACKSIZE-8] = 0x08; // R27
	OS_ps8Stacks[i][STACKSIZE-9] = 0x09; // R26
	OS_ps8Stacks[i][STACKSIZE-10] = 0x10; // R25
	OS_ps8Stacks[i][STACKSIZE-11] = 0x11; // R24
	OS_ps8Stacks[i][STACKSIZE-12] = 0x12; // R23
	OS_ps8Stacks[i][STACKSIZE-13] = 0x13; // R22
	OS_ps8Stacks[i][STACKSIZE-14] = 0x14; // R21
	OS_ps8Stacks[i][STACKSIZE-15] = 0x15; // R20
	OS_ps8Stacks[i][STACKSIZE-16] = 0x16; // R19
	OS_ps8Stacks[i][STACKSIZE-17] = 0x17; // R18
	OS_ps8Stacks[i][STACKSIZE-18] = 0x18; // R17
	OS_ps8Stacks[i][STACKSIZE-19] = 0x19; // R16
	OS_ps8Stacks[i][STACKSIZE-20] = 0x20; // R15
	OS_ps8Stacks[i][STACKSIZE-21] = 0x21; // R14
	OS_ps8Stacks[i][STACKSIZE-22] = 0x22; // R13
	OS_ps8Stacks[i][STACKSIZE-23] = 0x23; // R12
	OS_ps8Stacks[i][STACKSIZE-24] = 0x24; // R11
	OS_ps8Stacks[i][STACKSIZE-25] = 0x25; // R10
	OS_ps8Stacks[i][STACKSIZE-26] = 0x26; // R09
	OS_ps8Stacks[i][STACKSIZE-27] = 0x27; // R08
	OS_ps8Stacks[i][STACKSIZE-28] = 0x28; // R07
	OS_ps8Stacks[i][STACKSIZE-29] = 0x29; // R06
	OS_ps8Stacks[i][STACKSIZE-30] = 0x30; // R05
	OS_ps8Stacks[i][STACKSIZE-31] = 0x31; // R04
	OS_ps8Stacks[i][STACKSIZE-32] = 0x32; // R03
	OS_ps8Stacks[i][STACKSIZE-33] = 0x33; // R02
	OS_ps8Stacks[i][STACKSIZE-34] = 0x34; // R01
	OS_ps8Stacks[i][STACKSIZE-35] = 0x35; // R00

}

void (*OS_vPeriodicTask0)(void);
void (*OS_vPeriodicTask1)(void);
uint16_t OS_u16PeriodTask0=0, OS_u16PeriodTask1=0;
uint32_t OS_u32MaxPeriod=0;
OS_nStatus OS__enAddPeriodicThreads(void(*vPeriodicTask0)(void), 
uint16_t u16PeriodTask0, void(*vPeriodicTask1)(void), uint16_t u16PeriodTask1)
{
	OS_vPeriodicTask0=vPeriodicTask0;
	OS_vPeriodicTask1=vPeriodicTask1;
	if(u16PeriodTask0!=0)
		OS_u16PeriodTask0=u16PeriodTask0;
	else
		OS_u16PeriodTask0=1;
	if(u16PeriodTask1!=0)
		OS_u16PeriodTask1=u16PeriodTask1;
	else
		OS_u16PeriodTask1=1;
		
	OS_u32MaxPeriod= (OS_u16PeriodTask0*OS_u16PeriodTask1);
	return OS_enOK;
}

OS_nStatus OS__enAddMainThreads(void(*vTask0)(void),
void(*vTask1)(void),
void(*vTask2)(void),
void(*vTask3)(void)){
	uint8_t u8Status;
	u8Status = OS__u8StartCriticalSection();
	OS_sTCBs[0].next = &OS_sTCBs[1]; // 0 points to 1
	OS_sTCBs[1].next = &OS_sTCBs[2]; // 1 points to 2
	OS_sTCBs[2].next = &OS_sTCBs[3]; // 2 points to 0
	OS_sTCBs[3].next = &OS_sTCBs[0]; // 2 points to 0

	OS_vSetInitialStack(0); 
	OS_ps8Stacks[0][STACKSIZE-1] =((int16_t)vTask0)&0xFF; // PC
	OS_ps8Stacks[0][STACKSIZE-2] = (((int16_t)vTask0)>>8)&0xFF; // PC
	OS_vSetInitialStack(1); 
	OS_ps8Stacks[1][STACKSIZE-1] =((int16_t)vTask1)&0xFF; // PC
	OS_ps8Stacks[1][STACKSIZE-2] = (((int16_t)vTask1)>>8)&0xFF; // PC
	OS_vSetInitialStack(2);
	OS_ps8Stacks[2][STACKSIZE-1] =((int16_t)vTask2)&0xFF; // PC
	OS_ps8Stacks[2][STACKSIZE-2] = (((int16_t)vTask2)>>8)&0xFF; // PC
	OS_vSetInitialStack(3);
	OS_ps8Stacks[3][STACKSIZE-1] =((int16_t)vTask3)&0xFF; // PC
	OS_ps8Stacks[3][STACKSIZE-2] = (((int16_t)vTask3)>>8)&0xFF; // PC
	OS_psRunPt = &OS_sTCBs[0];        // thread 0 will run first
	OS__vEndCriticalSection(u8Status);
	return OS_enOK; // successful
}

void OS_vScheduler(void)
{	
	static uint32_t u32Count= 0;
	u32Count%=OS_u32MaxPeriod;
	 if(((uint32_t)u32Count%(uint32_t)OS_u16PeriodTask0) == 0)
	 { 
		 OS_vPeriodicTask0();
	 }
	 if(((uint32_t)u32Count%(uint32_t)OS_u16PeriodTask1) == 0)
	 { 
		 OS_vPeriodicTask1();
	 }	
	u32Count++;
	OS_psRunPt = OS_psRunPt->next; // Round Robin scheduler
}

/* SpinLock semaphore*/

void OS__vInitSemaphore(int8_t *ps8Semaphore, SEMAPHORE_nTypeInit enInitValue)
{
	*ps8Semaphore=(int8_t)enInitValue;
}

void OS__vWaitSemaphore(int8_t *ps8Semaphore)
{
	uint8_t u8Status;
	u8Status = OS__u8StartCriticalSection();
	/*Wait until data are available*/
	while(*ps8Semaphore == 0){
	sei(); /* interrupts can occur here*/
	cli();
	}
	*ps8Semaphore = (*ps8Semaphore) - 1;
	OS__vEndCriticalSection(u8Status);
} 

void OS__vSignalSemaphore(int8_t *ps8Semaphore)
{
	uint8_t u8Status;
	u8Status = OS__u8StartCriticalSection();
	*ps8Semaphore = (*ps8Semaphore) + 1;
	OS__vEndCriticalSection(u8Status);
}



void OS__vLaunch(void){

	/*Clear pending Interrupt of Timer Overflow*/
	Timer0__vClearInterrupt(Timer0_enInterruptOCIEA);
	/*Enable Interrupt of Timer Overflow*/
	Timer0__vEnableInterrupt(Timer0_enInterruptOCIEA);
	
	/*Intialization of Timer: Normal Mode MAX and CLK div64 ~~ 1ms*/
	Timer0__vInit(Timer0_enModeNormal_OCRA,Timer0_enClockDiv64,251);

	OS_vStartOS();                   // start on the first task
}

void OS_vStartOS(void)
{
	asm volatile (
	"LDS 	 ZL, OS_psRunPt ; Initialize Yh pointer with OS_psRunPt \n\t"
	"LDS 	 ZH, OS_psRunPt+1 ;\n\t"
	"LD  	 r0,Z+  ; Save new Stack Pointer \n\t"
	"LD		 r1,Z ;  \n\t"
	"OUT     __SP_L__, r0  ;Save SP into R0 and R1\n\t "
	"OUT     __SP_H__, r1  \n\t "
	"POP    r0\n\t "
	"POP    r1\n\t "
	"POP    r2\n\t "
	"POP    r3\n\t "
	"POP    r4\n\t "
	"POP    r5\n\t "
	"POP    r6\n\t "
	"POP    r7\n\t "
	"POP    r8\n\t "
	"POP    r9\n\t "
	"POP    r10\n\t "
	"POP    r11\n\t "
	"POP    r12\n\t "
	"POP    r13\n\t "
	"POP    r14\n\t "
	"POP    r15\n\t "
	"POP    r16\n\t "
	"POP    r17\n\t "
	"POP    r18\n\t "
	"POP    r19\n\t "
	"POP    r20\n\t "
	"POP    r21\n\t "
	"POP    r22\n\t "
	"POP    r23\n\t "
	"POP    r24\n\t "
	"POP    r25\n\t "
	"POP    r26\n\t "
	"POP    r27\n\t "
	"POP    r28\n\t "
	"POP    r29\n\t "
	"POP    r30\n\t "
	"POP    r31\n\t "
	"OUT    __SREG__,r31 ;\n\t "
	"POP    r31\n\t "
	);
}





// Task switching, ISR_NAKED is necessary to prevent compiler to manipulate the stack
ISR(TIMER0_COMPA_vect, ISR_NAKED) //1) Saves PC
{
	asm volatile (
	"PUSH    r31 ;\n\t "
	"IN     r31,__SREG__ ;\n\t "
	"PUSH    r31 ;\n\t "
	"PUSH    r30 ;\n\t "
	"PUSH    r29 \n\t "
	"PUSH    r28 ;\n\t "
	"PUSH    r27 ;\n\t "
	"PUSH    r26 ;\n\t "
	"PUSH    r25 ;\n\t "
	"PUSH    r24 ;\n\t "
	"PUSH    r23 ;\n\t "
	"PUSH    r22 ;\n\t "
	"PUSH    r21 ;\n\t "
	"PUSH    r20 ;\n\t "
	"PUSH    r19 ;\n\t "
	"PUSH    r18 ;\n\t "
	"PUSH    r17 ;\n\t "
	"PUSH    r16 ;\n\t "
	"PUSH    r15 ;\n\t "
	"PUSH    r14 ;\n\t "
	"PUSH    r13 ;\n\t "
	"PUSH    r12 ;\n\t "
	"PUSH    r11\n\t "
	"PUSH    r10\n\t "
	"PUSH    r9\n\t "
	"PUSH    r8\n\t "
	"PUSH    r7\n\t "
	"PUSH    r6\n\t "
	"PUSH    r5\n\t "
	"PUSH    r4\n\t "
	"PUSH    r3\n\t "
	"PUSH    r2\n\t "
	"PUSH    r1\n\t "
	"PUSH    r0\n\t "
	
	"IN      r0, __SP_L__ ;Save SP into R0 and R1\n\t "
	"IN      r1, __SP_H__ \n\t "
	"LDS 	 ZL, OS_psRunPt ; Initialize Yh pointer with OS_psRunPt \n\t"
	"LDS 	 ZH, OS_psRunPt+1 ;\n\t"
	"ST		 Z+,r0 ; Save new Stack Pointer \n\t"
	"ST		 Z,r1 ;  \n\t"
	
	"CALL   OS_vScheduler ; \n\t"
	
	"LDS 	 ZL, OS_psRunPt ; Initialize Yh pointer with OS_psRunPt \n\t"
	"LDS 	 ZH, OS_psRunPt+1 ;\n\t"
	
	"LD		 r0,Z+ ; \n\t"
	"LD		 r1,Z ; \n\t"
	"OUT	 __SP_L__, r0 ; \n\t"
	"OUT	 __SP_H__, r1 ; \n\t"
	
	"POP    r0\n\t "
	"POP    r1\n\t "
	"POP    r2\n\t "
	"POP    r3\n\t "
	"POP    r4\n\t "
	"POP    r5\n\t "
	"POP    r6\n\t "
	"POP    r7\n\t "
	"POP    r8\n\t "
	"POP    r9\n\t "
	"POP    r10\n\t "
	"POP    r11\n\t "
	"POP    r12\n\t "
	"POP    r13\n\t "
	"POP    r14\n\t "
	"POP    r15\n\t "
	"POP    r16\n\t "
	"POP    r17\n\t "
	"POP    r18\n\t "
	"POP    r19\n\t "
	"POP    r20\n\t "
	"POP    r21\n\t "
	"POP    r22\n\t "
	"POP    r23\n\t "
	"POP    r24\n\t "
	"POP    r25\n\t "
	"POP    r26\n\t "
	"POP    r27\n\t "
	"POP    r28\n\t "
	"POP    r29\n\t "
	"POP    r30\n\t "
	"POP    r31\n\t "
	"OUT    __SREG__,r31 \n\t "
	"POP    r31 \n\t "
	"RETI  \n\t"
	);
}