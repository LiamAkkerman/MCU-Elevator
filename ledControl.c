
#include <xc.h>								// PIC control functions
#include "ledControl.h"
#include "..\Common\genericFunctions.h" 	// Delays

// Inner door led (active low)
void LED1(int state){
    PORTAbits.RA4 = state;
}
void LED2(int state){
    PORTAbits.RA7 = state;
}
void LED3(int state){
    PORTEbits.RE0 = state;
}
// Outer door led (active low)
void LED4(int state){
    PORTCbits.RC3 = state;
}


//Display test pattern
void segUp(void){
    seg7(14);
    WaitSet_ms(50);
    seg7(19);
    WaitSet_ms(50);
    seg7(17);
    WaitSet_ms(50);
    seg7(18);
    WaitSet_ms(50);
    seg7(11);
    WaitSet_ms(50);
    seg7(10);
}

//Display test pattern
void seg2up(void){
    
    
    seg7(14);
    WaitSet_ms(25);
    seg7(15);
    WaitSet_ms(25);
    seg7(17);
    WaitSet_ms(25);
    seg7(12);
    WaitSet_ms(25);
    seg7(11);
    WaitSet_ms(25);
    }

//Display test pattern
void seg2up2(void){
    //---------CBA----
    PORTD = 0b01000000;
    //------------GFED
    PORTB = 0b00000101;
    WaitSet_ms(300);
    //---------CBA----
    PORTD = 0b01000000;
    //------------GFED
    PORTB = 0b00001100;
    WaitSet_ms(300);
    //---------CBA----
    PORTD = 0b01010000;
    //------------GFED
    PORTB = 0b00000100;
    WaitSet_ms(300);
}

//Display test pattern
void segDown(void){
    seg7(11);
    WaitSet_ms(100);
    seg7(17);
    WaitSet_ms(100);
    seg7(14);
    WaitSet_ms(100);
    seg7(10);
}

//Function displays selected integer as a digit on a 7 segment display
void seg7(int digit){
    
switch(digit){
        case 0 : {
            PORTD = 0b00000000;
            PORTB = 0b00001000;
        }
        break;
        case 1 :{
            PORTD = 0b00010000;
            PORTB = 0b00001111;
        }
        break;
        case 2 :{
            PORTD = 0b01000000;
            PORTB = 0b00000100;
        }
        break;
        case 3 :{
            PORTD = 0b00000000;
            PORTB = 0b00000110;
        }
        break;
        case 4 :{
            PORTD = 0b00010000;
            PORTB = 0b00000011;
        }
        break;
        case 5 :{
            PORTD = 0b00100000;
            PORTB = 0b00000010;
        }
        break;
        case 6 :{
            PORTD = 0b00110000;
            PORTB = 0b00000000;
        }
        break;
        case 7 :{
            PORTD = 0b00000000;
            PORTB = 0b00001111;
        }
        break;
        case 8 :{
            PORTD = 0b00000000;
            PORTB = 0b00000000;
        }
        break;
        case 9 :{
            PORTD = 0b00000000;
            PORTB = 0b00000010;
        }
        break;
        case 10 :{              //All off
            PORTD = 0b01110000;
            PORTB = 0b00001111;
        }
        break;
        case 11 :{              //"A" top bar only
            PORTD = 0b01100000;
            PORTB = 0b00001111;
        }
        break;
        case 12 :{              //"B" top right bar only
            PORTD = 0b01010000;
            PORTB = 0b00001111;
        }
        break;
        case 13 :{              //"C" bottom right bar only
            PORTD = 0b00110000;
            PORTB = 0b00001111;
        }
        break;
        case 14 :{              //"D" low bar only
            PORTD = 0b01110000;
            PORTB = 0b00001110;
        }
        break;
        case 15 :{              //"E" bottom left bar only
            PORTD = 0b01110000;
            PORTB = 0b00001101;
        }
        break;
        case 16 :{              //"F" top left bar only
            PORTD = 0b01110000;
            PORTB = 0b00001011;
        }
        break;
        case 17 :{              //"G" mid bar only
            PORTD = 0b01110000;
            PORTB = 0b00000111;
        }
        break;
        case 18 :{              //Top vertical bars only
            PORTD = 0b01010000;
            PORTB = 0b00001011;
        }
        break;
        case 19 :{              //Bottom vertical bars only
            PORTD = 0b00110000;
            PORTB = 0b00001101;
        }
        break;
       
        
        
        default :               //"E"
            {
            PORTD = 0b01100000;
            PORTB = 0b00000000;
        }
}
}