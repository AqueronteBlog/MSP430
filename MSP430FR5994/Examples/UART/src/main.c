/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the GPIO<_IN with interrupts. Every time any
 *              button is pressed ( S1 or S2 ) changes the state of the LED ( LED 1 or LED2 ).
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/November/2018
 * @version     7/November/2018    The ORIGIN
 * @pre         This firmware was tested on the MSP-EXP430FR5994 with CCS vs8.2.0.00007.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <msp430.h> 
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"


/**@brief Constants.
 */



/**@brief Variables.
 */



/**@brief Function Prototypes.
 */



/**@brief Function for application main entry.
 */
int main(void)
{
    conf_WDT    ();
    conf_CLK    ();
    conf_GPIO   ();
    conf_UART   ();


    /* All interrupts are enabled    */
    __enable_interrupt();


    while ( 1 )
    {
        LPM4;
    }
}
