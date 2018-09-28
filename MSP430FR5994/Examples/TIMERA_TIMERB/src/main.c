/**
 * @brief       main.c
 * @details     [todo]This example shows how to blink the both LEDs on the board.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/September/2018
 * @version     14/September/2018    The ORIGIN
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
void myDelay    ( uint16_t myCounter );



/**@brief Function for application main entry.
 */
int main(void)
{
    conf_WDT  ();
    conf_GPIO ();



    while ( 1 )
    {
        P1OUT   |=   LED1;      // LED 1 on
        P1OUT   &=  ~LED2;      // LED 2 off
        myDelay ( 0x2323 );

        P1OUT   &=  ~LED1;      // LED 1 off
        P1OUT   |=   LED2;      // LED 2 on
        myDelay ( 0x2323 );
    }
}



/**
 * @brief       void myDelay ( uint16_t )
 * @details     A simple delay.
 *
 *
 * @param[in]    myCounter: A simple counter.
 *
 * @param[out]   N/A.
 *
 *
 *@return      N/A
 *
 * @author      Manuel Caballero
 * @date        23/September/2018
 * @version     23/September/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void myDelay ( uint16_t myCounter )
{
    uint16_t i = 0;

    for ( i = 0; i < myCounter; i++ );
}
