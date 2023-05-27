/*
 * ATmega328P_startup.h
 *
 * Created: 27/5/2022 23:07:45
 *  Author: InDeviceMex
 */ 


#ifndef ATMEGA328P_STARTUP_H_
#define ATMEGA328P_STARTUP_H_

#include <avr/interrupt.h>

typedef void (*interrupt_handler_t)(void);
typedef struct {
	uint16_t interrupt_instruction;
	interrupt_handler_t interrupt_handler;
}interrupt_vector;


__attribute__((section(".vec")))
extern interrupt_vector const _vectab[25U];

#endif /* ATMEGA328P_STARTUP_H_ */