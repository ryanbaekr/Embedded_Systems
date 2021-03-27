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

   // enable GPIO
   PM5CTL0 &= ~LOCKLPM5;

   // enable output to LED and turn it off
   P2SEL0 |= 0x01;                  // enable peripheral function on P1.0...
   P2SEL1 &= ~0x01;                 // ...by setting both of these bits
   P2DIR |= 0x01;                   // set P1.0 as an output
   P2OUT &= ~0x01;                  // set P1.0 low

   // enable input from button and pull-up resistor
   P1SEL0 &= ~0x02;                 // enable GPIO on P1.1
   P1DIR &= ~0x02;                  // set P1.1 as an input
   P1OUT |= 0x02;                   // set resistor as pull-up
   P1REN |= 0x02;                   // enable resistor

   // configure interrupts
   P1IE |= 0x02;                    // enable interrupts on P1.1
   P1IES |= 0x02;                   // enabling falling edge detection on P1.1
   P1IFG &= ~0x02;                  // clear the interrupt flag on P1.1

   // configure outmod
   //TB1CCTL0 = CCIE;                 // set to 0x10 (CCIE) for capture/compare interrupt enable
   TB1CCTL1 = OUTMOD_7;             // set to OUTMOD_7 for pwm reset/set
   TB1CCR0 = 1000;                  // set to 1000
   TB1CCR1 = 0;                     // set to 0
   TB1CTL = TBSSEL_2 + MC_1;        // set to use SMCLK (TBSSEL_2) and count to CCR0 in up mode
                                    // (MC_1)

   // configure timers
   TB0CCTL0 = CCIE;                 // set to 0x10 (CCIE) for capture/compare interrupt enable
   TB0CCR0 = 5000;                  // set to 5000
   TB0CTL = TBSSEL_1 + MC_1;        // set to use ACLK (TBSSEL_1) and count to CCR0 in up mode
                                    // (MC_1)

   // enable global interrupts
   __enable_interrupt();
}

#pragma vector=PORT1_VECTOR
// interrupt when button is pressed
__interrupt void Port_1(void)
{
   // start TA1
   TB0CTL = TBSSEL_1 + MC_1;        // set to use ACLK (TASSEL_1) and count to CCR0 in up mode
                                    // (MC_1)

   // temporarily disable interrupts on button
   P1IE &= ~0x02;                   // disable interrupts on P1.1
   P1IFG &= ~0x02;                  // clear the interrupt flag on P1.1

   // modify TA0
   TB1CCR1 += 100;
   if (TB1CCR1 >= 1000)
   {
      TB1CCR1 = 0;                  // reset CCR1 to 0% after 100% is reached
   }
}

#pragma vector=TIMER0_B0_VECTOR
// interrupt when timer reaches CCR0
__interrupt void Timer0_B0(void)
{
   // enable interrupts on button
   P1IE |= 0x02;                    // enable interrupts on P1.1
   P1IFG &= ~0x02;                  // clear the interrupt flag on P1.1

   // reset clock
   TB0CTL = 0x0000;
}
