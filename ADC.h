
#ifndef ADC_H
#define ADC_H
/******************************************************************************
*                      Includes
******************************************************************************/
#define ENABLE_ADC() ADCSRA|=(1<<ADEN); // enabling the ADC
#define DISABLE_ADC() ADCSRA&=~(1<<ADEN);
#include<avr/io.h>
#include<avr/interrupt.h>
#define CLR_BIT(PORT,BIT) PORT&= ~(1<<BIT)
#define SET_BIT(PORT,BIT) PORT|= (1<<BIT)
//#define DISABLE_ADC() ADCSRA&= ~(1<<ADEN);
//#define ENABLE_ADC()  ADCSRA| = (1<<ADEN);
/*******************************************************************
            Public function prototypes
********************************************************************/

//* Name: Init_ADC(void)
//* Description:  Intializes the ADC
extern void InitADC();

//* Name: Read_ADC(void)
//* Description:  Read the ADC databn
extern uint16_t Read_ADC();
extern void channel_select(uint8_t);

/******************************************************************************
*                      End of File
******************************************************************************/
#endif
