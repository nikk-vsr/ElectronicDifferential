a : main.o ADC.o Timer.o gcc
        main.o ADC.o Timer.o : main.o ADC.h Timer.h gcc
   
//// This is used to run the makefile 

/*make -f makefile.mk
After make file is executed, enter a */
