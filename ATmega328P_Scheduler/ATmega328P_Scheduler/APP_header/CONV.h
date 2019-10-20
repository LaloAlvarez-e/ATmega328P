/*
 * CONV.h
 *
 *  Created on: 8 mar. 2018
 *      Author: InDev
 */

#ifndef CONV_H_
#define CONV_H_

#include <stdint.h>

#define INT2STRINGMAX 	(21)
#define HEX2STRINGMAX 	(19)
#define OCT2STRINGMAX 	(24)
#define BIN2STRINGMAX 	(40)


typedef enum
{
	CONV_enNAN = -1,
	CONV_enOK = 0,
	CONV_enERROR = 1,
}CONV_nStatus;



uint8_t CONV__u8IntToString(int64_t s64Number, char* pcConv);
uint8_t CONV__u8UIntToString(uint64_t u64Number, char* pcConv);
uint8_t CONV__u8HexToString(uint64_t u64Number, char* pcConv);
uint8_t CONV__u8HEXToString(uint64_t u64Number, char* pcConv);
uint8_t CONV__u8OctToString(uint64_t u64Number, char* pcConv);
uint8_t CONV__u8BinToString(uint64_t u64Number, char* pcConv);
uint8_t CONV__u8IntToStringCeros(int64_t s64Number,int8_t s8CerosLeft, char* pcConv);
uint8_t CONV__u8DIntToString(int64_t s64Number,uint8_t u8Positive,uint8_t u8Padding0,uint8_t u8Deci, char* pcConv);
uint8_t CONV__u8FloatToString(double dNumber,uint8_t u8Positive,uint8_t u8Padding0,int32_t s32Enteros,int32_t s32Decimals,char* pcConv);




int32_t CONV__s32String2Hex(char* pcString,int64_t* s64NumSigned );
int32_t CONV__s32String2Oct(char* pcString,int64_t* s64NumSigned );
int32_t CONV__s32String2Bin(char* pcString,int64_t* s64NumSigned );
int32_t CONV__s32String2Int(char* pcString,int64_t* s64NumSigned );
int32_t CONV__s32String2UInt (char* pcString,uint64_t* u64NumUnsigned );
int32_t CONV__s32String2Float(char* pcString,int8_t s8Decimals, float* pfConversion);

#endif /* CONV_H_ */
