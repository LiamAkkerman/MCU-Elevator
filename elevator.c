#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "Board_LED.h"                  // ::Board Support:LED
#include <stdio.h>
#include <stdbool.h>
#include "elevator.h"

int main(void) {
	
	while (1) {
		update_inputs();
		
	}
	
	return 0;
}

bool update_inputs() {
	bool result = 0;
	
	return result;
}
	
bool open_door() {
	bool result = 0;
	
	return result;
}
	
bool close_door(void) {
	bool result = 0;
	
	return result;
}
	
bool move_up(void) {
	bool result = 0;
	
	return result;
}
	
bool move_down(void) {
	bool result = 0;
	
	return result;
}
	
bool move_stop(void) {
	bool result = 0;
	
	return result;
}
	
