/************************************************/
/*	Author		: Ahmed Rezk		        	*/
/*	Date		: 4 Mar 2023		        	*/
/*	file name	: FPEC_interface.h	        	*/
/*	file module	: general purpose input output	*/
/*	Version		: V01				        	*/
/************************************************/

#ifndef FPEC_INTERFACE__H_
#define FPEC_INTERFACE__H_

void FPEC_VidEraseAppArea(void);

void FPEC_VidFlashPageErase(uint8_t Copy_u8PageNumber);

void FPEC_VidFlashWrite(uint32_t Copy_u32Address, uint16_t* Copy_u16Data, uint8_t Copy_u8Length);

#endif /* FPEC_INTERFACE__H_ */
