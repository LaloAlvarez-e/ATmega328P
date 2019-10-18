/*
 * ILI9163.h
 *
 * Created: 17/10/2019 01:50:15 a. m.
 *  Author: Lalo
 */ 


#ifndef ILI9163_H_
#define ILI9163_H_

#include <avr/io.h>
#include <os.h>
#include <SPI.h>

#define ILI9163_WIDTHTOTAL	(128u)
#define ILI9163_HEIGHTTOTAL	(128u)

#define ILI9163_DC_PIN	(1<<PORTB1)
#define ILI9163_DC_DIR	(DDRB)
#define ILI9163_DC_OUT	(PORTB)

#define ILI9163_DC_COMMAND()	ILI9163_DC_OUT&=~ILI9163_DC_PIN
#define ILI9163_DC_DATA()		ILI9163_DC_OUT|=ILI9163_DC_PIN


void ILI9163__vInit(void);
void ILI9163__vSendCommandData(uint8_t u8Command,uint8_t* pu8DataOut,uint8_t u8CountData);
void ILI9163__vSendCommandList (const uint8_t *pu8Addr);

void ILI9163__vClear(uint16_t u16Color);
#endif /* ILI9163_H_ */