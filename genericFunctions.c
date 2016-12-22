// *******************************************************************
// GenericFunctions.c
// Final Version
// Remi Michalowski and Mahsa Kohansal
// April 2015
// *******************************************************************
//DELAY COMMAND FUNCTIONS

#include <xc.h>
#include "genericFunctions.h"		// My generic functions (delay)


//Delay function set by miliseconds
void WaitSet_ms(float miliSec)
{
int delayCycles;
delayCycles = miliSec*100;
int  i = 0;
for(i=0; i<=delayCycles; i++)
   {
NOP();
    _delay(80ul);
NOP();
   }
}

//Delay function set by seconds
void WaitSet_s(float Sec)
{
float delayCycles;
delayCycles = Sec * 80; //Each second is 80 delay cycles
int  i = 0;
for(i=0; i<=delayCycles; i++)
   {
    _delay(100000ul);
   }
}