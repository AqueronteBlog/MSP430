/**
 * @brief       main.c
 * @details     [todo]This example shows how to blink the both LEDs on the board.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     28/September/2018    The ORIGIN
 * @pre         This firmware was tested on the nrf51-DK with EmBitz 1.11 rev 0 ( SDK 1.1.0 ).
 * @warning     Softdevice S310 was used although the file's name is S130. The softdevice is not used in this example anyway because of Bluetooth was not used.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <msp430.h> 
#include "board.h"
#include "variables.h"
#include "functions.h"

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
    conf_GPIO   ();
    conf_TimerA ();
    conf_TimerB ();


    while ( 1 )
    {

    }
}
