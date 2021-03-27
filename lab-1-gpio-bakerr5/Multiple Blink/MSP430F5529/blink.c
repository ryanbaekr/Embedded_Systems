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
   P4OUT &= ~0x80;                  // set P4.7 to low
   P4DIR |= 0x80;                   // set P4.7 to output

   while(1)
   {
      P1OUT ^= 0x01;                // toggle P1.0
      P4OUT ^= 0x80;                // toggle P4.7
      __delay_cycles(500000);       // wait 500000 cycles
      P1OUT ^= 0x01;                // toggle P1.0
      __delay_cycles(500000);       // wait 500000 cycles
   }
}
