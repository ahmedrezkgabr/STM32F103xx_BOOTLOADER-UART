/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Ahmed Rezk
 * @brief          : Main program body
 ******************************************************************************
 ******************************************************************************
 */

/* includes */
/* Library */
#include "LIB/std_types.h"
#include "LIB/bit_math.h"

/* lower layers */
#include "APP/PARSER/parser.h"
#include "MCAL/STK/STK_interface.h"
#include "MCAL/GPIO/GPIO_interface.h"
#include "MCAL/NVIC/NVIC_interface.h"
#include "MCAL/RCC/RCC_interface.h"
#include "MCAL/USART/USART_interface.h"
#include "MCAL/FPEC/FPEC_interface.h"


void Parser_VidParseRecord(uint8_t* Copy_u8BufData);

volatile uint8_t  u8RecBuffer[100]   ;
volatile uint8_t  u8RecCounter    = 0;
volatile uint8_t  u8TimeOutFlag   = 0;
volatile uint16_t u16TimerCounter = 0;
volatile uint8_t  u8BLWriteReq    = 1;
typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void goToApplication(void)
{
#define SCB_VTOR   *((volatile uint32_t*)0xE000ED08)

	SCB_VTOR = 0x08001000;

	addr_to_call = *(Function_t*)(0x08001004);
	addr_to_call();
}

int main(void)
{
	uint8_t Loc_u8RecStatus;


	RCC_VidInit();	/* HSI */
	RCC_VidEnablePeripheralClock(APB2,	 USART1_RCC);
	RCC_VidEnablePeripheralClock(APB2,	 GPIOA_RCC);
	RCC_VidEnablePeripheralClock(AHB,	 4);			/* FPEC */

	GPIO_VidSetPinMode(PORT_A, PIN9, OUTPUT_SPEED_2MHZ_AFPP);	/* TX */
	GPIO_VidSetPinMode(PORT_A, PIN10, INPUT_FLOATING);			/* RX */

	USART1_VidInit();

	STK_VidInit();
	STK_VidSetIntervalSingle(15000000, goToApplication);	/* 15sec */

	while(!u8TimeOutFlag)
	{
		Loc_u8RecStatus = USART1_U8ReceiveSynchronous(&(u8RecBuffer[u8RecCounter]));

		if(Loc_u8RecStatus)
		{
			STK_VidStopTimer();
			if(u8RecBuffer[u8RecCounter] == '\n')
			{
				if(u8BLWriteReq)
				{
					/* erase when first receive only */
					FPEC_VidEraseAppArea();
					u8BLWriteReq = 0;
				}

				/* parse and send acknowledgment  */
				Parser_VidParseRecord(u8RecBuffer);
				USART1_VidTransmitSynchronous('o');
				USART1_VidTransmitSynchronous('k');
				u8RecCounter = 0;
			}
			else
			{
				u8RecCounter++;
			}

			STK_VidSetIntervalSingle(15000000, goToApplication);	/* 15sec */
		}
		else
		{

		}

	}
}
