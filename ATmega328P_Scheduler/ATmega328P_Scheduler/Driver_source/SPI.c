/*
 * SPI.c
 *
 * Created: 16/10/2019 08:32:09 p. m.
 *  Author: Lalo
 */ 

#include "SPI.h"
void SPI__vDeInit(void)
{
	SPCR=0;
	SPSR=0;
}

void SPI__vInit(SPI_nMode enMode,SPI_nDataOrder enDataOrder,SPI_nClockPolarity enPolarity, SPI_nClockPhase enPhase, SPI_nClock enClockSource )
{
	SPCR&=~(1<<SPE);
	if(enMode == SPI_enModeSlave)
		SPCR&=~(1<<MSTR);
	else
		SPCR|=(1<<MSTR);
		
	if(enDataOrder == SPI_enMSBFirst)
		SPCR&=~(1<<DORD);
	else
		SPCR|=(1<<DORD);
		
	if(enPolarity == SPI_enClockIdleLow)
		SPCR&=~(1<<CPOL);
	else
		SPCR|=(1<<CPOL);
		
	if(enPhase == SPI_enClockSampleFirst)
		SPCR&=~(1<<CPHA);
	else
		SPCR|=(1<<CPHA);
		
	SPCR&=~((1<<SPR0)|(1<<SPR1));
	SPSR&=~(1<<SPI2X);	
	switch(enClockSource)
	{
		case SPI_enClockDiv2:
			SPCR&=~((1<<SPR0)|(1<<SPR1));
			SPSR|=(1<<SPI2X);
			break;
		case SPI_enClockDiv4:
			SPCR&=~((1<<SPR0)|(1<<SPR1));
			SPSR&=~(1<<SPI2X);
			break;
		case SPI_enClockDiv8:
			SPCR&=~(1<<SPR1);
			SPCR|= (1<<SPR0);
			SPSR|= (1<<SPI2X);
			break;
		case SPI_enClockDiv16:
			SPCR&=~(1<<SPR1);
			SPCR|= (1<<SPR0);
			SPSR&=~(1<<SPI2X);
			break;
		case SPI_enClockDiv32:
			SPCR&=~(1<<SPR0);
			SPCR|= (1<<SPR1);
			SPSR|= (1<<SPI2X);
			break;
		case SPI_enClockDiv64:
			SPCR&=~(1<<SPR0);
			SPCR|= (1<<SPR1);
			SPSR&=~(1<<SPI2X);
			break;
		case SPI_enClockDiv64_1:
			SPCR|= (1<<SPR0);
			SPCR|= (1<<SPR1);
			SPSR|= (1<<SPI2X);
			break;
		case SPI_enClockDiv128:
			SPCR|= (1<<SPR0);
			SPCR|= (1<<SPR1);
			SPSR&=~(1<<SPI2X);
			break;
		default:
			break;
	}
	
	SPCR|=(1<<SPE);
		
}


void SPI__vEnableInterrupt(void)
{
	
	SPCR|=(1<<SPIE);
}

void SPI__vDisableInterrupt(void)
{
	SPCR&=~(1<<SPIE);
}


void SPI__vInitPin(SPI_nPin enPin)
{
	if((enPin&SPI_enPinCLK)==SPI_enPinCLK)
	{
		DDRB|=(1<<DDB1);
		PORTB&=~(1<<PORTB1);
	}
	
	if((enPin&SPI_enPinMISO)==SPI_enPinMISO)
	{
		DDRB&=~(1<<DDB3);
		PORTB|=(1<<PORTB3);		
	}
			
	if((enPin&SPI_enPinMOSI)==SPI_enPinMOSI)
	{
		DDRB|=(1<<DDB2);
		PORTB&=~(1<<PORTB2);
	}
	if((enPin&SPI_enPinSS)==SPI_enPinSS)
	{
		DDRB|=(1<<DDB0);
		PORTB|=(1<<DDB0);

	}		
}
void SPI__vDeInitPin(SPI_nPin enPin)
{
	if((enPin&SPI_enPinCLK)==SPI_enPinCLK)
	{
		DDRB&=~(1<<DDB1);
		PORTB&=~(1<<PORTB1);
	}
	
	if((enPin&SPI_enPinMISO)==SPI_enPinMISO)
	{
		DDRB&=~(1<<DDB3);
		PORTB&=~(1<<PORTB3);
	}
	
	if((enPin&SPI_enPinMOSI)==SPI_enPinMOSI)
	{
		DDRB&=~(1<<DDB2);
		PORTB&=~(1<<PORTB2);
	}
	if((enPin&SPI_enPinSS)==SPI_enPinSS)
	{
		DDRB&=~(1<<DDB0);
		PORTB&=~(1<<PORTB0);
	}	
}

void SPI__vSendReceiveDataMaster(uint8_t* pu8DataOut, uint8_t* pu8DataIn, int16_t s16DataNumber )
{
	if((SPSR&(1<<SPIF))==(1<<SPIF))
	*pu8DataIn=SPDR;
		
	PORTB&=~(1<<DDB0);
	while((uint16_t)s16DataNumber>0)
	{
		SPCR|=(1<<MSTR);
		SPDR=*pu8DataOut;
		while((SPSR&(1<<SPIF))==0);
		*pu8DataIn=SPDR;
		pu8DataIn++;
		pu8DataOut++;
		s16DataNumber--;
	}
	
	PORTB|=(1<<DDB0);
}
void SPI__vSendDataMaster(uint8_t* pu8DataOut,int16_t s16DataNumber )
{
	uint8_t u8Dummy=0;
	if((SPSR&(1<<SPIF))==(1<<SPIF))
	u8Dummy=SPDR;
	
	PORTB&=~(1<<DDB0);
	while((uint16_t)s16DataNumber>0)
	{
		SPCR|=(1<<MSTR);
		SPDR=*pu8DataOut;
		while((SPSR&(1<<SPIF))==0);
		u8Dummy=SPDR;
		pu8DataOut++;
		s16DataNumber--;
	}
	
	PORTB|=(1<<DDB0);
}