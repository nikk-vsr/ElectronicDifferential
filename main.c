/*Created by : nikhil Valiveti 
PD0 -> Engine input
PC0 -> right motor speed
PC1 -> left motor speed
PC2 -> steering angle
PC3 -> Yaw rate
PD6  ->  Right motor PWM       PD6 OC0A
PD5/PB3  -> left motor PWM     PD5 OC0B */

/* #include<avr/io.h>  check whether this library need to be added or not, As in C it might not recognize function related to the 
ATMEGA libraries are developed so that we can use C to code other than Assembly language*/

#include"timer.h"
#include"ADC.h"
#include<stdlib.h>
#include<math.h>
#define READ_BIT(PORT,PIN) !(PORT&(1<<PIN))

typedef struct
{
    volatile unsigned int BIT_FLAG:1;

}FLAG;
FLAG Engine_FLAG;
//Engine_FLAG.BIT_FLAG;
static int8_t abs(int8_t);

int main(void)
{   CLR_BIT(DDRD,PD0);
    SET_BIT(PORTD,PD0);     /* setting engine pin as input*/

    CLR_BIT(DDRD,PD1);
    SET_BIT(PORTD,PD1);

    CLR_BIT(EICRA,ISC01);
    SET_BIT(EICRA ,ISC00); //set logical change as interrupt for INT0

    SET_BIT(DDRD,PD5);   //set PD5 as output
    SET_BIT(DDRD,PD6);   // set PD6 as output
    SET_BIT(DDRB,PB5);    //set PB5 as output for understeer detection
    float Steering_Value;
    float Yaw_Rate;
    float Wheel_Base=5.24; //5.24 m
    float Car_Width=1.81;   //1.81m
    float Wheel_Radius=0.40;  //40cm   ---12inches
    float P_Delta_Leftmotor=0;  // change in speed of left motor
    float P_Delta_Rightmotor=0;    // change in speed of right motor
    float Left_Motor_Speed=0;
    float Right_Motor_Speed=0;
    //float Angular_velocity_wheel=0;
    float Turning_Radius=0;
    float Radius_Turn= 3.0;
    float Set_Leftmotor_Speed=0;
    float Set_Rightmotor_Speed=0;     //range taken as 0-1000RPM , 0-104 rad/s
    float Angularvelocity_Rightmotor=0;
    float Angularvelocity_Leftmotor=0;
    InitADC();
    ENABLE_ADC();
    timer_PWM_Init();
    //Enable_PWM();
    sei();
    //int x=0;
    //int y=0;
    //int flag=0;

    while(1)
    {
        //if((Engine_FLAG.BIT_FLAG )%2!=0)   // if engine is on then only check
       // if(flag%2 ==0)
       if((READ_BIT(PIND,PD0)))

       //if((EIFR)==0x01)  // set the flag for the interrupt)
        {
            if (READ_BIT(PIND,PD1))
            {
            Enable_PWM();
            channel_select(2);
            Steering_Value=(-65.0+ ((Read_ADC()*(130.0))/1024.0));  /*-65 to +65 degrees are taken as range of steering angle*/
                                                                    /* 0-2.5v is left , 2.5-5V is right*/
            channel_select(3);
            Yaw_Rate=(-50.0+ ((Read_ADC()*(100.0))/1024.0));    /*-50 to  +50 to degree per sec taken as range*/

            channel_select(0);
            Left_Motor_Speed=((Read_ADC()*(100.0))/(1024.0));     /* right motor angular speed   rad/s*/

            channel_select(1);
            Right_Motor_Speed=((Read_ADC()*(100.0))/(1024.0));    /*assuming it is given in rad/s*/

            if (Left_Motor_Speed <20 && Right_Motor_Speed <20 )   /* check for under steer*/
            {
                if ((abs(Steering_Value)) < (((10.0)*(Wheel_Base))/(Radius_Turn)))
                    SET_BIT(PORTB,PB5);  //under steer is occurring
                else
                    CLR_BIT(PORTB,PB5);
            }

            Turning_Radius= (Wheel_Base/tan(abs(Steering_Value)));  //Radius of turn making by the car  (meters)

            Set_Leftmotor_Speed=  (abs(Yaw_Rate)*(Turning_Radius+(Car_Width/2.0)));   //translational velocity   m/s
            Set_Rightmotor_Speed= (abs(Yaw_Rate)*(Turning_Radius-(Car_Width/2.0)));   // m/s

            Angularvelocity_Rightmotor=(Set_Rightmotor_Speed/ Wheel_Radius);   // motor angular velocity rad/ s
            Angularvelocity_Leftmotor=(Set_Leftmotor_Speed/ Wheel_Radius);     // rad/s

            P_Delta_Rightmotor= (((Left_Motor_Speed- Angularvelocity_Leftmotor)/(Left_Motor_Speed))*(100.0));
            P_Delta_Leftmotor= (((Right_Motor_Speed- Angularvelocity_Rightmotor)/(Right_Motor_Speed))*(100.0));

            Fix_Right_PWM(P_Delta_Rightmotor);   /* setting the PWM change for each motor*/
            Fix_Left_PWM(P_Delta_Leftmotor);
            }
            else
            {
               CLR_BIT(PORTD,PD5);
               CLR_BIT(PORTD,PD6);
            }

        }

        else
        { /*stop all of them*/
          Disable_PWM();
          CLR_BIT(PORTD,PD5);
          CLR_BIT(PORTD,PD6);
        }
    }

    return 0;
}

static int8_t abs(int8_t val)
{
  if (val<0)
  {
    return (val*-1);
  }
  else
  {
    return val;
  }

}
//ISR(INT0_vect)
   //   {    cli();
           //Engine_FLAG.BIT_FLAG= Engine_FLAG.BIT_FLAG +1; /* set the flag for the interrupt*/
          //flag=flag+1;
   //        EIFR=0x01; // set the flag for the interrupt
   //        sei();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ;
   //   }
