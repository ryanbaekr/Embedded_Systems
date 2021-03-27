#include "msp.h"

/**
 * blink.c
 * Author: Ryan Baker
 * Date: 09/21/18
 */

int main(void)
{
   // disable watchdog timer
   WDTCTL = WDTPW + WDTHOLD;        // watchdog timer stopped by enabling bit 7 (WDTHOLD) and using
                                    // the password (WDTPW)

   // enable input from button and output to other
   P1DIR = 0xFD;                    // input on P1.1, output on all other P1.y

   // turn off LED
   P1OUT &= ~0x01;                  // set P1.0 low

   // enable pull-up resistor on button
   P1OUT |= 0x02;                   // enable resistor
   P1REN |= 0x02;                   // set resistor to pull-up

   // configure interrupts
   P1IE |= 0x02;                    // enable interrupts on P1.1
   P1IES |= 0x02;                   // enabling falling edge detection on P1.1
   P1IFG &= ~0x02;                  // clear the interrupt flag on P1.1

   // configure timers
   TA0CCTL0 = CCIE;                 // set to 0x10 (CCIE) for capture/compare interrupt enable
   TA0CCR0 = 50000;                 // set to 50000
   TA0CTL = TASSEL_1 + MC_1;        // set to use ACLK (TASSEL_1) and count to CCR0 in up mode
                                    // (MC_1)

   // enable TA0 interrupt on the NVIC
   NVIC->ISER[0] = 1 << ((8) & 31);

   // the following comes from "MSP432P401 Demo - Software Port Interrupt Service on P1.1 from
   // LPM4"
      // Enable Port 1 interrupt on the NVIC
      NVIC->ISER[1] = 1 << ((PORT1_IRQn) & 31);

      // Configure Port J
      PJ->DIR |= (BIT0| BIT1 | BIT2 | BIT3);
      PJ->OUT &= ~(BIT0 | BIT1 | BIT2 | BIT3);

      // Enable PCM rude mode, which allows to device to enter LPM3 without waiting for peripherals
      PCM->CTL1 = PCM_CTL0_KEY_VAL | PCM_CTL1_FORCE_LPM_ENTRY;

      // Enable global interrupt
      __enable_irq();

      // Setting the sleep deep bit
      SCB->SCR |= (SCB_SCR_SLEEPDEEP_Msk);

      // Do not wake up on exit from ISR
      SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;

      // Ensures SLEEPONEXIT takes effect immediately
      __DSB();

      // Go to LPM4
      __sleep();
   //
}

// interrupt when button is pressed
void PORT1_IRQHandler(void)
{
   // toggle LED and temporarily disable interrupts on button
   P1IE &= ~0x02;                   // disable interrupts on P1.1
   P1IFG &= ~0x02;                  // clear the interrupt flag on P1.1
   P1OUT ^= 0x01;                   // toggle P1.0
}

// interrupt when timer reaches CCR0
void TA0_0_IRQHandler (void)
{
   // enable interrupts on button and reset clock
   P1IE |= 0x02;                    // enable interrupts on P1.1
}
