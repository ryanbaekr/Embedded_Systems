# BLINK
### Written by Ryan Baker
### Last editted on Sept 21, 2018
## Description
This project uses the MSP430G2553 on a breadboard, rather than a launchpad, to blink two LEDs at different frequencies
## Files
In the folder named MSP430G2553 there is a file named blink.c which contains the code.
## Execution
To run this code on an MSP430G2553 without the launchpad, I recommend first connecting the microprocessor to your computer using the launchpad. Run Code Composer and create a new project using the MSP430G2553. I used CCS 8.2.0 for this. Add the code to your project by adding the file directly or copying and pasting the contents of the file into a new file. Debug and let CCS flash the code to your processor. If there are any updates, update your board. Once the code is running on your board, you can unplug the launchpad and remove your MSP430G2553 from the launchpad. Plug the MSP430G2553 into your breadboard with jumpers running from 3.3V on the launchpad to pin 1 on the MSP430G2553, from GND to pin 20, from TEST to pin 17, and from RST to pin 16. Lastly, run an LED in series with a 1k ohm resistor from pin 2 to GND and again from pin 14 to GND. Now plug in your launchpad and your code will run. This can be seen in the GIF.