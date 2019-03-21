# MCU-Elevator
An elevator system based around a STM32F4VGT6 microcontroller board

Place the 00-STM32_SVD, 00-STM32F4xx_HAL_DRIVERS, 00-STM32F4xx_STANDARD_PERIPHERAL_DRIVERS, and 00-STM32F429_LIBRARIES folders in the root of this repository.

The code is in \MCU-Elevator-Code\MCU-Elavator\User\

**This is a scale model of an elevator system** 

 * LED indicators for the states of the elevator doors, determines whether the doors are closed or open   
 * LED indicators for the requested floors after a button press for the corresponding floor  
 * Priority queue for the floor-button presses
 * Able to stop the elevator on desired floors (if the floor button is pressed)

