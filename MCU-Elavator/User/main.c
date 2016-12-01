/* Include core modules */

#include "stm32f4xx.h"
#include "main.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_usart.h"

int main(void) {
	init();
	
	//char moving;
	
	
	while(1) {
		update_inputs();		
		button_display();
		bcd_display();
		
		/*
		if(butt_f1||butt_f2_down||butt_f2_up||butt_f3||butt_car_stop||butt_car_reset) { 			//if any button is activated
			moving = (moving_up|moving_down);
			if(!door_closed) { 																																	//close doors if they're open. probably only open from reset function.
				door_close();
			}
		*/
			if(butt_car_stop) {																																	//emergency stop activated. stops motion, but doors don't
				
				if(usart_on) {
					usart_message("EMERGENCY STOP ACTIVATED!\n");
				}
				char direction;																																		//1 for up, 0 for down
				if(moving_up) {
					direction = 1;
				}
				if(moving_down) {
					direction = 0;
				}
				//if(moving) {						
					move_stop();							
				//}
				butt_car_stop = 0;																																//TODO debounce button
				while(!butt_car_stop) {																														//wait for the stop button to be pressed again
					update_critical();																															//only update the stop and reset button
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
			} 
			
			else if(butt_car_reset) {																														//if the car needs to be reset
				butt_f1 = 0;																																			//reset all button presses
				butt_f2_down = 0;
				butt_f2_up = 0;
				butt_f3 = 0;
				butt_car_stop = 0;
				butt_car_reset = 0;	
				button_display();
				if(usart_on) {
					usart_message("RESET\n");
				}
				
				move_stop();
				if(!loc_floor_1) {																																//check to see if it needs to move
					move_down();																																		//if it isn't on the bottom floor already go downn
					
					while(!loc_floor_1) {																														//move until the bottom floor is reached						                 																															                                                                             
						update_location();
					}
					move_stop();
				}
				door_open_critical();
				
				while(!(butt_f1||butt_f2_down||butt_f2_up||butt_f3)) {
					update_inputs();
				}
				
				door_close();
			}
			
			
			
			//else switch(loc_cur) {   																										//react according to which floor the carrige is at
			switch(loc_cur) { 
				case 1 : {																																//it's on the 1st floor
					if(butt_f1 && loc_floor_1) {																							//if a button calling the first floor was active
						//if(moving) {
							move_stop();
						//}														
						button_display();
						if(usart_on) {
							usart_message("F1, arrived\n");
						}
						door_cycle();
						butt_f1 = 0;																													//turn off the buttons and open the doors

					}
					//else if((butt_f2_down||butt_f2_up||butt_f3)&&!moving&&door_closed) {  				//if a higher floor is called, it's not already moving, and it's ready to go
					else if((butt_f2_down||butt_f2_up||butt_f3)) { 
						if(usart_on) {
							usart_message("F1, departing\n");
						}
						move_up();																																																//go up
					}
					break;
				}
				
				
				case 2 : {																																								//if it's at the 2nd floor
					if(butt_f2_down && butt_f2_up && loc_floor_2) {															//if the carrige is on it's way down and someone at the second floor is going down, pick 'em up
						//if(moving) {
							/*
							for(int i = 0; i < motor_delay_2; i++) {															//to adjust to the correct position       TODO find the real value
								update_inputs();
							}
							*/
							move_stop();							
						//}
						
						button_display();
						if(usart_on) {
							usart_message("F2, arrived\n");
						}
						door_cycle();
						butt_f2_down = 0;
						butt_f2_up = 0;
					}
					else if(butt_f2_down && loc_floor_2 && !moving_up) {															//if the carrige is on it's way down and someone at the second floor is going down, pick 'em up
						//if(moving) {
							/*
							for(int i = 0; i < motor_delay_2; i++) {															//to adjust to the correct position       TODO find the real value
								update_inputs();
							}
							*/
							move_stop();							
						//}
						
						button_display();
						if(usart_on) {
							usart_message("F2, arrived\n");
						}
						door_cycle();
						butt_f2_down = 0;
					}
					else if(butt_f2_up && loc_floor_2 && !moving_down) {														//if the carrige is on it's way up and someone at the second floor is going up, pick 'em up
						//if(moving) {
							/*for(int i = 0; i < motor_delay_2; i++) {															//to adjust to the correct position       TODO find the real value
								update_inputs();
							}
							*/
							move_stop();						
						//}
						
						button_display();
						if(usart_on) {
							usart_message("F2, arrived\n");
						}
						door_cycle();
						butt_f2_up = 0;
					}					
					//else if(butt_f1&&!moving&&door_closed) {										 					//if a lower floor is called, it's not already moving, and it's ready to go
					else if(butt_f1) {
						if(usart_on) {
							usart_message("F2, departing\n");
						}
						move_down();
					}
					//else if(butt_f3&&!moving&&door_closed) {														//if a higher floor is called, it's not already moving, and it's ready to go
					else if(butt_f3) {	
						if(usart_on) {
							usart_message("F2, departing\n");
						}
						move_up();
					}
					break;
				}
				
				
				case 3 : {																																			//it's on the 3rd floor
					if(butt_f3 && loc_floor_3) {																										//if the 3rd floor was called
						//if(moving) {
							move_stop();							
						//}						
						
						button_display();
//						if(usart_on) {
//							usart_message("F3, arrived\n");
//						}
						door_cycle();
						butt_f3 = 0;
					}	
					//else if((butt_f1||butt_f2_down||butt_f2_up)&&!moving&&door_closed) {					//if a lower floor is called, it's not already moving, and it's ready to go
					else if(butt_f1 || butt_f2_down || butt_f2_up) {
//						if(usart_on) {
//							usart_message("F3, departing\n");
//						}
						move_down();
					}
					break;
				}
			}
		//}		
	}
	
	
}

char init(void) { 																																								//itianize all the pins and whatever else
	SystemInit();
	
	//Input pins
	TM_GPIO_Init(GPIOA, GPIO_Pin_13 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, GPIO_Pin_10 | GPIO_Pin_12 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOD, GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	//output pins
	TM_GPIO_Init(GPIOA, GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, GPIO_Pin_11 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOD, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	TM_GPIO_Init(GPIOB, GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_11 , TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	//Initialize USART1 at 9600 baud, TX: PB6, RX: PB7
	TM_USART_Init(USART1, TM_USART_PinsPack_2, 9600);
	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);

	
	return 0;
}

char update_critical(void) {																																			//inputs that always need to be updated
	if(!butt_car_stop && TM_GPIO_GetInputPinValue(GPIOA, GPIO_Pin_13)) {
		butt_car_stop = 1;
	}
	if(!butt_car_reset && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_6)) {
		butt_car_reset = 1;
	}	
	
	return 0;
}

char update_location(void) {
	if(loc_floor_1 == TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_10)) {																//trigger switch checking for state changes of the location switches
		loc_floor_1 = !loc_floor_1;																																		//toggle the variable
		loc_cur = 1;																																									//they also set the current floor, or once it leaves it'll be the latest floor
		bcd_display();
	}
	if(loc_floor_2 == TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_12)) {																//location sensors are active low, thus the ==, not !=
		loc_floor_2 = !loc_floor_2;
		loc_cur = 2;
		bcd_display();
	}
	if(loc_floor_3 == TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_1)) {
		loc_floor_3 = !loc_floor_3;
		loc_cur = 3;
		bcd_display();
	}
	
	return 0;
}

char update_inputs(void) {																																				//poll all the pins for thier values
	update_critical();
	update_location();
	
	
	if(!butt_f1 && TM_GPIO_GetInputPinValue(GPIOB, GPIO_Pin_3)) {																//only update variable if the pin is high and the varibale isn't already set
		butt_f1 = 1;																																							//the floor call buttons latch until the request has been satisfied
		TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_10);																																												//both the buttons inside and out can be connected to this pin
	}
	if(!butt_f2_up && TM_GPIO_GetInputPinValue(GPIOB, GPIO_Pin_4)) {														//the inside carriage button can be connected to both this pin, and the next one, possibly using diodes or or gates
		butt_f2_up = 1;
	}
	if(!butt_f2_down && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_7)) {													//connected to the outside F2 up and the inside F2
		butt_f2_down = 1;
	}
	if(!butt_f3 && TM_GPIO_GetInputPinValue(GPIOB, GPIO_Pin_5)) {																//connectedo inside and outside button
		butt_f3 = 1;
	}
	
	/*
	if(door_closed != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_2)) {
		door_closed = !door_closed;
	}
	*/
	
	button_display();
	
	//TODO poll for USART password

	return 0;
}




char move_up(void) {
	moving_up = 1;
	if(usart_on) {
		usart_message("UP, moving\n");
	}
	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_10);																					
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_14);			
	return 0;
}

char move_down(void) {
	moving_down = 1;
	if(usart_on) {
		usart_message("DOWN, moving\n");
	}
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_10);
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_14);																					
	
	return 0;
} 

char move_stop(void) {
	moving_up = 0;
	moving_down = 0;
	if(usart_on) {
		usart_message("STOP, stopping\n");
	}
	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_10);																				
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_14);
	
	return 0;
}



char usart_message(char* str) {
	TM_USART_Puts(USART1, str);
	return 0;
}

char bcd_display(void){
	switch(loc_cur) {
		case 1 : {
			TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_5);																				
			TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_3);
			break;
		}
		case 2 : {
			TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_5);
			TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_3);	
			break;	
		}	
		case 3 : {
			TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_5);
			TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_3);
			break;
		}		
	}
	
	return 0;
}

char door_open(void){
	if(usart_on) {
		usart_message("OPEN, doors\n");
	}
	
	door_closed = 0;
	
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){																					//wait for a certain amount of time, constantly updating the inputs
		update_inputs();
	}
	
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}	

	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}	
	
	return 0;
}

char door_open_critical(void) {																								//doors open without updating buttons
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


char door_close(void){
	if(usart_on) {
		usart_message("CLOSE, doors\n");
	}
	TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinLow(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}	
		
	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinHigh(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}		

	TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_2);
  TM_GPIO_SetPinHigh(GPIOD, GPIO_Pin_0);	
	TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_11);	
	TM_GPIO_SetPinLow(GPIOA, GPIO_Pin_15);
	for( int i = 0; i<door_delay ; i++){
		update_inputs();
	}	
	door_closed = 1;
	
	return 0;
}

char door_cycle(void) {																													//open doors, wait, then close doors
	door_open();
	for( int i = 0; i< 12*door_delay; i++);	
	door_close();
	
	return 0;
}

/*char check_password(void){																			//TODO make this work
	usart_message("Input Password\n");
	TM_USART_Gets(USART1, pass_array, sizeof(pass_array));
	
	for(int i = 0; i < 12; i++){
		
		if ( pass_array[0] == 'M' && pass_array[0] == 'S' && pass_array[0] == 'E' && pass_array[0] == ' ' && pass_array[0] == 'R' && pass_array[0] == 'o' && pass_array[0] == 'c' && pass_array[0] == 'k' && pass_array[0] == 's' && pass_array[0] == '!' ){
	   usart_on = 1;
		} 
		else{
		TM_USART_ClearBuffer(USART1);
		usart_message("Password Incorrect, Please enter again\n");		
		}
	}
	
	return 0;
}*/

char button_display(void) {
	if(butt_f1) {
		TM_GPIO_SetPinHigh(GPIOB, GPIO_Pin_11 );
	} else {
		TM_GPIO_SetPinLow(GPIOB, GPIO_Pin_11 );
	}
	
	if(butt_f2_down) {
		TM_GPIO_SetPinHigh(GPIOB, GPIO_Pin_12 );
	} else {
		TM_GPIO_SetPinLow(GPIOB, GPIO_Pin_12 );
	}
	
	if(butt_f2_up) {
		TM_GPIO_SetPinHigh(GPIOB, GPIO_Pin_14 );
	} else {
		TM_GPIO_SetPinLow(GPIOB, GPIO_Pin_14 );
	}
	
	if(butt_f3) {
		TM_GPIO_SetPinHigh(GPIOB, GPIO_Pin_10 );
	} else {
		TM_GPIO_SetPinLow(GPIOB, GPIO_Pin_10 );
	}
	
	return 0;
}	

