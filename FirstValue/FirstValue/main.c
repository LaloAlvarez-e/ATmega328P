/*
 * FirstValue.c
 *
 * Created: 27/5/2022 13:16:43
 * Author : InDeviceMex
 */ 
#include <ATmega328P_startup.h>
interrupt_vector stVector = {0U};

int main(void)
{
	uint8_t u8Count = 0U;
    /* Replace with your application code */
    while (1) 
    {
		stVector.interrupt_instruction = _vectab[u8Count].interrupt_instruction;
		stVector.interrupt_handler = _vectab[u8Count].interrupt_handler;
		u8Count++;
		if(u8Count > 25U)
			u8Count = 0U;
    }
}

