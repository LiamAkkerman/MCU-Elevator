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
		
		bool moving = moving_up||moving_down;
		
		if(butt_f1_up||butt_f2_down||butt_f2_up||butt_f3_down||butt_car_f1||butt_car_f2||butt_car_f3||butt_car_stop) {
			if(butt_car_stop) {
				butt_car_stop = 0;
				if(usart_on) {
					usart_message("EMERGENCY STOP ACTIVATED!");
				}
				if(moving) {						
					move_stop();							
				}
			}
			else switch(loc_cur) {
				case 1 : {
					if((butt_f1_up||butt_car_f1)&&loc_floor_1) {
						if(moving_up||moving_down) {
							move_stop();
						}														
						butt_f1_up = 0;
						butt_car_f1 = 0;
						if(usart_on) {
							usart_message("F1, arrived");
						}
						open_door();
					}
					else if((butt_f2_down||butt_f2_up||butt_f3_down||butt_car_f2||butt_car_f3)&&!moving&&door_closed) {
						if(usart_on) {
							usart_message("F1, departing");
						}
						move_up();
					}
					break;
				}
				
				
				case 2 : {
					if((butt_f2_down||butt_car_f2)&&loc_floor_2&&moving_down) {
						if(moving) {
							move_stop();							
						}
						butt_f2_down = 0;
						butt_car_f2 = 0;
						if(usart_on) {
							usart_message("F2, arrived");
						}
						open_door();
					}
					else if((butt_f2_up||butt_car_f2)&&loc_floor_2&&moving_up) {
						if(moving) {
							move_stop();						
						}
						butt_f2_up = 0;
						butt_car_f2 = 0;
						if(usart_on) {
							usart_message("F2, arrived");
						}
						open_door();
					}					
					else if((butt_f1_up||butt_car_f1)&&!moving&&door_closed) {
						if(usart_on) {
							usart_message("F2, departing");
						}
						move_down();
					}
					else if((butt_f3_down||butt_car_f3)&&!moving&&door_closed) {
						if(usart_on) {
							usart_message("F2, departing");
						}
						move_up();
					}
					break;
				}
				
				
				case 3 : {
					if((butt_f3_down||butt_car_f3)&&loc_floor_3) {
						if(moving_up||moving_down) {
							move_stop();							
						}						
						butt_f3_down = 0;
						butt_car_f3 = 0;
						if(usart_on) {
							usart_message("F3, arrived");
						}
						open_door();
					}	
					else if((butt_f1_up||butt_car_f1||butt_f2_down||butt_f2_up||butt_car_f2)&&!moving&&door_closed) {
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

bool init(void) {
	SystemInit();
	
	TM_GPIO_Init(GPIOD, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOC, GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 , TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	TM_GPIO_Init(GPIOD, GPIO_Pin_2 | GPIO_Pin_4, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
	
	return 0;
}


bool update_inputs(void) {
	if(loc_floor_1 != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_5)) {
		loc_floor_1 = !loc_floor_1;
		loc_cur = 1;
	}
	if(loc_floor_2 != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_6)) {
		loc_floor_2 = !loc_floor_2;
		loc_cur = 2;
	}
	if(loc_floor_3 != TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_7)) {
		loc_floor_3 = !loc_floor_3;
		loc_cur = 3;
	}
	
	
	if(!butt_f1_up && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_8)) {
		butt_f1_up = 1;
	}
	if(!butt_f2_up && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_9)) {
		butt_f2_up = 1;
	}
	if(!butt_f2_down && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_10)) {
		butt_f2_down = 1;
	}
	if(!butt_f3_down && TM_GPIO_GetInputPinValue(GPIOD, GPIO_Pin_11)) {
		butt_f3_down = 1;
	}
	
	
	if(!butt_car_f1 && TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_5)) {
		butt_car_f1 = 1;
	}
	if(!butt_car_f2 && TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_6)) {
		butt_car_f2 = 1;
	}
	if(!butt_car_f3 && TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_7)) {
		butt_car_f3 = 1;
	}
	if(!butt_car_stop && TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_8)) {
		butt_car_stop = 1;
	}
	
	if(door_closed != TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_9)) {
		door_closed = !door_closed;
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
	
	return 0;
}

bool usart_message(char* str) {
		
	return 0;
}

