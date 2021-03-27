# SOFTWARE PWM
### Written by Ryan Baker
### Last editted on Oct 04, 2018
## Description
This project is written for both the MSP430G2553 and the MSP430F5529. An blinks with a frequency of approximately 1kHz. The percentage of the period that the LED is on each cycle is increased by 10% when the button is pressed. After 100% the percentage resets to 0%.
## Files
There are two folders named after the microcontroller they correspond to. In each folder there is a main.c that contains the code.
## Execution
To run this code, create a new project in Code Composer that uses the microcontroller that you have. I used CCS 8.2.0 for this. Add the code to your project by adding the file directly or copying and pasting the contents of the file into a new file. Debug and let CCS flash the code to your processor. If there are any updates, update your board. Once the code is running on your board, you will see the LEDs blinking at different frequencies.