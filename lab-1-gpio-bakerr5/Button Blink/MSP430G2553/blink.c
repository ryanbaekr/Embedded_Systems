#include <msp430.h>

/**
 * blink.c
 * Author: Ryan Baker
 * Date: 09/21/18
 */

void main(void)
{
   WDTCTL = WDTPW | WDTHOLD;        // stop watchdog timer
   P1OUT &= ~0x01;                  // set P1.0 to low
   P1DIR |= 0x01;                   // set P1.0 to output
   P1REN |= 0x08;                   // pull up on P1.3
   P1DIR &= ~0x08;                  // set P1.3 to input

   while(1)
   {
      // if the button is not pressed
      if(P1IN & 0x08)
      {
          P1OUT &= ~0x01;           // set P1.0 to low
      }
      // otherwise
      else
      {
          P1OUT |= 0x01;            // set P1.0 to high
      }
   }
}
