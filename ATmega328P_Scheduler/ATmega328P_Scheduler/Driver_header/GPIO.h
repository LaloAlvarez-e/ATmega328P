/*
 * GPIO.h
 *
 * Created: 11/10/2019 12:27:10 p. m.
 *  Author: Lalo
 */ 


#ifndef GPIO_H_
#define GPIO_H_



#include <avr/io.h>
#include <avr/interrupt.h>

#define LEDRED_PIN	(1<<PORTB5)
#define LEDRED_DIR	(DDRB)
#define LEDRED_OUT	(PORTB)

#define LEDGREEN_PIN	(1<<PORTC4)
#define LEDGREEN_DIR	(DDRC)
#define LEDGREEN_OUT	(PORTC)

#define LEDAMBER_PIN	(1<<PORTC5)
#define LEDAMBER_DIR	(DDRC)
#define LEDAMBER_OUT	(PORTC)

#define LEDBLUE_PIN	(1<<PORTC3)
#define LEDBLUE_DIR	(DDRC)
#define LEDBLUE_OUT	(PORTC)

#define PBUTTON1_READPIN	(1<<PIND2)
#define PBUTTON1_READPORT	(PIND)
#define PBUTTON1_DIR		(DDRD)
#define PBUTTON1_PULLUP		(PORTD)

#define PBUTTON2_READPIN	(1<<PINB2)
#define PBUTTON2_READPORT	(PINB)
#define PBUTTON2_DIR		(DDRB)
#define PBUTTON2_PULLUP		(PORTB)

#define PBUTTON3_READPIN	(1<<PINB1)
#define PBUTTON3_READPORT	(PINB)
#define PBUTTON3_DIR		(DDRB)
#define PBUTTON3_PULLUP		(PORTB)

typedef enum
{
	PBUTTON1_enPRESS = 0,
	PBUTTON1_enRELEASE = PBUTTON1_READPIN,
	
}PBUTTON1_nState;

typedef enum
{
	PBUTTON2_enPRESS = 0,
	PBUTTON2_enRELEASE = PBUTTON2_READPIN,
	
}PBUTTON2_nState;

typedef enum
{
	PBUTTON3_enPRESS = 0,
	PBUTTON3_enRELEASE = PBUTTON3_READPIN,
	
}PBUTTON3_nState;

#define PBUTTON1_READSTATE  (PBUTTON1_READPORT & PBUTTON1_READPIN)
#define PBUTTON2_READSTATE  (PBUTTON2_READPORT & PBUTTON2_READPIN)
#define PBUTTON3_READSTATE  (PBUTTON3_READPORT & PBUTTON3_READPIN)

void GPIO__vInitPort(void);
void GPIO__vInitPortInterrupt(void);

void GPIO__vClearCounterRisingPCINT2(void);
void GPIO__vSetCounterRisingPCINT2(uint8_t u8Value);
uint8_t GPIO__u8GetCounterRisingPCINT2(void);

void GPIO__vClearCounterRisingINT0(void);
void GPIO__vSetCounterRisingINT0(uint8_t u8Value);
uint8_t GPIO__u8GetCounterRisingINT0(void);

#endif /* GPIO_H_ */