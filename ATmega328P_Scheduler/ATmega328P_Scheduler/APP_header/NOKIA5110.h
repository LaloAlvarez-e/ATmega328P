/*
 * NOKIA5110.h
 *
 *  Created on: 15 mar. 2018
 *      Author: InDev
 */

#ifndef NOKIA5110_H_
#define NOKIA5110_H_

#include <avr/io.h>
#include <os.h>
#include <stdarg.h>
#include <SPI.h>
#include <CONV.h>

#define NOKIA5110_WIDTHTOTAL	(84u)
#define NOKIA5110_HEIGHTTOTAL	(48u)

#define NOKIA5110_DC_PIN	(1<<PORTF0)
#define NOKIA5110_DC_DIR	(DDRF)
#define NOKIA5110_DC_OUT	(PORTF)


#define NOKIA5110_DC_COMMAND()	NOKIA5110_DC_OUT&=~NOKIA5110_DC_PIN
#define NOKIA5110_DC_DATA()		NOKIA5110_DC_OUT|=NOKIA5110_DC_PIN


#define NOKIA5110_MAX_X 84
#define NOKIA5110_MAX_Y 48

#define NOKIA5110_COLUMN_SIZE 12
#define NOKIA5110_ROW_SIZE 6
#define NOKIA5110_TAB_SIZE 3

typedef enum
{
	NOKIA5110_enOK   =0,
	NOKIA5110_enERROR  =1,
}NOKIA5110_nStatus;

void NOKIA5110__vInit(void);
void NOKIA5110__vSendCommand(uint8_t u8Data);
void NOKIA5110__vSendMultipleData(uint8_t* u8Data, uint16_t u16Cant);
void NOKIA5110__vSendMultipleCommand(uint8_t* u8Command, uint16_t u16Cant);
void NOKIA5110__vSendData(uint8_t u8Data);
void NOKIA5110__vSendChar(uint8_t u8Ascii);
void NOKIA5110__vSetCursorChar(uint8_t u8X, uint8_t u8Y);
void NOKIA5110__vSetCursor(uint8_t u8X, uint8_t u8Y);
uint8_t NOKIA5110__u8SendString(char* cString,uint8_t* u8Column, uint8_t* u8Row);
uint8_t NOKIA5110__u8SendStringSection(char* cString,uint8_t* u8Column, uint8_t* u8Row, uint8_t u8X1,uint8_t u8X2,uint8_t u8Y1,uint8_t u8Y2);

void NOKIA5110__vClear(void);
void NOKIA5110__vClearSectionPixel(uint8_t u8X1,uint8_t u8X2,uint8_t u8Y1,uint8_t u8Y2);
void NOKIA5110__vClearSectionChar(uint8_t u8X1,uint8_t u8X2,uint8_t u8Y1,uint8_t u8Y2);


uint16_t NOKIA5110__u16Print(char* cString,uint8_t* u8Column, uint8_t* u8Row);
uint16_t NOKIA5110__u16PrintSection(char* cString,uint8_t* u8Column, uint8_t* u8Row, uint8_t u8X1, uint8_t u8X2, uint8_t u8Y1, uint8_t u8Y2);


uint16_t NOKIA5110__u16Printf(char* cString,uint8_t* u8Column,uint8_t* u8Row,...);
//unsigned long long NOKIA5110_PrintfSection(char* string,unsigned char* column,unsigned char* row,unsigned char X1,unsigned char X2,unsigned char Y1,unsigned char Y2,...);

//int NOKIA5110_BMPBinary(const unsigned char *ptr);


void NOKIA5110__vPrintBuffer(void);
void NOKIA5110__vPrintImage( uint8_t *pu8Image);
void NOKIA5110__vClearBuffer(void);
void NOKIA5110__vFillBuffer(uint8_t *pu8Image);


#endif /* NOKIA5110_H_ */
