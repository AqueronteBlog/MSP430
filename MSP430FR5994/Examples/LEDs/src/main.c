#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer


    /* Disable the GPIO power-on default high-impedance mode to activate previously configured port settings     */
    PM5CTL0 &= ~LOCKLPM5;

    while ( 1 )
    {

    }
}
