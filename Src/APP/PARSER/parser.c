/************************************************/
/*	Author		: Ahmed Rezk		        	*/
/*	Date		: 4 Mar 2023		        	*/
/*	file name	: parser.c 		    			*/
/*	file module	: parser						*/
/*	Version		: V01				        	*/
/************************************************/

/* includes */
/* Library */
#include "LIB/std_types.h"
#include "LIB/bit_math.h"

/* Lower layers interfaces */
/* None */

/* My own interface */
#include "APP/PARSER/parser.h"
#include "MCAL/FPEC/FPEC_interface.h"

uint16_t Data[100] = {0};
uint32_t Address= 0x08000000;

uint8_t AsciToHex(uint8_t Copy_u8Asci)
{
	uint8_t Result;
	if ( (Copy_u8Asci >= 48) && (Copy_u8Asci <= 57) )	/* '0' : '9' */
	{
		Result = Copy_u8Asci - 48;
	}

	else	/* 'A' : 'F' */
	{
		Result = Copy_u8Asci - 55;
	}

	return Result;
}


void ParseData(uint8_t* Copy_u8BufData)
{
	uint8_t DigitLow,DigitHigh,CC,i;
	uint8_t DataDigit0,DataDigit1,DataDigit2,DataDigit3;
	uint8_t DataCounter = 0;

	/* Get Character Count */
	DigitHigh = AsciToHex (Copy_u8BufData[1]);
	DigitLow  = AsciToHex (Copy_u8BufData[2]);
	CC        = (DigitHigh<<4) | DigitLow ;

	/* Get Address */
	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
	DataDigit3 = AsciToHex (Copy_u8BufData[6]);

	/* Clear Low Part of Address */
	Address = Address & 0xFFFF0000;
	Address = Address | (DataDigit3) | (DataDigit2 << 4) | (DataDigit1 << 8) | (DataDigit0<<12);

	for (i=0; i<CC/2; i++)
	{
		DataDigit0 = AsciToHex (Copy_u8BufData[4*i+9 ]);
		DataDigit1 = AsciToHex (Copy_u8BufData[4*i+10]);
		DataDigit2 = AsciToHex (Copy_u8BufData[4*i+11]);
		DataDigit3 = AsciToHex (Copy_u8BufData[4*i+12]);

		Data[DataCounter] = (DataDigit3 << 8) | (DataDigit2 << 12) | (DataDigit1) | (DataDigit0<<4);
		DataCounter++;
	}

	FPEC_VidFlashWrite(Address,Data,CC/2);
}

void ParseUpperAddress(uint8_t* Copy_u8BufData)
{
//	u8 DataDigit0,DataDigit1,DataDigit2,DataDigit3;
//
//	/* Get Address */
//	DataDigit0 = AsciToHex (Copy_u8BufData[3]);
//	DataDigit1 = AsciToHex (Copy_u8BufData[4]);
//	DataDigit2 = AsciToHex (Copy_u8BufData[5]);
//	DataDigit3 = AsciToHex (Copy_u8BufData[6]);
//
//	/* Clear Low Part of Address */
//	Address = Address & (u32)0x0000FFFF;
//	Address = Address | (u32)((u32)(DataDigit3 << 28) | (u32)(DataDigit2 << 24) | (u32)(DataDigit1 << 20) | (u32)(DataDigit0 << 16));
}

void Parser_VidParseRecord(uint8_t* Copy_u8BufData)
{
	switch (Copy_u8BufData[8])
	{
	case '0': ParseData(Copy_u8BufData); break;
	case '4': ParseUpperAddress(Copy_u8BufData); break;
	}
}

