/************************************************/
/*	Author		: Ahmed Rezk		        	*/
/*	Date		: 4 Mar 2023		        	*/
/*	file name	: FPEC_program.c 		    	*/
/*	file module	: general purpose input output	*/
/*	Version		: V01				        	*/
/************************************************/

/* includes */
/* Library */
#include "LIB/std_types.h"
#include "LIB/bit_math.h"

/* Lower layers interfaces */
/* None */

/* My own interface */
#include "MCAL/FPEC/FPEC_interface.h"

/* Private and configuration files */
#include "MCAL/FPEC/FPEC_private.h"
#include "MCAL/FPEC/FPEC_config.h"


void FPEC_VidEraseAppArea(void)
{
	uint8_t i;

	for (i=4;i<64;i++)
	{
		FPEC_VidFlashPageErase(i);
	}
}

void FPEC_VidFlashPageErase(uint8_t Copy_u8PageNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,7) == 1)
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}

	/* Page Erase Operation */
	SET_BIT(FPEC->CR,1);

	/* Write Page address */
	FPEC->AR = (uint32_t)(Copy_u8PageNumber * 1024) + 0x08000000 ;

	/* Start operation */
	SET_BIT(FPEC->CR,6);

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,0) == 1);

	/* EOP */
	SET_BIT(FPEC->SR,5);
	CLR_BIT(FPEC->CR,1);
}

void FPEC_VidFlashWrite(uint32_t Copy_u32Address, uint16_t* Copy_u16Data, uint8_t Copy_u8Length)
{
	uint8_t i;
	volatile uint16_t Temp;

	while (GET_BIT(FPEC->SR,0) == 1);

	/* Check if FPEC is locked or not */
	if ( /* FPEC_CR->BitAccess.LOCK == 1 */ GET_BIT(FPEC->CR,7) == 1 )
	{
		FPEC -> KEYR = 0x45670123;
		FPEC -> KEYR = 0xCDEF89AB;
	}


	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,0);

		/* Half word operation */

		Temp = Copy_u16Data[i];
		*((volatile uint16_t*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,0) == 1);

		/* EOP */
		SET_BIT(FPEC->SR,5);
		CLR_BIT(FPEC->CR,0);
	}

}
