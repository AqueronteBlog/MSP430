/**
 * @brief       main.c
 * @details     [todo]This example shows how to blink the both LEDs on the board by interrupts.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/October/2018
 * @version     7/October/2018    The ORIGIN
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
    conf_TimerA ();
    conf_TimerB ();

    /* All interrupts are enabled    */
    __enable_interrupt();


    while ( 1 )
    {
        LPM3;
    }
}
