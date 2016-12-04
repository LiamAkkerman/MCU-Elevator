/* Include core modules */

#include "stm32f4xx.h"
#include "main.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_usart.h"

int main(void) {
	
	init();     									 //inittialises the all the GPIO pins in use
	char direction = 0;						//remembers the direction of motion of elevator before the elevator is stopped
	
	
	while(1) {
		update_inputs();		
		//button_display();					//this function was removed as it was primarily for debugging and not on the physical model. it may ne re-implimented later. 
																//it would display on lEDs which buttons had been pressed until the request was met
		bcd_display();
	
		
		if(butt_f1 || butt_f2_down || butt_f2_up || butt_f3 || butt_car_stop || butt_car_reset) { 			//if any button is activated
		
			if(butt_car_stop) {					//emergency stop activated. stops motion		 
				if(usart_on) {
					usart_message("EMERGENCY STOP ACTIVATED!\n");
				}
				
				move_stop();
																		
				if(moving_up) {								//store direction for afterwards, 1 for up, 2 for down, stays at zero if wasn't moving before
					direction = 1;
				}
				if(moving_down) {
					direction = 2;
				}										
  			butt_car_stop = 0;							 
			                     																																
				while(!butt_car_stop) {				//wait for the stop button to be pressed again
					update_critical();											
				}				
				butt_car_stop = 0;
        
				switch(direction) {
					case 1 : {
						move_up();
						break;
					}
					case 2 : {
						move_down();
						break;
					}
				}
				direction = 0;
			} 
			
			else if(butt_car_reset) {						//if the car needs to be reset
				butt_f1 = 0;														//reset all button presses
				butt_f2_down = 0;
				butt_f2_up = 0;
				butt_f3 = 0;
				butt_car_stop = 0;
				butt_car_reset = 0;	
				//button_display();
				if(usart_on) {
					usart_message("RESET\n");
				}
				
				move_stop();
				if(!loc_floor_1) {				//check to see if it needs to move
					move_down();						//if it isn't on the bottom floor already go down
					
					while(!loc_floor_1) {		//move until the bottom floor is reached						                 																															                                                                             
						update_location();
					}
					move_stop();
				}
				door_open_critical();
				
				while(!(butt_f1 || butt_f2_down || butt_f2_up || butt_f3)) {					//stay in this position until another request is made
					update_inputs();
				}
				
				door_close();
			}
			
			   																									
			switch(loc_cur) {         										 	//react according to which floor the carrige is at
				case 1 : {																		//it's on the 1st floor
					if(butt_f1 && loc_floor_1) {								//if a button calling the first floor was active and it is activiating the hall sensor, indicating the correct position to stop						
						move_stop();														
						if(usart_on) {
							usart_message("F1, arrived\n");
						}
						door_cycle();
						butt_f1 = 0;                       //turn off the buttons and open the doors
					}
     
					else if((butt_f2_down || butt_f2_up || butt_f3) && door_closed) {  //if a higher floor is called, it's not already moving, and it's ready to go					
						if(usart_on) {
							usart_message("F1, departing\n");
						}
						move_up();									//go up
					}
					break;
				}
				
				
				case 2 : {															                //if it's at the 2nd floor
					if(butt_f2_down && butt_f2_up && loc_floor_2) {				//if the carrige is on it's way down and someone at the second floor is going down, pick 'em up				
						move_stop();							
						if(usart_on) {
							usart_message("F2, arrived\n");
						}
						door_cycle();
						butt_f2_down = 0;
						butt_f2_up = 0;
					}
					else if(butt_f2_down && loc_floor_2 && !moving_up) {			//if the carrige is on it's way down and someone at the second floor is going down, pick 'em up					
						move_stop();												
						if(usart_on) {
							usart_message("F2, arrived\n");
						}
						door_cycle();
						butt_f2_down = 0;
					}
					else if(butt_f2_up && loc_floor_2 && !moving_down) {				//if the carrige is on it's way up and someone at the second floor is going up, pick 'em up
						move_stop();						
						if(usart_on) {
							usart_message("F2, arrived\n");
						}
						door_cycle();
						butt_f2_up = 0;
					}					
		
					else if(butt_f1 && door_closed) {					//if a lower floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F2, departing\n");
						}
						move_down();
					}		
					else if(butt_f3 && door_closed) {						//if a higher floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F2, departing\n");
						}
						move_up();
					}
					break;
				}
				
				
				case 3 : {													//it's on the 3rd floor
					if(butt_f3 && loc_floor_3) {	  	//if the 3rd floor was called
						move_stop();												
						if(usart_on) {
							usart_message("F3, arrived\n");
						}
						door_cycle();
						butt_f3 = 0;
					}	
					else if((butt_f1 || butt_f2_down || butt_f2_up) && door_closed) {			//if a lower floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F3, departing\n");
						}
						move_down();
					}
					break;
				}
			}
		}		
	}
	
	
}

char init(void) { 		//itianize all the pins and whatever else
	SystemInit();  			// initalize the system
	
	//Input pins
	TM_GPIO_Init(GPIOA, GPIO_Pin_13 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High );
	TM_GPIO_Init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, GPIO_Pin_10 | GPIO_Pin_12 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOD, GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	//output pins
	TM_GPIO_Init(GPIOA, GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, GPIO_Pin_11 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOD, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_15 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	//Initialize USART1 at 9600 baud, TX: PB6, RX: PB7
	TM_USART_Init(USART1, TM_USART_PinsPack_2, 9600);
	
	//initilize door LEDs
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);

	//initiilize motor
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_10);																				
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_14);

	return 0;
}

char update_critical(void) {					//updates stop and reset button
	if(!butt_car_stop && TM_GPIO_GetInputPinValue(GPIOA, GPIO_Pin_13)) {
		  butt_car_stop = 1;
	}

	if(!butt_car_reset && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_6)) {
		butt_car_reset = 1;
	}	
	
	return 0;
}

char update_location(void) {																	
	if(loc_floor_1 == TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_10)) {	//trigger switch checking for state changes of the location switches
		loc_floor_1 = !loc_floor_1;	
		loc_cur = 1;																									//they also set the current floor, or once it leaves it'll be the latest floor
		bcd_display();
	}
	if(loc_floor_2 == TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_12)) {	//location sensors are active low, thus the ==, not !=	
    loc_floor_2 = !loc_floor_2;	                                    //toggle the variable
		loc_cur = 2;
		bcd_display();
	}
	if(loc_floor_3 == TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_1)) {
    loc_floor_3 = !loc_floor_3;  //toggle the variable
		loc_cur = 3;
		bcd_display();
	}
	
	return 0;
}

char update_inputs(void) {				//poll all the pins for thier values
	update_critical();
	update_location();
	
	if(!butt_f1 && TM_GPIO_GetInputPinValue(GPIOB, GPIO_Pin_3)) {		//only update variable if the pin is high and the varibale isn't already set
		butt_f1 = 1;																									//the floor call buttons latch until the request has been satisfied																																												//both the buttons inside and out can be connected to this pin
	}
	if(!butt_f2_up && TM_GPIO_GetInputPinValue(GPIOB, GPIO_Pin_4)) { //the inside carriage button can be connected to both this pin, and the next one, using or gates
		butt_f2_up = 1;
	}
	if(!butt_f2_down && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_7)) { //connected to the outside F2 up or the inside F2
		butt_f2_down = 1;
	}
	if(!butt_f3 && TM_GPIO_GetInputPinValue(GPIOB, GPIO_Pin_5)) {		//connected inside and outside button
		butt_f3 = 1;
	}
	
	//TODO poll for USART password
	
	//button_display();

	return 0;
}

char move_up(void) { // controls the inputs to the H-bridge for motor to move up
	if(usart_on) {
		usart_message("UP, moving\n");
	}
	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_10);																					
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_14);	

	moving_up = 1;	
	moving_down = 0;
	
	return 0;
}

char move_down(void) {  // controls the inputs to the H-bridge for motor to move down
	if(usart_on) {
		usart_message("DOWN, moving\n");
	}
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_10);
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_14);		
	
	moving_up = 0;
	moving_down = 1;																			
	
	return 0;
} 

char move_stop(void) {   // controls the inputs to the H-bridge for motor to stop
	if(usart_on) {
		usart_message("STOP, stopping\n");
	}
		
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_10);																				
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_14);

	moving_up = 0;
	moving_down = 0;
	
	return 0;
}

char usart_message(char* str) {   // function sets out a message about elevator state through usart
	TM_USART_Puts(USART1, str);
	return 0;
}

char bcd_display(void){   // function to control the bcd display. Our 7-seg driver broke so we had to manually set pins
	switch(loc_cur) {
		case 1 : {
			//TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_5); //if we had the 7-seg IC
			//TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_3);
			
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_9);// B																	
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_11);// C  
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_7);// A 
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_13);// D
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_15);// E
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_8);// F
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_10);// G
			break;
		}
		case 2 : {
			//TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_5);
			//TM_GPIO_SetPinLowGPIOD, GPIO_Pin_3);
			
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_9);// B																
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_11);// C  
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_7);// A  
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_13);// D
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_15);// E
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_8);// F
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_10);// G	
			break;	
		}	
		case 3 : {
			//TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_5);
			//TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_3);
			
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_9);// B																
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_11);// C  
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_7);// A  
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_13);// D
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_15);// E
			TM_GPIO_SetPinHigh(GPIOE, GPIO_Pin_8);// F
			TM_GPIO_SetPinLow(GPIOE, GPIO_Pin_10);// G
			break;
		}		
	}
	
	return 0;
}

char door_open(void){  // fuction controls the led motion which simulates doors opening on the elevator
	if(usart_on) {
		usart_message("OPEN, doors\n");
	}
	
	door_closed = 0;
	
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){     //wait for a certain amount of time, constantly updating the inputs
		update_inputs();
		move_stop();													//it would sometimes randomly move during this, hence the stop directive
	}
	
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){			
		update_inputs();
		move_stop();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
		move_stop();
	}	

	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
		move_stop();
	}	
	
	return 0;
}

char door_open_critical(void) {					//doors open without updating buttons
	if(usart_on) {
		usart_message("OPEN, doors, without update\n");
	}

	door_closed = 0;
	
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<12*door_delay ; i++);
	
	
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<12*door_delay ; i++);
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<12*door_delay ; i++);

	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<12*door_delay ; i++);

	return 0;
}


char door_close(void){         // fuction controls the led motion which simulates doors closing on the elevator
	if(usart_on) {
		usart_message("CLOSE, doors\n");
	}
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
		move_stop();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
		move_stop();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
		move_stop();
	}		

	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
		move_stop();
	}	
	
	door_closed = 1;
	
	return 0;
}

char door_cycle(void) {	   //open doors, wait, then close doors
	door_open();
	for( int i = 0; i< 12*door_delay; i++);	
	door_close();
	
	return 0;
}
