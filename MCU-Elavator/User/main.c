/* Include core modules */
#include "stm32f4xx.h"
#include "main.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_gpio.h"

int main(void) {
	init();
	
	
	
	while(1) {
		update_inputs();
		
		bool moving = (moving_up|moving_down);
		
		if(butt_f1||butt_f2_down||butt_f2_up||butt_f3||butt_car_stop) { 			//if any button is activated
			if(butt_car_stop) {
				butt_car_stop = 0;
				if(usart_on) {
					usart_message("EMERGENCY STOP ACTIVATED!");
				}
				if(moving) {						
					move_stop();							
				}
			}
			
			else switch(loc_cur) {   																										//react according to which floor the carrige is at
				case 1 : {																																//it's on the 1st floor
					if(butt_f1&&loc_floor_1) {														//if a button calling the first floor was active
						if(moving) {
							move_stop();
						}														
						butt_f1 = 0;																												//turn off the buttons and open the doors
						if(usart_on) {
							usart_message("F1, arrived");
						}
						open_door();
					}
					else if((butt_f2_down||butt_f2_up||butt_f3)&&!moving&&door_closed) {  				//if a higher floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F1, departing");
						}
						move_up();																																																//go up
					}
					break;
				}
				
				
				case 2 : {																																								//if it's at the 2nd floor
					if(butt_f2_down&&loc_floor_2&&moving_down) {															//if the carrige is on it's way down and someone at the second floor is going down, pick 'em up
						if(moving) {
							move_stop();							
						}
						butt_f2_down = 0;
						if(usart_on) {
							usart_message("F2, arrived");
						}
						open_door();
					}
					else if((butt_f2_up)&&loc_floor_2&&moving_up) {														//if the carrige is on it's way up and someone at the second floor is going up, pick 'em up
						if(moving) {
							move_stop();						
						}
						butt_f2_up = 0;
						if(usart_on) {
							usart_message("F2, arrived");
						}
						open_door();
					}					
					else if(butt_f1&&!moving&&door_closed) {										 					//if a lower floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F2, departing");
						}
						move_down();
					}
					else if(butt_f3&&!moving&&door_closed) {														//if a higher floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F2, departing");
						}
						move_up();
					}
					break;
				}
				
				
				case 3 : {																																								//it's on the 3rd floor
					if(butt_f3&&loc_floor_3) {																					//if the 3rd floor was called
						if(moving) {
							move_stop();							
						}						
						butt_f3 = 0;
						if(usart_on) {
							usart_message("F3, arrived");
						}
						open_door();
					}	
					else if((butt_f1||butt_f2_down||butt_f2_up)&&!moving&&door_closed) {				//if a lower floor is called, it's not already moving, and it's ready to go
						if(usart_on) {
							usart_message("F3, departing");
						}
						move_down();
					}
					break;
				}
			}
		}		
	}
	
	
	return 0;
}

bool init(void) { 																																								//itianize all the pins and whatever else
	SystemInit();
	
	//TODO change to the actual pins
	TM_GPIO_Init(GPIOD, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, GPIO_Pin_8 | GPIO_Pin_9 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOD, GPIO_Pin_2 | GPIO_Pin_4, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	return 0;
}


bool update_inputs(void) {																																				//poll all the pins for thier values
	if(loc_floor_1 != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_5)) {																//trigger switch checking for state changes of the location switches
		loc_floor_1 = ~loc_floor_1;																																		//toggle the variable
		loc_cur = 1;																																									//they also set the current floor, or once it leaves it'll be the latest floor
		bcd_display();
	}
	if(loc_floor_2 != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_6)) {
		loc_floor_2 = ~loc_floor_2;
		loc_cur = 2;
		bcd_display();
	}
	if(loc_floor_3 != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_7)) {
		loc_floor_3 = ~loc_floor_3;
		loc_cur = 3;
		bcd_display();
	}
	
	
	if(!butt_f1 && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_8)) {																//only update variable if the pin is high and the varibale isn't already set
		butt_f1 = 1;																																							//the floor call buttons latch until the request has been satisfied
																																															//both the buttons inside and out can be connected to this pin
	}
	if(!butt_f2_up && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_9)) {														//the inside carriage button can be connected to both this pin, and the next one, possibly using diodes or or gates
		butt_f2_up = 1;
	}
	if(!butt_f2_down && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_10)) {													//connected to the outside F2 up and the inside F2
		butt_f2_down = 1;
	}
	if(!butt_f3 && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_11)) {															//connectedo inside and outside button
		butt_f3 = 1;
	}
	if(!butt_car_stop && TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_8)) {
		butt_car_stop = 1;
	}
	
	if(door_closed != TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_9)) {
		door_closed = ~door_closed;
	}
	
	//TODO poll for USART password

	return 0;
}




bool move_up(void) {
	moving_up = 1;
	if(usart_on) {
		usart_message("UP, moving");
	}
	
	return 0;
}

bool move_down(void) {
	moving_down = 1;
	if(usart_on) {
		usart_message("DOWN, moving");
	}
	
	return 0;
}

bool move_stop(void) {
	moving_up = 0;
	moving_down = 0;
	if(usart_on) {
		usart_message("STOP, stopping");
	}
	
	return 0;
}

bool open_door(void) {
	//TODO get from Hriday
	return 0;
}

bool usart_message(char* str) {
	//TODO get from Hriday	
	return 0;
}

bool bcd_display(void){
	switch(loc_cur) {
		case 1 : {
			TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_12);
			TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_10);
			break;
		}
		case 2 : {
			TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_12);
			TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_10);	
			break;	
		}	
		case 3 : {
			TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_12);
			TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_10);
			break;
		}		
	}
	
	return 0;
}

bool door_open(void){
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}
		
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}
		
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}	
		
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}	

	return 0;
}

bool door_close(void){
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}
		
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}
		
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_12);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_11);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_10);
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_9);
	for( int i = 0; i<15000000 ; i++){
		update_inputs();
	}	
	
	return 0;
}
