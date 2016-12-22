// monitor a digital input pin PORTXbits.RXn for changes
// Usually connect a button to this pin but any square wave input will do. 

#include "buttons.h"

// global variable holds the current state of the button. Initially assumed to be off.
//
// Usually you won't want to access this since we are interested in edges.
// If you do want to use it in you main.c function, you must have a line
//
// declare extern unsigned char last_switch1_edge; 
//
// in main.c so that the compiler knows where it is
// 
unsigned char last_switch1_value = 0;    // last button value, initalized to low 
unsigned char last_switch2_value = 0;    // last button value, initalized to low 
unsigned char last_switch3_value = 0;    // last button value, initalized to low
unsigned char last_switch4_value = 0;
unsigned char last_switch5_value = 0;
unsigned char last_switch6_value = 0;
unsigned char last_switch7_value = 0;
unsigned char last_hall1_value = 1;
unsigned char last_hall2_value = 1;
unsigned char last_hall3_value = 1;

// returns 0 if no edge has happened
// returns 1 at a rising edge
// returns 2 at a falling edge


unsigned char monitor_switch1_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_switch1_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge
    
  
      
    if (last_switch1_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch1_value = 1;   // save current switch value (on)
        has_switch1_changed = 1;  // found a rising edge
    } 
    if (last_switch1_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch1_value = 0;   // save current switch value (off)
        has_switch1_changed = 2;  // found a falling edge
    } 

    return has_switch1_changed;
    }



// returns 0 if no edge has happened
// returns 1 at a rising edge
// returns 2 at a falling edge
//
//
unsigned char monitor_switch2_for_edges(unsigned char digitalinputpin) 
{ 

      
    unsigned char has_switch2_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge

    if (last_switch2_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch2_value = 1;   // save current switch value (on)
        has_switch2_changed = 1;  // found a rising edge
    } 
    if (last_switch2_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch2_value = 0;   // save current switch value (off)
        has_switch2_changed = 2;  // found a falling edge
    } 

    return has_switch2_changed; 
} 
unsigned char monitor_switch3_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_switch3_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge

    if (last_switch3_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch3_value = 1;   // save current switch value (on)
        has_switch3_changed = 1;  // found a rising edge
    } 
    if (last_switch3_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch3_value = 0;   // save current switch value (off)
        has_switch3_changed = 2;  // found a falling edge
    } 

    return has_switch3_changed;
    }
unsigned char monitor_switch4_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_switch4_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge

    if (last_switch4_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch4_value = 1;   // save current switch value (on)
        has_switch4_changed = 1;  // found a rising edge
    } 
    if (last_switch4_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch4_value = 0;   // save current switch value (off)
        has_switch4_changed = 2;  // found a falling edge
    } 

    return has_switch4_changed;
    }
unsigned char monitor_switch5_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_switch5_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge

    if (last_switch5_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch5_value = 1;   // save current switch value (on)
        has_switch5_changed = 1;  // found a rising edge
    } 
    if (last_switch5_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch5_value = 0;   // save current switch value (off)
        has_switch5_changed = 2;  // found a falling edge
    } 

    return has_switch5_changed;
    }
unsigned char monitor_switch6_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_switch6_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge

    if (last_switch6_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch6_value = 1;   // save current switch value (on)
        has_switch6_changed = 1;  // found a rising edge
    } 
    if (last_switch6_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch6_value = 0;   // save current switch value (off)
        has_switch6_changed = 2;  // found a falling edge
    } 

    return has_switch6_changed;
    }
unsigned char monitor_switch7_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_switch7_changed = 0;  // 0 = no change; 1 = rising edge; 2 = falling edge

    if (last_switch7_value == 0 && digitalinputpin) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_switch7_value = 1;   // save current switch value (on)
        has_switch7_changed = 1;  // found a rising edge
    } 
    if (last_switch7_value == 1 && !digitalinputpin) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_switch7_value = 0;   // save current switch value (off)
        has_switch7_changed = 2;  // found a falling edge
    } 

    return has_switch7_changed;
    }

unsigned char monitor_hall1_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_hall1_changed = 0;  // 0 = no change; 1 = rising edge; 1 = falling edge

    if (last_hall1_value == 1 && digitalinputpin == 1) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_hall1_value = 1;   // save current switch value (on)
        has_hall1_changed = 0;  // no change
    } 
    if (last_hall1_value == 1 && digitalinputpin == 0) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall1_value = 0;   // save current switch value (off)
        has_hall1_changed = 2;  // found a falling edge
    } 
    if (last_hall1_value == 0 && digitalinputpin == 1) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall1_value = 1;   // save current switch value (off)
        has_hall1_changed = 1;  // found a rising edge
    }
    if (last_hall1_value == 0 && digitalinputpin == 0) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall1_value = 0;   // save current switch value (off)
        has_hall1_changed = 0;  // no change
    }

    return has_hall1_changed;
    }
unsigned char monitor_hall2_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_hall2_changed = 0;  // 0 = no change; 1 = rising edge; 1 = falling edge

    if (last_hall2_value == 1 && digitalinputpin == 1) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_hall2_value = 1;   // save current switch value (on)
        has_hall2_changed = 0;  // no change
    } 
    if (last_hall2_value == 1 && digitalinputpin == 0) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall2_value = 0;   // save current switch value (off)
        has_hall2_changed = 2;  // found a falling edge
    } 
    if (last_hall2_value == 0 && digitalinputpin == 1) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall2_value = 1;   // save current switch value (off)
        has_hall2_changed = 1;  // found a rising edge
    }
    if (last_hall2_value == 0 && digitalinputpin == 0) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall2_value = 0;   // save current switch value (off)
        has_hall2_changed = 0;  // no change
    }

    return has_hall2_changed;
    }
unsigned char monitor_hall3_for_edges(unsigned char digitalinputpin) 
{ 

    unsigned char has_hall3_changed = 0;  // 0 = no change; 1 = rising edge; 1 = falling edge

    if (last_hall3_value == 1 && digitalinputpin == 1) 
    {                // rising edge detected if digitalinputpin is 1 (on) 
        last_hall3_value = 1;   // save current switch value (on)
        has_hall3_changed = 0;  // no change
    } 
    if (last_hall3_value == 1 && digitalinputpin == 0) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall3_value = 0;   // save current switch value (off)
        has_hall3_changed = 2;  // found a falling edge
    } 
    if (last_hall3_value == 0 && digitalinputpin == 1) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall3_value = 1;   // save current switch value (off)
        has_hall3_changed = 1;  // found a rising edge
    }
    if (last_hall3_value == 0 && digitalinputpin == 0) 
    {                // falling edge detected if digitalinputpin is 0 (off) 
        last_hall3_value = 0;   // save current switch value (off)
        has_hall3_changed = 0;  // no change
    }

    return has_hall3_changed;
    }