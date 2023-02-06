/*
 * OccupancyDetector.c
 *
 *  Created on: Jan 30, 2023
 *      Author: Hunter Geitz
 */
#include <msp430.h>

int main()
{
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here

        // Stop watchdog timer
        WDTCTL = WDTPW | WDTHOLD;
        // Set green LED pin (P1.0) as an output
        P6DIR |= BIT6;
        // Set red LED pin (P1.0) as an output
        P1DIR |= BIT0;
        // Configure P2.3 to an Input
        P2DIR &= ~BIT3;

char state = ARMED_STATE; // Initializing first state as ARMED state

while(1)
{
  switch (state) {


    case ARMED_STATE:
    {
        if (P2IN & BIT3)                    // If S2 (P2.3) is pressed)
            state = WARNING_STATE           // Go to WARNING state
        else
                P6OUT ^= BIT6;              // Toggle P6.6
                __delay_cycles(100000);     // Delay for 100000*(1/MCLK)=0.1s

                                            // Do something in the ARMED state
                                            // If something happens, you can move into the WARNING_STATE
                                            // state = WARNING_STATE
    }


    case WARNING_STATE:
    {
        if (P2IN & BIT3)                    // If S2 (P2.3) is pressed)
            state = ALERT_STATE           // Go to WARNING state
        else if ()
        else
                P1OUT ^= BIT0;              // Toggle P1.0
                __delay_cycles(1000000);     // Delay for 1000000*(1/MCLK)=1s
      // Do something in the WARNING state
      // If something happens, you can move into the ALERT_STATE or the ARMED_STATE

    }


    case ALERT_STATE:
    {
      // Do something in the ALERT state
      // If something happens, you can move into the WARNING_STATE or the ARMED_STATE
    }
                 }
}
}
