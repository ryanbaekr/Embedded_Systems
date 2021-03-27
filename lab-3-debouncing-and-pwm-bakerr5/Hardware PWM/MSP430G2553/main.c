#include <msp430.h>

/**
 * main.c
 * Author: Ryan Baker
 * Date: 10/04/18
 */

int main(void)
{
   // disable watchdog timer
   WDTCTL = WDTPW + WDTHOLD;        // watchdog timer stopped by enabling bit 7 (WDTHOLD) and using
                                    // the password (WDTPW)

   // enable output to LED and turn it off
   P1SEL |= 0x40;                   // enable peripheral function on P1.6...
   P1SEL2 &= ~0x40;                 // ...by setting both of these bits
   P1DIR |= 0x40;                   // set P1.6 as an output
   P1OUT &= ~0x40;                  // set P1.6 low

   // enable input from button and pull-up resistor
   P1SEL &= ~0x08;                  // enable GPIO on P1.3
   P1DIR &= ~0x08;                  // set P1.3 as an input

   // configure interrupts
   P1IE |= 0x08;                    // enable interrupts on P1.3
   P1IES |= 0x08;                   // enabling falling edge detection on P1.3
   P1IFG &= ~0x08;                  // clear the interrupt flag on P1.3

   // configure outmod
   TA0CCTL0 = CCIE;                 // set to 0x10 (CCIE) for capture/compare interrupt enable
   TA0CCTL1 = OUTMOD_7;             // set to OUTMOD_7 for pwm reset/set
   TA0CCR0 = 1000;                  // set to 1000
   TA0CCR1 = 0;                     // set to 0
   TA0CTL = TASSEL_2 + MC_1;        // set to use SMCLK (TASSEL_2) and count to CCR0 in up mode
                                    // (MC_1)

   // configure timers
   TA1CCTL0 = CCIE;                 // set to 0x10 (CCIE) for capture/compare interrupt enable
   TA1CCR0 = 20000;                 // set to 20000
   TA1CTL = TASSEL_2 + MC_1;        // set to use SMCLK (TASSEL_2) and count to CCR0 in up mode
                                    // (MC_1)

   // enable global interrupts
   __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
// interrupt when button is pressed
__interrupt void Port_1(void)
{
   // start TA1
   TA1CTL = TASSEL_1 + MC_1;        // set to use ACLK (TASSEL_1) and count to CCR0 in up mode
                                    // (MC_1)

   // temporarily disable interrupts on button
   P1IE &= ~0x08;                   // disable interrupts on P1.3
   P1IFG &= ~0x08;                  // clear the interrupt flag on P1.3

   // modify TA0
   TA0CCR1 += 100;
   if (TA0CCR1 >= 1000)
   {
      TA0CCR1 = 0;                  // reset CCR1 to 0% after 100% is reached
   }
}

#pragma vector=TIMER0_A0_VECTOR
// interrupt when timer reaches CCR0
__interrupt void Timer0_A0(void)
{
   // enable interrupts on button
   P1IE |= 0x08;                    // enable interrupts on P1.3
   P1IFG &= ~0x08;                  // clear the interrupt flag on P1.3

   // reset clock
   TA1CTL = 0x0000;
}
