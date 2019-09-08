
/******************************************************************************
*                      Includes
******************************************************************************/
#include"ADC.h"
/******************************************************************************
*                      Defines and data types
******************************************************************************/

/******************************************************************************
*                      Global variables
******************************************************************************/

/******************************************************************************
*                      Static variables
******************************************************************************/
/******************************************************************************
*                      Internal function prototypes
******************************************************************************/


/******************************************************************************
*                      Public functions
******************************************************************************/


void InitADC()
{

// Select Vref=AVcc
  CLR_BIT(ADMUX,REFS1);
  SET_BIT(ADMUX,REFS0);
  ADCSRA|= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //set pre-scaler to 128
}

uint16_t Read_ADC()
{   uint16_t ADC_value=0;
    ADCSRA|= (1<< ADSC);
     while(ADCSRA&(1<<ADSC));
        ADC_value=ADC;
      return ADC_value;
}


void channel_select(uint8_t i)
{
    if (i==0)
    {
     /* left wheel speed of vehicle sensor ADC channel is selected*/
     //ADMUX=0x00;
     CLR_BIT(ADMUX,MUX0);
     CLR_BIT(ADMUX,MUX1);
     CLR_BIT(ADMUX,MUX2);
     CLR_BIT(ADMUX,MUX3);

    }
     if (i==1)
    {
     /* right wheel speed of vehicle sensor ADC channel is selected*/
     //ADMUX=0x00;
     SET_BIT(ADMUX,MUX0);
     CLR_BIT(ADMUX,MUX1);
     CLR_BIT(ADMUX,MUX2);
     CLR_BIT(ADMUX,MUX3);

    }



    if (i==2)
    {
      /*Steering angle is selected*/
        //ADMUX=0x02;
        CLR_BIT(ADMUX,MUX0);
        SET_BIT(ADMUX,MUX1);
        CLR_BIT(ADMUX,MUX2);
        CLR_BIT(ADMUX,MUX3);
    }

    if (i==3)
    {
    /*Yaw rate is selected*/
    //ADMUX=0x03;
    SET_BIT(ADMUX,MUX0);
    SET_BIT(ADMUX,MUX1);
    CLR_BIT(ADMUX,MUX2);
    CLR_BIT(ADMUX,MUX3);
    }
}


/******************************************************************************
*                      Internal functions
******************************************************************************/


/******************************************************************************
*                      End of File
******************************************************************************/
