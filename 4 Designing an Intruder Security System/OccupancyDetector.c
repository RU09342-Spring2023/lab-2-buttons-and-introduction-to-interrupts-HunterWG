/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Hunter Geitz
 */
#include <msp430.h>

int main(void)
{
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here
// Stop watchdog timer
WDTCTL = WDTPW | WDTHOLD;
PM5CTL0 &= ~LOCKLPM5;

// Set green LED pin (P1.0) as an output
P6DIR |= BIT6;
// Set red LED pin (P1.0) as an output
P1DIR |= BIT0;
// Configure P2.3 to an Input
P2DIR &= ~BIT3;

// Configure P4.1 to an Input
P4DIR &= ~BIT1;
P4REN |= BIT1;                  // Enable resistor on P4.1
P4OUT |= BIT1;
P2REN |= BIT3;                  // Enable resistor on P2.3
P2OUT |= BIT3;

P1OUT &= ~BIT0;                         // Clear P1.0 output latch for a defined power-on state
P6OUT &= ~BIT6;                         // Clear P1.0 output latch for a defined power-on state

char state = ARMED_STATE; // Initializing first state as ARMED state
int totaltime = 0;        // Initializing time
while(1)
{
  switch (state) {


    case ARMED_STATE:
    {
        if (!(P2IN & BIT3))                   // If S2 (P2.3) is pressed
        {
            totaltime = 0;
            state = WARNING_STATE;           // Go to WARNING state
        }
        else {
                P1OUT &= ~BIT0;             // Red LED turns off
                P6OUT ^= BIT6;              // Toggle P6.6
                __delay_cycles(100000);     // Delay for 100000*(1/MCLK)=0.1s
                P6OUT &= ~BIT6;             // Toggle P6.6
                __delay_cycles(3000000);    // Delay for 3s

                                            // Do something in the ARMED state
                                            // If something happens, you can move into the WARNING_STATE
                                            // state = WARNING_STATE
        }
        break;
    }


    case WARNING_STATE:
    {
        P6OUT &= ~BIT6;             // Toggle P6.6
        if (!(P2IN & BIT3))                    // If S2 (P2.3) is pressed
        {
            P1OUT ^= BIT0;                      // Toggle red LED every 0.5s
            __delay_cycles(500000);         // Delay for .5s
            totaltime ++;                           // Increment totaltime by 1
                                if (totaltime == 19)                    // After 10 seconds
                                {
                                    totaltime = 0;                  // Set count to zero
                                    state = ALERT_STATE;            // Go to ALERT state
                                }
        }
        else
                state = ARMED_STATE;                                // Go to ARMED state
      // Do something in the WARNING state
      // If something happens, you can move into the ALERT_STATE or the ARMED_STATE
        break;
    }


    case ALERT_STATE:
    {
        if(!(P4IN & BIT1))                      // If S1 (P4.1) is pressed
                        {
                            state = ARMED_STATE;                // Go to ARMED state
                        }
        else
                        P1OUT |= BIT0;                          // toggle red LED
                        break;
      // Do something in the ALERT state
      // If something happens, you can move into the WARNING_STATE or the ARMED_STATE
    }
                 }
}
}
