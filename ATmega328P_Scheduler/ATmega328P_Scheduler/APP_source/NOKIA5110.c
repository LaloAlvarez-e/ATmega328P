/*
 * NOKIA5110.c
 *
 *  Created on: 15 mar. 2018
 *      Author: InDev
 */



//cada envio de datos son  bits que se  acomodan en las siuientes 8 filas,(6*8)
//luego se pasa automaticmente a la siguiente columna (12*7)

#include <NOKIA5110.h>

uint8_t NOKIA5110_u8ImageBuffer[NOKIA5110_MAX_X*(NOKIA5110_MAX_Y/8)];
static const uint8_t NOKIA5110_u8ASCII[96][5] = {
  {0x00, 0x00, 0x00, 0x00, 0x00} // 20
  ,{0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
  ,{0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
  ,{0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
  ,{0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
  ,{0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
  ,{0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
  ,{0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
  ,{0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
  ,{0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
  ,{0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
  ,{0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
  ,{0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
  ,{0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
  ,{0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
  ,{0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
  ,{0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
  ,{0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
  ,{0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
  ,{0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
  ,{0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
  ,{0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
  ,{0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
  ,{0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
  ,{0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
  ,{0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
  ,{0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
  ,{0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
  ,{0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
  ,{0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
  ,{0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
  ,{0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
  ,{0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
  ,{0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
  ,{0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
  ,{0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
  ,{0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
  ,{0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
  ,{0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
  ,{0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
  ,{0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
  ,{0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
  ,{0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
  ,{0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
  ,{0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
  ,{0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
  ,{0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
  ,{0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
  ,{0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
  ,{0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
  ,{0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
  ,{0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
  ,{0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
  ,{0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
  ,{0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
  ,{0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
  ,{0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
  ,{0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
  ,{0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
  ,{0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
  ,{0x02, 0x04, 0x08, 0x10, 0x20} // 5c '\'
  ,{0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
  ,{0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
  ,{0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
  ,{0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
  ,{0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
  ,{0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
  ,{0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
  ,{0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
  ,{0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
  ,{0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
  ,{0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
  ,{0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
  ,{0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
  ,{0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
  ,{0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
  ,{0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
  ,{0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
  ,{0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
  ,{0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
  ,{0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
  ,{0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
  ,{0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
  ,{0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
  ,{0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
  ,{0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
  ,{0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
  ,{0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
  ,{0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
  ,{0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
  ,{0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
  ,{0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
  ,{0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
  ,{0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
  ,{0x10, 0x08, 0x08, 0x10, 0x08} // 7e ~
//  ,{0x78, 0x46, 0x41, 0x46, 0x78} // 7f DEL
  ,{0x1f, 0x24, 0x7c, 0x24, 0x1f} // 7f UT sign
};

void NOKIA5110__vInit(void)
{
	uint32_t u32Delay=0;
	NOKIA5110_DC_DIR|=NOKIA5110_DC_PIN;
	NOKIA5110_DC_OUT&=~NOKIA5110_DC_PIN;

	SPI__vInit(SPI_enModeMaster, SPI_enMSBFirst,SPI_enClockIdleLow,SPI_enClockSampleFirst,SPI_enClockDiv2);
	SPI__vInitPin(SPI_enPinCLK|SPI_enPinSS|SPI_enPinMOSI|SPI_enPinMISO);
	for(u32Delay=0; u32Delay<0x5FFFF; u32Delay++);
    NOKIA5110__vSendCommand(0x21);
    NOKIA5110__vSendCommand(0xB0);
    NOKIA5110__vSendCommand(0x04);
    NOKIA5110__vSendCommand(0x14);
    NOKIA5110__vSendCommand(0x20);
    NOKIA5110__vSendCommand(0x0C);

}


void NOKIA5110__vSendCommand(uint8_t u8Data)
{
	volatile uint8_t u8DataTemp=u8Data;
	NOKIA5110_DC_COMMAND();
	SPI__vSendDataMaster(( uint8_t*)&u8DataTemp,1);
}

void NOKIA5110__vSendData(uint8_t u8Data)
{
	volatile uint8_t u8DataTemp=u8Data;
	NOKIA5110_DC_DATA();
	SPI__vSendDataMaster(( uint8_t*)&u8DataTemp,1);
}

void NOKIA5110__vSendMultipleData(uint8_t* u8Data, uint16_t u16Cant)
{
	NOKIA5110_DC_DATA();
	SPI__vSendDataMaster(u8Data,u16Cant);
}

void NOKIA5110__vSendMultipleCommand(uint8_t* u8Command, uint16_t u16Cant)
{
	NOKIA5110_DC_COMMAND();
	SPI__vSendDataMaster(u8Command,u16Cant);
}
void NOKIA5110__vSendChar(uint8_t u8Ascii)
{
  int8_t s8Value=u8Ascii - 0x20;
  if(s8Value<0)
	return;
   
   NOKIA5110__vSendData(0);
   NOKIA5110__vSendData(NOKIA5110_u8ASCII[s8Value][0]);
   NOKIA5110__vSendData(NOKIA5110_u8ASCII[s8Value][1]);
   NOKIA5110__vSendData(NOKIA5110_u8ASCII[s8Value][2]);
   NOKIA5110__vSendData(NOKIA5110_u8ASCII[s8Value][3]);
   NOKIA5110__vSendData(NOKIA5110_u8ASCII[s8Value][4]);
   NOKIA5110__vSendData(0);
}



void NOKIA5110__vSetCursorChar(uint8_t u8X, uint8_t u8Y)
{
	if(u8X > (NOKIA5110_COLUMN_SIZE-1))
		u8X=0;
	if(u8Y > (NOKIA5110_ROW_SIZE-1))
		u8Y=0;
	
	NOKIA5110__vSendCommand(0x80|(u8X*7));
	NOKIA5110__vSendCommand(0x40|u8Y);
}


void NOKIA5110__vSetCursor(uint8_t u8X, uint8_t u8Y)
{
	if(u8X > (NOKIA5110_MAX_X-1))
	u8X=0;
	if(u8Y > (NOKIA5110_ROW_SIZE-1))
	u8Y=0;
	
	NOKIA5110__vSendCommand(0x80|(u8X));
	NOKIA5110__vSendCommand(0x40|u8Y);
}

uint8_t NOKIA5110__u8SendString(char* cString,uint8_t* u8Column, uint8_t* u8Row)
{
    uint8_t u8Count=0;
	char* cStringTemp=cString;
	uint8_t* u8ColumnTemp=u8Column;
	uint8_t* u8RowTemp=u8Row;
    if(((uint8_t)(*u8ColumnTemp)&0xF)>(uint8_t)(NOKIA5110_COLUMN_SIZE-1))
    {
        *u8ColumnTemp=0;
    }
    else
    {
        (*u8ColumnTemp)&=0xF;
    }
	
    if((uint8_t)(*u8RowTemp)>(uint8_t)(NOKIA5110_ROW_SIZE-1))
        *u8RowTemp=0;
		
    NOKIA5110__vSetCursorChar((uint8_t)(*u8ColumnTemp),(uint8_t)(*u8RowTemp));
    while((char)(*cStringTemp)!=0)
    {
        NOKIA5110__vSendChar((char)(*(cStringTemp))); //envia el caracter correspondiente
        (*u8ColumnTemp)++; //suma 1 a la column indicando que se ha escrito un valor
        if((*u8ColumnTemp&0xF)>(NOKIA5110_COLUMN_SIZE-1)) //si la column es 0 indica que empieza una nueva row
        {
            (*u8ColumnTemp)=0;
            (*u8RowTemp)++; //invierte el valor e row para que se reinciie
            if(((uint8_t)((*u8RowTemp)&0x7))>(uint8_t)(NOKIA5110_ROW_SIZE-1))
                (*u8RowTemp)=0;
            NOKIA5110__vSetCursorChar((uint8_t)(*u8ColumnTemp),(uint8_t)(*u8RowTemp)); //pone el cursor en 0,x
        }
        cStringTemp++; //el puntero apunta al siguiente caracter
        u8Count++; //suma 1 al count total de caracter enviados a la LCD
    }
    return u8Count;
}


uint8_t NOKIA5110__u8SendStringSection(char* cString,uint8_t* u8Column, uint8_t* u8Row, uint8_t u8X1,uint8_t u8X2,uint8_t u8Y1,uint8_t u8Y2)
{
	uint8_t u8Count=0;
    NOKIA5110__vSetCursorChar(*u8Column,*u8Row);
    while(*cString)
    {
        NOKIA5110__vSendChar(*(cString)); //envia el caracter correspondiente
        (*u8Column)++; //suma 1 a la column indicando que se ha escrito un valor
        if((*u8Column)>(u8X2)) //si la column es 0 indica que empieza una nueva row
        {
            (*u8Column)=u8X1;
            (*u8Row)++; //invierte el valor e row para que se reinciie
            if((*u8Row)>(u8Y2))
                (*u8Row)=u8Y1;
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //pone el cursor en 0,x
        }
        cString++; //el puntero apunta al siguiente caracter
        u8Count++; //suma 1 al count total de caracter enviados a la LCD
    }
    return u8Count;
}



uint16_t NOKIA5110__u16Print(char* cString,uint8_t* u8Column, uint8_t* u8Row)
{
    uint16_t u16Count=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    uint8_t  u8Exit=0; //variable que funciona cuanod encuentra un ESC
    uint16_t u16Delay; //utilizada para los comandos como clear y home
    if(((*u8Column)&0xF)>(NOKIA5110_COLUMN_SIZE-1))
    {
        *u8Column=0;
    }
    else
    {
        (*u8Column)&=0xF;
    }
    if(*u8Row>(NOKIA5110_ROW_SIZE-1))
        *u8Row=0;
		
    NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //indica la posicion inicial del cursor
    while(*cString)// realiza el ciclo mientras la cString tenga algun valor
           //el valor 0 o '\0' es fin de cString
    {
        switch (*cString) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*u8Row)++; //aumenta la u8Row
            if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                *u8Row=0;
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\r': //retorno de carro
            *u8Column=0; //actualiza el valor de la u8Column a la primera posicion
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*u8Column)&0xF)<(NOKIA5110_COLUMN_SIZE-NOKIA5110_TAB_SIZE))
                *u8Column+=NOKIA5110_TAB_SIZE; //aumenta 3 espacios vacios
            else
            {
                *u8Column=0; // pasa a la siguiente u8Row si no cabe la tabulacion
                (*u8Row)++; //aumenta la u8Row
                if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                    *u8Row=0;
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
         case '\b': //retroceso
            if(((*u8Column)!=0) || ((*u8Row)!=0)) //si la u8Column y u8Row es diferente a 0 puede retroceder
            {
                if(((*u8Column)!=0)) //si la u8Column encuentra entre 1 y 15 puede disminuir uno
                    (*u8Column)--;
                else
                    if(((*u8Row)!=0)) //si la u8Column es 0 entonces checa si existen rows que disminuir
                    {
                        (*u8Column)=NOKIA5110_COLUMN_SIZE-1;
                        (*u8Row)--;
                    }
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*u8Column)!=0) || ((*u8Row)!=0)) //si la u8Column es diferente a 0 puede retroceder
            {
                if(((*u8Column)!=0))
                    (*u8Column)--;
                else
                    if(((*u8Row)!=0))
                    {
                        (*u8Column)=NOKIA5110_COLUMN_SIZE-1;
                        (*u8Row)--;
                    }
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            NOKIA5110__vSendChar(' ');//borra el caracter que pudiera haber en la posicion
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\e': //escape
            u8Exit=1;//indica que se necesita u8Exit de la funcion
            break;
        case '\f': //nueva pagina
            *u8Column=*u8Row=0;//reinicia los valores
            NOKIA5110__vClear(); //limpia la pantalla
            for(u16Delay=3000; u16Delay>0; u16Delay--);//1.60 ms aprox a 16MHz
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion a 0,0
            break;
        default :
            NOKIA5110__vSendChar(*(cString)); //envia el caracter correspondiente
            (*u8Column)++; //suma 1 a la u8Column indicando que se ha escrito un valor
            if(((*u8Column)&0xF)>(NOKIA5110_COLUMN_SIZE-1)) //si la u8Column es 0 indica que empieza una nueva u8Row
            {
                (*u8Column)=0;
                (*u8Row)++; //aumenta la u8Row
                if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                    *u8Row=0;
                NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //pone el cursor en 0,x
            }
            break;
        }
        cString++; //el puntero apunta al siguiente caracter
        u16Count++; //suma 1 al u16Count total de caracter enviados a la LCD
        if(u8Exit) //si detecto un \e (escape) sale del ciclo while
            break;
    }
     return u16Count; //regresa el u16Count de caracteres y caracteres especiales
}




uint16_t NOKIA5110__u16PrintSection(char* cString,uint8_t* u8Column, uint8_t* u8Row, uint8_t u8X1, uint8_t u8X2, uint8_t u8Y1, uint8_t u8Y2)
{
    uint16_t u16Count=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    uint8_t u8Exit=0; //variable que funciona cuanod encuentra un ESC
    uint32_t u32Delay; //utilizada para los comandos como clear y home
    uint8_t u8Temp=0;

    if((u8X1>(NOKIA5110_MAX_X/7)-1) || (u8X2>(NOKIA5110_MAX_X/7)-1) || (u8Y1>(NOKIA5110_MAX_Y/8)-1) || (u8Y2>(NOKIA5110_MAX_Y/8)-1)   )
         return 0;


    if(u8X1>u8X2)
    {
        u8Temp=u8X1;
        u8X1=u8X2;
        u8X2=u8Temp;
    }
    if(u8Y1>u8Y2)
    {
        u8Temp=u8Y1;
        u8Y1=u8Y2;
        u8Y2=u8Temp;
    }

    *u8Column+=u8X1;
    *u8Row+=u8Y1;
    if((*u8Column)>(u8X2))
    {
        (*u8Column)=u8X1;
    }
    else
    {
        (*u8Column)&=0xF;
    }
    if(*u8Row>(u8Y2))
        (*u8Row)=u8Y1;
    NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //indica la posicion inicial del cursor
    while(*cString)// realiza el ciclo mientras la cString tenga algun valor
           //el valor 0 o '\0' es fin de cString
    {
        switch (*cString) //detecta si existe un caracter especial
        {
        case '\n': //salto de linea
            (*u8Row)++; //aumenta la u8Row
            if(*u8Row>(u8Y2))
                (*u8Row)=u8Y1;
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\r': //retorno de carro
            (*u8Column)=u8X1; //actualiza el valor de la u8Column a la primera posicion
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*u8Column)&0xF)<(u8X2-NOKIA5110_TAB_SIZE))
                *u8Column+=NOKIA5110_TAB_SIZE; //aumenta 3 espacios vacios
            else
            {
                (*u8Column)=u8X1; // pasa a la siguiente u8Row si no cabe la tabulacion
                (*u8Row)++; //aumenta la u8Row
                if(*u8Row>(u8Y2))
                    (*u8Row)=u8Y1;
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
         case '\b': //retroceso
            if(((*u8Column)!=u8X1) || ((*u8Row)!=u8Y1)) //si la u8Column y u8Row es diferente a 0 puede retroceder
            {
                if(((*u8Column)!=u8X1)) //si la u8Column encuentra entre 1 y 15 puede disminuir uno
                    (*u8Column)--;
                else
                    if(((*u8Row)!=u8Y1)) //si la u8Column es 0 entonces checa si existen u8Rows que disminuir
                    {
                        (*u8Column)=u8X2;
                        (*u8Row)--;
                    }
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*u8Column)!=u8X1) || ((*u8Row)!=u8X1)) //si la u8Column es diferente a 0 puede retroceder
            {
                if(((*u8Column)!=u8X1))
                    (*u8Column)--;
                else
                    if(((*u8Row)!=u8X1))
                    {
                        (*u8Column)=u8Y2;
                        (*u8Row)--;
                    }
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            NOKIA5110__vSendChar(' ');//borra el caracter que pudiera haber en la posicion
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\e': //escape
            u8Exit=1;//indica que se necesita u8Exit de la funcion
            break;
        case '\f': //nueva pagina
            *u8Column=u8X1;
            (*u8Row)=u8Y1;//reinicia los valores
            NOKIA5110__vClearSectionChar(u8X1,u8X2,u8Y1,u8Y2);
            for(u32Delay=3000; u32Delay>0; u32Delay--);//1.60 ms aprox a 16MHz
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion a 0,0
            break;
        default :
            NOKIA5110__vSendChar(*(cString)); //envia el caracter correspondiente
            (*u8Column)++; //suma 1 a la u8Column indicando que se ha escrito un valor
            if(((*u8Column)&0xF)>(u8X2)) //si la u8Column es 0 indica que empieza una nueva u8Row
            {
                (*u8Column)=u8X1;
                (*u8Row)++; //aumenta la u8Row
                if(*u8Row>(u8Y2))
                    (*u8Row)=u8Y1;
                NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //pone el cursor en 0,x
            }
            break;
        }
        cString++; //el puntero apunta al siguiente caracter
        u16Count++; //suma 1 al u16Count total de caracter enviados a la LCD
        if(u8Exit) //si detecto un \e (escape) sale del ciclo while
            break;
    }
     return u16Count; //regresa el u16Count de caracteres y caracteres especiales
}





uint16_t NOKIA5110__u16Printf(char* cString,uint8_t* u8Column,uint8_t* u8Row,...)
{
    uint16_t u16Count=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    uint8_t u8Exit=0;
    uint32_t u32Delay;


    va_list ap; //crea puntero de los argumentos
    double valueARGd; //variable donde guardara el valor del argumento
    char* valueARGc; //variable donde guardara el valor del argumento
    int32_t valueARGi; //variable donde guardara el valor del argumento
    int64_t valueARGii; //variable donde guardara el valor del argumento
    uint64_t valueARGuu; //variable donde guardara el valor del argumento
    void* valueARGcl; //variable donde guardara el valor del argumento
    char conversion[30];
    va_start(ap, u8Row);//maneja la memoria de los argumentos empezando desde el ultimo conocido ingresado

    if(((*u8Column)&0xF)>(NOKIA5110_COLUMN_SIZE-1))
    {
        *u8Column=0;
    }
    else
    {
        (*u8Column)&=0xF;
    }

    if(*u8Row>(NOKIA5110_ROW_SIZE-1))
            *u8Row=0;

    NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //indica la posicion inicial del cursor

    while(*cString)// realiza el ciclo mientras la cString tenga algun valor
    {
        switch (*cString) //detecta si existe un caracter especial
        {


        case '\n': //salto de linea
            (*u8Row)++; //aumenta la u8Row
            if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                *u8Row=0;
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\r': //retorno de carro
            *u8Column=0; //actualiza el valor de la u8Column a la primera posicion
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if(((*u8Column)&0xF)<(NOKIA5110_COLUMN_SIZE-NOKIA5110_TAB_SIZE))
                *u8Column+=NOKIA5110_TAB_SIZE; //aumenta 3 espacios vacios
            else
            {
                *u8Column=0; // pasa a la siguiente u8Row si no cabe la tabulacion
                (*u8Row)++; //aumenta la u8Row
                if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                    *u8Row=0;
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
         case '\b': //retroceso
            if(((*u8Column)!=0) || ((*u8Row)!=0)) //si la u8Column y u8Row es diferente a 0 puede retroceder
            {
                if(((*u8Column)!=0)) //si la u8Column encuentra entre 1 y 15 puede disminuir uno
                    (*u8Column)--;
                else
                    if(((*u8Row)!=0)) //si la u8Column es 0 entonces checa si existen rows que disminuir
                    {
                        (*u8Column)=NOKIA5110_COLUMN_SIZE-1;
                        (*u8Row)--;
                    }
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*u8Column)!=0) || ((*u8Row)!=0)) //si la u8Column es diferente a 0 puede retroceder
            {
                if(((*u8Column)!=0))
                    (*u8Column)--;
                else
                    if(((*u8Row)!=0))
                    {
                        (*u8Column)=NOKIA5110_COLUMN_SIZE-1;
                        (*u8Row)--;
                    }
            }
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            NOKIA5110__vSendChar(' ');//borra el caracter que pudiera haber en la posicion
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion
            break;
        case '\e': //escape
            u8Exit=1;//indica que se necesita u8Exit de la funcion
            break;
        case '\f': //nueva pagina
            *u8Column=*u8Row=0;//reinicia los valores
            NOKIA5110__vClear(); //limpia la pantalla
            for(u32Delay=3000; u32Delay>0; u32Delay--);//1.60 ms aprox a 16MHz
            NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //actualiza la posicion a 0,0
            break;




        case '%':
            cString++;
            switch(*cString)
            {
                case 'd': //"%d o %i"
                case 'i':
                    valueARGi=(int16_t)va_arg(ap, int16_t);
                    CONV__u8IntToString((int16_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break;
                case 'u':// "%u"
                    valueARGi=(uint16_t)va_arg(ap, uint16_t);
                    CONV__u8UIntToString((uint16_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break;
                case 'x': //"%x"
                    valueARGi=(uint16_t)va_arg(ap, uint16_t);
                    CONV__u8HexToString((uint16_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break;
                case 'X':// "%X"
                    valueARGi=(uint16_t)va_arg(ap, uint16_t);
                    CONV__u8HEXToString((uint16_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break;
                case 'o': //"%o"
                    valueARGi=(uint16_t)va_arg(ap, uint16_t);
                    CONV__u8OctToString((uint16_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break;
               case 'p': //"%p"
                    valueARGcl=(void*)va_arg(ap, void*);
                    CONV__u8BinToString((uint64_t)((uint16_t)valueARGcl),conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                        break;
                case 'f': //"%f"
                    valueARGd=(double)va_arg(ap, double);
                    CONV__u8FloatToString((float)valueARGd,0,1,2,3,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break;




                case 'c': //"%c"
                    valueARGi=(uint8_t)va_arg(ap, int);
                    NOKIA5110__vSendChar(valueARGi);//manda el caracter a la LCD
                    (*u8Column)++;
                    if(((*u8Column)&0xF)>(NOKIA5110_COLUMN_SIZE-1)) //si la u8Column es 0 indica que empieza una nueva u8Row
                    {
                        (*u8Column)=0;
                        (*u8Row)++; //aumenta la u8Row
                        if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                            *u8Row=0;
                        NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //pone el cursor en 0,x
                    }
                    break;
                case 's':// "%s"
                    valueARGc=(char*)va_arg(ap,char*);  //el siguiente argumento es un puntero
                    u16Count+=NOKIA5110__u16Print(valueARGc,u8Column,u8Row)-1;//imprime la cString del puntero
                    break;
                case 'l'://"%lf" "%8.4lf" "%5.3f" "%l"
                    cString++; //aumenta en uno la posicion del cString
                    if(*cString=='f') //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                        valueARGd=(double)va_arg(ap, double);
                        CONV__u8FloatToString((double)valueARGd,0,1,2,5,conversion);
                        u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                        break; //break de este caso
                    }
                    if(*cString=='l' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                        cString++;
                        if(*cString=='d' || *cString=='i' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                          {
                          valueARGii=(int64_t)va_arg(ap, int64_t);
                          CONV__u8IntToString((int64_t)valueARGii,conversion);
                          u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                          break; //break de este caso
                          }
                        if(*cString=='u' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                          {
                          valueARGuu=(uint64_t)va_arg(ap, uint64_t);
                          CONV__u8UIntToString((uint64_t)valueARGuu,conversion);
                          u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                          break; //break de este caso
                          }
                    }
                    if(*cString=='d' || *cString=='i' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                    valueARGi=(int32_t)va_arg(ap, int32_t);
                    CONV__u8IntToString((int32_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break; //break de este caso
                    }
                    if(*cString=='u' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                    valueARGi=(uint32_t)va_arg(ap, uint32_t);
                    CONV__u8IntToString((uint32_t)valueARGi,conversion);
                    u16Count+=NOKIA5110__u8SendString(conversion,u8Column,u8Row)-1;
                    break; //break de este caso
                    }
                    else
                    {
                        cString--; //si no encuentra la 'f' regresa a la 'l'
                    cString--;//si no es ningun caso anterior regresa al '%'
                    NOKIA5110__vSendChar(*cString);
                    break;
                    }
                default:// "%p"
                    cString--;//si no es ningun caso anterior regresa al '%'
                    NOKIA5110__vSendChar(*cString);
                    (*u8Column)++;
                    if(((*u8Column)&0xF)>(NOKIA5110_COLUMN_SIZE-1)) //si la u8Column es 0 indica que empieza una nueva u8Row
                    {
                        (*u8Column)=0;
                        (*u8Row)++; //aumenta la u8Row
                        if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                            *u8Row=0;
                        NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //pone el cursor en 0,x
                    }
                    break;

           }
            break;



        default :
            NOKIA5110__vSendChar(*(cString)); //envia el caracter correspondiente
            (*u8Column)++;
            if(((*u8Column)&0xF)>(NOKIA5110_COLUMN_SIZE-1)) //si la u8Column es 0 indica que empieza una nueva u8Row
            {
                (*u8Column)=0;
                (*u8Row)++; //aumenta la u8Row
                if(*u8Row>(NOKIA5110_ROW_SIZE-1))
                    *u8Row=0;
                NOKIA5110__vSetCursorChar(*u8Column,*u8Row); //pone el cursor en 0,x
            }
            break;
        }
        cString++; //el puntero apunta al siguiente caracter
        u16Count++; //suma 1 al conteo total de caracter enviados a la LCD
        if(u8Exit)
            break;
    }
    va_end(ap); //reinicia el puntero

     return u16Count; //regresa el conteo de caracteres y caracteres especiales
}


/*
unsigned long long NOKIA5110_PrintfSection(char* string,unsigned char* column,unsigned char* row,unsigned char X1,unsigned char X2,unsigned char Y1,unsigned char Y2,...)
{
    register unsigned long long count=0;//variable usada para saber cuantos caracteres se mandaron a la LCD
    register char exit=0;
    register int delay;
    register char temp=0;

    if((X1>(MAX_X/7)-1) || (X2>(MAX_X/7)-1) || (Y1>(MAX_Y/8)-1) || (Y2>(MAX_Y/8)-1)   )
         return 0;


    if(X1>X2)
    {
        temp=X1;
        X1=X2;
        X2=temp;
    }
    if(Y1>Y2)
    {
        temp=Y1;
        Y1=Y2;
        Y2=temp;
    }



    va_list ap; //crea puntero de los argumentos
    double valueARGd; //variable donde guardara el valor del argumento
    char* valueARGc; //variable donde guardara el valor del argumento
    long valueARGi; //variable donde guardara el valor del argumento
    long long valueARGii; //variable donde guardara el valor del argumento
    unsigned long long valueARGuu; //variable donde guardara el valor del argumento
    void* valueARGcl; //variable donde guardara el valor del argumento
    char conversion[30];
    va_start(ap, Y2);//maneja la memoria de los argumentos empezando desde el ultimo conocido ingresado


    *column+=X1;
    *row+=Y1;

    if((*column)>(X2))
    {
        (*column)=X1;
    }
    else
    {
        (*column)&=0xF;
    }

    if(((*column)&0xF)<=(X1))
    {
        (*column)=X1;
    }
    else
    {
        (*column)&=0xF;
    }

    if(*row>(Y2))
            (*row)=Y1;

    if(*row<=(Y1))
            (*row)=Y1;


    NOKIA5110_CursorChar(*column,*row); //indica la posicion inicial del cursor

    while(*string)// realiza el ciclo mientras la string tenga algun valor
    {
        switch (*string) //detecta si existe un caracter especial
        {


        case '\n': //salto de linea
            (*row)++; //aumenta la row
            if(*row>(Y2))
                (*row)=Y1;
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion
            break;
        case '\r': //retorno de carro
            (*column)=X1; //actualiza el valor de la column a la primera posicion
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion
            break;
        case '\t': //tabulacion
            if((*column)<(X2-TAB_SIZE))
                *column+=TAB_SIZE; //aumenta 3 espacios vacios
            else
            {
                (*column)=X1; // pasa a la siguiente row si no cabe la tabulacion
                (*row)++; //aumenta la row
                if(*row>(Y2))
                    (*row)=Y1;
            }
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion
            break;
         case '\b': //retroceso
            if(((*column)!=X1) || ((*row)!=Y1)) //si la column y row es diferente a 0 puede retroceder
            {
                if(((*column)!=X1)) //si la column encuentra entre 1 y 15 puede disminuir uno
                    (*column)--;
                else
                    if(((*row)!=Y1)) //si la column es 0 entonces checa si existen rows que disminuir
                    {
                        (*column)=X2;
                        (*row)--;
                    }
            }
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion
            break;
        case '\a'://borrado (ascii sonido)
            if(((*column)!=X1) || ((*row)!=X1)) //si la column es diferente a 0 puede retroceder
            {
                if(((*column)!=X1))
                    (*column)--;
                else
                    if(((*row)!=Y1))
                    {
                        (*column)=Y2;
                        (*row)--;
                    }
            }
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion
            Nokia5110_SendChar(' ');//borra el caracter que pudiera haber en la posicion
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion
            break;
        case '\e': //escape
            exit=1;//indica que se necesita exit de la funcion
            break;
        case '\f': //nueva pagina
            *column=X1;
            (*row)=Y1;//reinicia los valores
            NOKIA5110_ClearSectionChar(X1,X2,Y1,Y2);
            for(delay=3000; delay>0; delay--);//1.60 ms aprox a 16MHz
            NOKIA5110_CursorChar(*column,*row); //actualiza la posicion a 0,0
            break;




        case '%':
            string++;
            switch(*string)
            {
                case 'd': //"%d o %i"
                case 'i':
                    valueARGi=(int)va_arg(ap, int);
                    Int_To_String((int)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break;
                case 'u':// "%u"
                    valueARGi=(unsigned int)va_arg(ap, unsigned int);
                    UInt_To_String((unsigned int)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break;
                case 'x': //"%x"
                    valueARGi=(unsigned int)va_arg(ap, unsigned int);
                    Hex_To_String((unsigned int)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break;
                case 'X':// "%X"
                    valueARGi=(unsigned int)va_arg(ap, unsigned int);
                    HEX_To_String((unsigned int)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break;
                case 'o': //"%o"
                    valueARGi=(unsigned int)va_arg(ap, unsigned int);
                    Oct_To_String((unsigned int)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break;
               case 'p': //"%p"
                    valueARGcl=(void*)va_arg(ap, void*);
                    Bin_To_String((long long)valueARGcl,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                        break;
                case 'f': //"%f"
                    valueARGd=(double)va_arg(ap, double);
                    Float_To_String((float)valueARGd,2,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break;




                case 'c': //"%c"
                    valueARGi=(unsigned char)va_arg(ap, unsigned char);
                    Nokia5110_SendChar(valueARGi);//manda el caracter a la LCD
                    (*column)++;
                    if((*column)>(X2)) //si la column es 0 indica que empieza una nueva row
                    {
                        (*column)=X1;
                        (*row)++; //aumenta la row
                        if(*row>(Y2))
                            (*row)=Y1;
                        NOKIA5110_CursorChar(*column,*row); //pone el cursor en 0,x
                    }
                    break;
                case 's':// "%s"
                    valueARGc=(char*)va_arg(ap,char*);  //el siguiente argumento es un puntero
                    count+=NOKIA5110_PrintSection(valueARGc,column,row,X1,X2,Y1,Y2)-1;//imprime la string del puntero
                    break;
                case 'l'://"%lf" "%8.4lf" "%5.3f" "%l"
                    string++; //aumenta en uno la posicion del string
                    if(*string=='f') //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                        valueARGd=(double)va_arg(ap, double);
                        Float_To_String((double)valueARGd,5,conversion);
                        count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                        break; //break de este caso
                    }
                    if(*string=='l' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                        string++;
                        if(*string=='d' || *string=='i' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                          {
                          valueARGii=(long long)va_arg(ap, long long);
                          Int_To_String((long long)valueARGii,conversion);
                          count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                          break; //break de este caso
                          }
                        if(*string=='u' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                          {
                          valueARGii=(unsigned long long)va_arg(ap, unsigned long long);
                          UInt_To_String((unsigned long long)valueARGuu,conversion);
                          count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                          break; //break de este caso
                          }
                    }
                    if(*string=='d' || *string=='i' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                    valueARGi=(long)va_arg(ap, long);
                    Int_To_String((long)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break; //break de este caso
                    }
                    if(*string=='u' ) //si es 'f' el sig caracter significa que vamos a convertir un double
                    {
                    valueARGi=(unsigned long)va_arg(ap, unsigned long);
                    Int_To_String((unsigned long)valueARGi,conversion);
                    count+=NOKIA5110_SendStringSection(conversion,column,row,X1,X2,Y1,Y2)-1;
                    break; //break de este caso
                    }
                    else
                    {
                        string--; //si no encuentra la 'f' regresa a la 'l'
                    string--;//si no es ningun caso anterior regresa al '%'
                    Nokia5110_SendChar(*string);
                    break;
                    }
                default:// "%p"
                    string--;//si no es ningun caso anterior regresa al '%'
                    Nokia5110_SendChar(*string);
                    (*column)++;
                    if(((*column)&0xF)>(X2)) //si la column es 0 indica que empieza una nueva row
                    {
                        (*column)=X1;
                        (*row)++; //aumenta la row
                        if(*row>(Y2))
                            (*row)=Y1;
                        NOKIA5110_CursorChar(*column,*row); //pone el cursor en 0,x
                    }
                    break;

           }
            break;



        default :
            Nokia5110_SendChar(*(string)); //envia el caracter correspondiente
            (*column)++;
            if((*column)>(X2)) //si la column es 0 indica que empieza una nueva row
            {
                (*column)=X1;
                (*row)++; //aumenta la row
                if(*row>(Y2))
                    (*row)=Y1;
                NOKIA5110_CursorChar(*column,*row); //pone el cursor en 0,x
            }
            break;
        }
        string++; //el puntero apunta al siguiente caracter
        count++; //suma 1 al conteo total de caracter enviados a la LCD
        if(exit)
            break;
    }
    va_end(ap); //reinicia el puntero

     return count; //regresa el conteo de caracteres y caracteres especiales
}

*/



void NOKIA5110__vClear(void)
{
  uint16_t u16I=0;
  for(u16I=0; u16I<(NOKIA5110_MAX_X*(NOKIA5110_MAX_Y/8)); u16I++){
      NOKIA5110__vSendData(0);
  }
  NOKIA5110__vSetCursor(0, 0);
}


void NOKIA5110__vClearSectionPixel(uint8_t u8X1,uint8_t u8X2,uint8_t u8Y1,uint8_t u8Y2)
{
  uint8_t u8Row=0, u8Column=0;
  uint8_t u8Temp=0;
  if((u8X1>NOKIA5110_MAX_X-1) || (u8X2>NOKIA5110_MAX_X-1) || (u8Y1>(NOKIA5110_MAX_Y/8)-1) || (u8Y2>(NOKIA5110_MAX_Y/8)-1)   )
      return;

  if(u8X1>u8X2)
  {
      u8Temp=u8X2;
      u8X2=u8X1;
      u8X1=u8Temp;
  }
  if(u8Y1>u8Y2)
  {
      u8Temp=u8Y2;
      u8Y2=u8Y1;
      u8Y1=u8Temp;
  }
  NOKIA5110__vSetCursor(u8X1, u8Y1);
  
  for (u8Row=u8Y1; u8Row<=u8Y2; u8Row++)
  {
      for (u8Column=u8X1; u8Column<=u8X2; u8Column++)
      {
          NOKIA5110__vSetCursor(u8Column, u8Row);
          NOKIA5110__vSendData(0);
      }
  }
  NOKIA5110__vSetCursor(u8X1, u8Y1);
}


void NOKIA5110__vClearSectionChar(uint8_t u8X1,uint8_t u8X2,uint8_t u8Y1,uint8_t u8Y2)
{
  uint8_t u8Row=0, u8Column=0;
  uint8_t u8Temp=0;
  if((u8X1>(NOKIA5110_MAX_X/7)-1) || (u8X2>(NOKIA5110_MAX_X/7)-1) || (u8Y1>(NOKIA5110_MAX_Y/8)-1) || (u8Y2>(NOKIA5110_MAX_Y/8)-1)   )
      return ;

  if(u8X1>u8X2)
  {
      u8Temp=u8X2;
      u8X2=u8X1;
      u8X1=u8Temp;
  }
  if(u8Y1>u8Y2)
  {
      u8Temp=u8Y2;
      u8Y2=u8Y1;
      u8Y1=u8Temp;
  }
  NOKIA5110__vSetCursorChar(u8X1, u8Y1);
  for (u8Row=u8Y1; u8Row<=u8Y2; u8Row++)
  {
      for (u8Column=u8X1; u8Column<=u8X2; u8Column++)
      {
          NOKIA5110__vSetCursorChar(u8Column, u8Row);
          NOKIA5110__vSendChar(' ');
      }
  }
  NOKIA5110__vSetCursorChar(0, 0);
}


void NOKIA5110__vPrintBuffer(void)
{
    NOKIA5110__vPrintImage(NOKIA5110_u8ImageBuffer);
}


void NOKIA5110__vPrintImage( uint8_t *pu8Image)
{
	NOKIA5110__vSetCursor(0,0);
     NOKIA5110__vSendMultipleData(pu8Image,(NOKIA5110_MAX_X*(NOKIA5110_MAX_Y/8)));
}



void NOKIA5110__vClearBuffer(void)
{
    int i;
    for(i=0; i<(NOKIA5110_MAX_X*NOKIA5110_MAX_Y/8); i++)
		NOKIA5110_u8ImageBuffer[i] = 0;
}

void NOKIA5110__vFillBuffer(uint8_t *pu8Image)
{
    int i;
    for(i=0; i<(NOKIA5110_MAX_X*NOKIA5110_MAX_Y/8); i++)
    {
        NOKIA5110_u8ImageBuffer[i] = pu8Image[i];
    }
}

/*
int NOKIA5110_BMPBinary(const unsigned char *ptr)
{
  long width,height,bitsPerPixel;
  long widthMax,heightMax,k;
  long bitsTotal;
  unsigned char mask1bit[8]=
  {
   0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
  };
  unsigned char mask4bit[2]=
  {
   0xF0,0x0F
  };
  unsigned char mask8bit[1]=
  {
   0xFF
  };
  unsigned char mask16bit[2]=
  {
   0xFF, 0xFF
  };
  unsigned char mask24bit[4]=
  {
   0xFF, 0xFF, 0xFF, 0x00
  };
  unsigned char mask32bit[4]=
  {
   0xFF, 0xFF, 0xFF, 0xFF
  };
  unsigned char* mask=mask1bit;
  unsigned long actualX, actualXi;
  bitmapV1x_t* bitmapV1= (bitmapV1x_t*)(ptr);
  bitmapV2x_t* bitmapV2= (bitmapV2x_t*)(ptr-2);
  bitmapV3x_t* bitmapV3x= (bitmapV3x_t*)(ptr-2);
  bitmapV3_t* bitmapV3=(bitmapV3_t*) (ptr-2);
  bitmapV4x_t* bitmapV4x= (bitmapV4x_t*)(ptr-2);
  bitmapV4_t* bitmapV4= (bitmapV4_t*)(ptr-2);
  unsigned char* image=0;
  if(bitmapV1->bitmapHeader.type==0)
  {
      if(bitmapV1->bitmapHeader.planes==1)
      {
          width=bitmapV1->bitmapHeader.width;
          height=bitmapV1->bitmapHeader.height;
          bitsPerPixel=bitmapV1->bitmapHeader.bitsPerPixel;
      }
      else
          return 0;
  }
  else if(bitmapV2->bitmapFileHeader.fileType==0x4D42 )
  {
      image=(unsigned char*)&ptr[bitmapV2->bitmapFileHeader.bitmapOffset];
      switch(bitmapV2->bitmapHeader.size)
      {
      case 12:
          if(bitmapV2->bitmapHeader.planes==1)
          {
              width=bitmapV2->bitmapHeader.width;
              height=bitmapV2->bitmapHeader.height;
              bitsPerPixel=bitmapV2->bitmapHeader.bitsPerPixel;
          }
          else
              return 0;
          break;
      case 40:
          if(bitmapV3x->bitmapHeader.compression==0)
          {
              if(bitmapV3x->bitmapHeader.planes==1)
              {
                  width=bitmapV3x->bitmapHeader.width;
                  height=bitmapV3x->bitmapHeader.height;
                  bitsPerPixel=bitmapV3x->bitmapHeader.bitsPerPixel;
              }
              else
                  return 0;
          }
          else if(bitmapV3x->bitmapHeader.compression==3)
          {
              if(bitmapV3->bitmapHeader.planes==1)
              {
                  width=bitmapV3->bitmapHeader.width;
                  height=bitmapV3->bitmapHeader.height;
                  bitsPerPixel=bitmapV3->bitmapHeader.bitsPerPixel;
              }
              else
                  return 0;

          }
          else
              return 0;
          break;
      case 108:
          if(bitmapV4x->bitmapHeader.compression==0)
          {
              if(bitmapV4x->bitmapHeader.planes==1)
              {
                  width=bitmapV4x->bitmapHeader.width;
                  height=bitmapV4x->bitmapHeader.height;
                  bitsPerPixel=bitmapV4x->bitmapHeader.bitsPerPixel;
              }
              else
                  return 0;
          }
          else if(bitmapV4x->bitmapHeader.compression==3)
          {
              if(bitmapV4->bitmapHeader.planes==1)
              {
                  width=bitmapV4->bitmapHeader.width;
                  height=bitmapV4->bitmapHeader.height;
                  bitsPerPixel=bitmapV4->bitmapHeader.bitsPerPixel;
              }
              else
                  return 0;

          }
          else
              return 0;
      default:
          return 0;
      }
  }
  else
  {
      return 0;
  }
//
//  widthTemp=width/zoom;
//  heightTemp=height/zoom;
//  while((widthTemp>MAX_X) || (heightTemp>MAX_Y))
//  {
//      zoom++;
//      widthTemp=width/zoom;
//      heightTemp=height/zoom;
//  }
//

  if(bitsPerPixel<=8)
  {
      if(bitsPerPixel==1)
          mask=mask1bit;
      if(bitsPerPixel==4)
          mask=mask4bit;
      if(bitsPerPixel==8)
          mask=mask8bit;
      bitsTotal=(8/bitsPerPixel);
      actualX = MAX_X*((MAX_Y/8)-1);
      actualXi=0;
      if(MAX_Y>height)
          heightMax=height;
      else
          heightMax=MAX_Y;

      heightMax/=8;

      if(MAX_X>width)
          widthMax=width;
      else
          widthMax=MAX_X;

      widthMax/=bitsTotal;


      for(long f=0; f<heightMax; f++)
      {
          for(long l=0; l<8; l++)
          {
              for(long i=0;i<widthMax; i++)
              {
                  for(long j=0; j<(bitsTotal); j++)
                  {
                      k=(i*(bitsTotal))+j;
                      if(image[actualXi+i]&mask[j])
                          Image[actualX+k]&=~mask1bit[l];
                      else
                          Image[actualX+k]|=mask1bit[l];
                  }
              }
              switch((width/(bitsTotal))%4)
              {      // skip any padding
                case 0: actualXi = actualXi + 0; break;
                case 1: actualXi = actualXi + 3; break;
                case 2: actualXi = actualXi + 2; break;
                case 3: actualXi = actualXi + 1; break;
              }
              actualXi+=width/(bitsTotal);
          }
          actualX-=MAX_X;
      }
      return 1;

  }
  else if(bitsPerPixel==16)
  {

  }
  else if(bitsPerPixel==24)
  {

  }
  else if(bitsPerPixel==32)
  {

  }

*/


/*
  long width = ptr[18], height = ptr[22], i, j;
  unsigned short Arreglox, Arregloy;
  unsigned char mask;
  // check for clipping
  if((height <= 0) ||              // bitmap is unexpectedly encoded in top-to-bottom pixel order
     ((width%2) != 0) ||           // must be even number of columns
     ((xpos + width) > MAX_X) || // right side cut off
     (ypos < (height - 1)) ||      // top cut off
     (ypos > MAX_Y))           { // bottom cut off
    return;
  }
  if(threshold > 14){
    threshold = 14;             // only full 'on' turns pixel on
  }
  // bitmaps are encoded backwards, so start at the bottom left corner of the image
  Arregloy = ypos/8;
  Arreglox = xpos + MAX_X*Arregloy;
  mask = ypos%8;                // row 0 to 7
  mask = 0x01<<mask;            // now stores a mask 0x01 to 0x80
  j = ptr[10];                  // byte 10 contains the offset where image data can be found
  for(i=1; i<=(width*height/2); i=i+1){
    // the left pixel is in the upper 4 bits
    if(((ptr[j]>>4)&0xF) > threshold){
      Arreglo[Arreglox] |= mask;
    } else{
      Arreglo[Arreglox] &= ~mask;
    }
    Arreglox = Arreglox + 1;
    // the right pixel is in the lower 4 bits
    if((ptr[j]&0xF) > threshold){
      Arreglo[Arreglox] |= mask;
    } else{
      Arreglo[Arreglox] &= ~mask;
    }
    Arreglox = Arreglox + 1;
    j = j + 1;
    if((i%(width/2)) == 0){     // at the end of a row
      if(mask > 0x01){
        mask = mask>>1;
      } else{
        mask = 0x80;
        Arregloy = Arregloy - 1;
      }
      Arreglox = xpos + MAX_X*Arregloy;
      // bitmaps are 32-bit word aligned
      switch((width/2)%4){      // skip any padding
        case 0: j = j + 0; break;
        case 1: j = j + 3; break;
        case 2: j = j + 2; break;
        case 3: j = j + 1; break;
      }
    }
  }
  */
//}


