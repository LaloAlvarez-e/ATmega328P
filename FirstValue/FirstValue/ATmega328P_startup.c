/*
 * ATmega328P_startup.c
 *
 * Created: 27/5/2022 13:18:23
 *  Author: InDeviceMex
 */ 
#include <ATmega328P_startup.h>

void IntDefaultHandler (void) __attribute__ ((signal,__INTR_ATTRS));


interrupt_vector const _vectab[25U] = {
	{0x0C94U,
	&IntDefaultHandler},                /* The EXT INT0 handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The EXT INT1 handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The PCINT0 handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The PCINT1 handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The PCINT2 handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The WDT handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM2_COMPA handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM2_COMPB handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM2_OVF handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM1_CAPT handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM1_COMPA handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM1_COMPB handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM1_OVF handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM0_COMPA handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM0_COMPB handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TIM0_OVF handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The SPI_STC handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The USART_RXC handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The USART_UDRE handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The USART_TXC handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The ADC handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The EE_RDY handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The ANA_COMP handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The TWI handler*/
	{0x0C94U,
	&IntDefaultHandler},                /* The SPM_Ready handler*/
};

void IntDefaultHandler(void)
{
	while(1U)
	{

	}
}
