typedef struct{
uint8_t TimerEnable;
uint8_t TimerMode;
uint8_t TimerChannel;
uint8_t ClockSource;
uint8_t ISREnable;
uint8_t Interval;

}TimerConfig_t;  // new user defined struct datatype TimerConfig_t 

typdef enum{TIMER0,TIMER1, TIMER2, MAX_TIMERS}Timer_Register_t;  // new user defined enum data type name Timer_Register




