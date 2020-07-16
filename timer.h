
#ifndef timer_h
#define timer_h
/*******************************************************************
            Public function prototypes
********************************************************************/


extern void timer_PWM_Init();
extern void Fix_Right_PWM(int value);  //extern void Fix_Right_PWM(int) this is also right way of declaring only, but if we give formal argument here same should be used in the .c file as well
extern void Fix_Left_PWM(int value);
extern void Enable_PWM();
extern void Disable_PWM();




/******************************************************************************
*                      Includes
******************************************************************************/

/******************************************************************************
*                      End of File
******************************************************************************/
#endif
