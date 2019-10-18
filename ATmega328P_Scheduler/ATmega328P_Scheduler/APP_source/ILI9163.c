/*
 * ILI9163.c
 *
 * Created: 17/10/2019 01:50:04 a. m.
 *  Author: Lalo
 */ 
#include <ILI9163.h>
uint8_t u8DataOut[20]={0x00,1,2,4,8,0x10,0x20,0x40,0x80,0x55,0xAA,0x33};
uint8_t u8DataIn[10];

static const uint8_t ILI9163_Commands[] =
{
	17,             // 17 commands follow
	0x01,  0,       // Software reset
	0x11,  0,       // Exit sleep mode
	0x3A,  1, 0x05, // Set pixel format
	0x26,  1, 0x04, // Set Gamma curve
	0xF2,  1, 0x01, // Gamma adjustment enabled
	0xE0, 15, 0x3F, 0x25, 0x1C, 0x1E, 0x20, 0x12, 0x2A, 0x90,
	0x24, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, // Positive Gamma
	0xE1, 15, 0x20, 0x20, 0x20, 0x20, 0x05, 0x00, 0x15,0xA7,
	0x3D, 0x18, 0x25, 0x2A, 0x2B, 0x2B, 0x3A, // Negative Gamma
	0xB1,  2, 0x08, 0x08, // Frame rate control 1
	0xB4,  1, 0x07,       // Display inversion
	0xC0,  2, 0x0A, 0x02, // Power control 1
	0xC1,  1, 0x02,       // Power control 2
	0xC5,  2, 0x50, 0x5B, // Vcom control 1
	0xC7,  1, 0x40,       // Vcom offset
	0x2A,  4+0x80, 0x00, 0x00, 0x00, 0x7F, 250, // Set column address
	0x2B,  4, 0x00, 0x00, 0x00, 0x9F,            // Set page address
	0x36,  1, 0xC8,       // Set address mode
	0x29,  0,             // Set display on
};



void ILI9163__vInit(void)
{
	uint32_t u32Delay=0;
	ILI9163_DC_DIR|=ILI9163_DC_PIN;
	ILI9163_DC_OUT&=~ILI9163_DC_PIN;
	
	SPI__vInit(SPI_enModeMaster, SPI_enMSBFirst,SPI_enClockIdleLow,SPI_enClockSampleFirst,SPI_enClockDiv2);
	SPI__vInitPin(SPI_enPinCLK|SPI_enPinSS|SPI_enPinMOSI|SPI_enPinMISO);
	for(u32Delay=0; u32Delay<0x5FFFF; u32Delay++);

	ILI9163__vSendCommandList(ILI9163_Commands);	
	ILI9163__vClear(0xF800);

}

void ILI9163__vClear(uint16_t u16Color)
{
	uint8_t u8DataOut[2];
	uint8_t u8DataIn[2];
	uint16_t u16size=0;
	u8DataOut[0]=0x2C;
	ILI9163_DC_COMMAND();
	SPI__vSendReceiveDataMaster(u8DataOut,u8DataIn,1);
	u8DataOut[0]=(u16Color>>8)&0xFF;
	u8DataOut[1]=u16Color&0xFF;
	ILI9163_DC_DATA();
	for(u16size=0; u16size<(ILI9163_HEIGHTTOTAL*ILI9163_WIDTHTOTAL); u16size++)
	{
		SPI__vSendReceiveDataMaster(u8DataOut,u8DataIn,2);
	}
}

void ILI9163__vSendCommandList (const uint8_t *pu8Addr)
{
	uint8_t  u8NumCommands, u8NumArgs;
	uint8_t  u8Delay;
	uint32_t  u32Delay;
	uint8_t	 u8Command;
	uint8_t u8DataIn[20];
	
	
	u8NumCommands = *pu8Addr;            // Number of commands to follow
	pu8Addr++;
	while (u8NumCommands--)                           // For each command...
	{
		u8Command=*pu8Addr;    // Read, issue command
		pu8Addr++;
		
		ILI9163_DC_COMMAND();
		SPI__vSendReceiveDataMaster(&u8Command,u8DataIn,1);
		
		u8NumArgs = *pu8Addr;            // Number of arg to follow
		pu8Addr++;
		u8Delay = u8NumArgs & 0x80;      // If hibit set, delay follows args
		u8NumArgs &= ~0x80;         // Mask out delay bit
		
		ILI9163_DC_DATA();
		SPI__vSendReceiveDataMaster((uint8_t*)pu8Addr,u8DataIn,u8NumArgs);
		pu8Addr+=u8NumArgs;

		if (u8Delay)
		{
			u8Delay =*pu8Addr;     // Read post-command delay time (ms)
			pu8Addr++;
			for(u32Delay=0; u32Delay<0xAFFFF; u32Delay++);
		}
	}
}
