/*
 * OS.h
 *
 * Created: 12/10/2019 01:54:22 a. m.
 *  Author: Lalo
 */ 


#ifndef OS_H_
#define OS_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <Timer0.h>

#define NUMTHREADS  (4)        // maximum number of threads
#define STACKSIZE   (0x100)      // number of 8-bit words in stack per thread

struct TCB{ //Thread control block
	int8_t *sp;       // pointer to stack (valid for threads not running)
	struct TCB *next;  // linked-list pointer
};
typedef struct TCB TCB_TypeDef;

typedef enum
{
	OS_enOK  =0,
	OS_enERROR,
}OS_nStatus;


void OS__vLaunch(void);
OS_nStatus OS__enAddMainThreads(void(*vTask0)(void),
void(*vTask1)(void),
void(*vTask2)(void),
void(*vTask3)(void));
OS_nStatus OS__enAddPeriodicThreads(void(*vPeriodicTask0)(void), 
uint16_t u16PeriodTask0,
void(*vPeriodicTask1)(void), 
uint16_t u16PeriodTask1);


uint8_t OS__u8StartCriticalSection(void);
void OS__vEndCriticalSection(uint8_t u8Status);


#endif /* OS_H_ */