//************************************************************************************
//File: elevatorMain.c
//Programmer: Remi Michalowski
//Purpose: Elevator model control code
 //************************************************************************************
 
#include <stdio.h>          				// library containing printf() function
#include <xc.h>								// PIC control functions
#include "..\Common\configuration_bits.h" 	// Configuration libray for proramming MCU
#include "..\Common\osc.h"            		// library for set_osc_32MHz()
#include "motorControl.h"                   // Motor control functions
#include "ledControl.h"                     // Door and 7 segment led's
#include "..\Common\genericFunctions.h" 	// Delays
#include "..\Common\buttons.h"

#define _XTAL_FREQ 32000000 				// operating at 32 MHz

void main(void)
{
    set_osc_32MHz();                // TCY = 500 ns
   //Motor pins 
    WaitSet_s(1);

    // GPIO settings: "0" is output, "1" is input
    TRISA = 0b00000000;             // RA3 "1A motor signal"
    TRISB = 0b00010000;             // RB0 "D",RB1 "E",RB2 "F", RB3 "G" (output),RB4 "hall 1"
    TRISC = 0b00110011;             // RC0 "F3",RC1 "F3",RC2 "2A motor signal",RC4 "Stop",RcC5 "Reset"
    TRISD = 0b10001111;             // RD0 "F2",RD1 "F2D",RD2 "hall 3",RD3 "F2U",RD4 "A",RD5 "B",RD6 "C" (output),RD7 "hall 2"
    TRISE = 0b00000000;

    PORTAbits.RA3 = 0;              // Motor signal 1A initialized  low (off)
    PORTCbits.RC2 = 0;              // Motor signal 2A initialized  low (off)
    
    //Door LED's initialized "off" (active low)
    // LED1 is inner most led, LED 4 is outer most
    LED1(1);
    LED2(1);
    LED3(1);
    LED4(1);
    
    unsigned char buttonF1 = 0;
    unsigned char buttonF2D = 0;        //Floor 2 Down
    unsigned char buttonF2U = 0;        //Floor 2 Up
    unsigned char buttonF2 = 0;
    unsigned char buttonF3 = 0;
    unsigned char buttonStop = 0;
    unsigned char buttonReset = 0;
    unsigned char hall1 = 0;            //Hall effect sensor Floor 1
    unsigned char hall2 = 0;            //Hall effect sensor Floor 2
    unsigned char hall3 = 0;            //Hall effect sensor Floor 3
    
 
    /*
     // Hall sensor test loop
     // 7 segment display's current floor when hall sensor tripped
    while(1){
        hall1 = monitor_hall1_for_edges(PORTBbits.RB4);
        hall2 = monitor_hall2_for_edges(PORTDbits.RD7);
        hall3 = monitor_hall3_for_edges(PORTDbits.RD2);
        if (hall1 == 1){
            seg7(3);
        }
        if (hall2 == 1){
            seg7(2);
        }
        if (hall3 == 1){
            seg7(1);
        }
    }
    */
    
    /*
     // Outside button test loop
    while(1){
        buttonF1 = monitor_switch1_for_edges(PORTCbits.RC0);
        buttonF2D = monitor_switch2_for_edges(PORTDbits.RD1);
        buttonF2U = monitor_switch3_for_edges(PORTDbits.RD3);
        buttonF2 = monitor_switch4_for_edges(PORTDbits.RD0);
        buttonF3 = monitor_switch5_for_edges(PORTCbits.RC1);
        buttonStop = monitor_switch6_for_edges(PORTCbits.RC4);
        buttonReset = monitor_switch7_for_edges(PORTCbits.RC5);
        
        if (buttonF1 == 1){
            seg7(1);
        }
        if (buttonF2D == 1){
            seg7(2);
        }
        if (buttonF2U == 1){
            seg7(3);
        }
        if (buttonF2 == 1){
            seg7(7);
        }
        if (buttonF3 == 1){
            seg7(4);
        }
        if (buttonReset == 1){
            seg7(5);
        }
        if (buttonStop == 1){
            seg7(6);
        }
    }
    */
    
    
    
    /*
    // 7 Segment display test loop
    // Runs loop from "0" to "9" and "E" for digit requested out of bounds
    while(1){
        
        for(int i = 0;i<11;i++){
            seg7(i);
            WaitSet_s(0.5);  
        }
    }
      */
    
    /*
    // Carriage button input test loop
    while(1){
        
        if (PORTCbits.RC0 == 1)
            LED1(0);       
        else
            LED1(1);
        
        if (PORTCbits.RC1 == 1)
            LED2(0);       
        else
            LED2(1);
        
        if (PORTDbits.RD0 == 1)
            LED3(0);       
        else
            LED3(1);
        
    }
    */
    
    /*
    // Door LED test loop
    while(1){
       LED2(1); 
       LED1(0); 
       WaitSet_ms(100);
       LED1(1); 
       LED2(0);
       WaitSet_ms(100);
       LED2(1); 
       LED3(0);
       WaitSet_ms(100);
       LED3(1); 
       LED4(0);
       WaitSet_ms(100);
       LED4(1); 
       LED3(0);
       WaitSet_ms(100);
       LED3(1); 
       LED2(0);
       WaitSet_ms(100);
    }
   */
    
    //Motor test loop
    /*
    while(1){
    setMotorFwd();
    WaitSet_s(1);
    setMotorBack();
    WaitSet_s(1);
    setMotorStop();
    WaitSet_s(1);
    }
     */
    
    
    

}