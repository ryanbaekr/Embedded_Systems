#include "msp.h"

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
   P1REN |= 0x02;                   // pull up on P1.1
   P1DIR &= ~0x02;                  // set P1.1 to input

   while(1)
   {
      // if the button is not pressed
      if(P1IN & 0x02)
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
