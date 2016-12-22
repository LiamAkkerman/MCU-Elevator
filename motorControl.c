#include <stdio.h>          				// library containing printf() function
#include <xc.h>								// PIC control functions
#include "motorControl.h"

void setMotorFwd(void){
    PORTAbits.RA3 = 1; 
    PORTCbits.RC2 = 0;
}

void setMotorBack(void){
    PORTAbits.RA3 = 0; 
    PORTCbits.RC2 = 1;
}

void setMotorStop(void){
    PORTAbits.RA3 = 0; 
    PORTCbits.RC2 = 0;
}
