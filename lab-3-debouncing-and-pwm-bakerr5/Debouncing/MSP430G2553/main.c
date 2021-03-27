#include <msp430.h>

/**
 * main.c
 * Author: Ryan Baker
 * Date: 10/04/18
 */

void main(void)
{
   // disable watchdog timer
   WDTCTL = WDTPW + WDTHOLD;        // watchdog timer stopped by enabling bit 7 (WDTHOLD) and using
                                    // the password (WDTPW)

   // enable output to LED and turn it off
   P1SEL &= ~0x01;                  // enable GPIO on P1.0
   P1DIR |= 0x01;                   // set P1.0 as an output
   P1OUT &= ~0x01;                  // set P1.0 low

   // enable input from button and pull-up resistor
   P1SEL &= ~0x08;                  // enable GPIO on P1.3
   P1DIR &= ~0x08;                  // set P1.3 as an input

   // configure interrupts
   P1IE |= 0x08;                    // enable interrupts on P1.3
   P1IES |= 0x08;                   // enabling falling edge detection on P1.3
   P1IFG &= ~0x08;                  // clear the interrupt flag on P1.3

   // configure timers
   TA0CCTL0 = CCIE;                 // set to 0x10 (CCIE) for capture/compare interrupt enable
   TA0CCR0 = 50000;                 // set to 50000
   TA0CTL = TASSEL_1 + MC_1;        // set to use ACLK (TASSEL_1) and count to CCR0 in up mode
                                    // (MC_1)

   // enable global interrupts
   __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
// interrupt when button is pressed
__interrupt void Port_1(void)
{
   // toggle LED and temporarily disable interrupts on button
   P1IE &= ~0x08;                   // disable interrupts on P1.3
   P1IFG &= ~0x08;                  // clear the interrupt flag on P1.3
   P1OUT ^= 0x01;                   // toggle P1.0
}

#pragma vector=TIMER0_A0_VECTOR
// interrupt when timer reaches CCR0
__interrupt void Timer_A(void)
{
   // enable interrupts on button and reset clock
   P1IE |= 0x08;                    // enable interrupts on P1.3
}
