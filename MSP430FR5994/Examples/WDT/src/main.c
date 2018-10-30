/**
 * @brief       main.c
 * @details     This example shows how to work with the WDT_A as a watchdog. The WDT is not refreshed
 *              so a PUC is generated.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/October/2018
 * @version     14/October/2018    The ORIGIN
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
    uint16_t i = 0U;


    /* The watchdog is disabled  */
    WDTCTL   =   ( WDTPW | WDTHOLD );   // stop watchdog timer

    conf_CLK    ();
    conf_GPIO   ();

    /* Little delay to check changes on the LEDs     */
    for ( i = 0U; i < 0x2323; i++ );

    conf_WDT    ();

    P1OUT   ^=   ( LED1 | LED2 );              // Change LED1 and LED2 state

    while ( 1 )
    {
        LPM3;
    }
}
