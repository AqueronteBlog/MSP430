/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/October/2018
 * @version     7/October/2018    The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       WDT_A_ISR interrupt service routine
 * @details     Subroutine for WDT_A.
 *
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/October/2018
 * @version     9/October/2018      Change LEDs state
 *              7/October/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = WDT_VECTOR
__interrupt void WDT_A_ISR ( void )
{
    P1OUT   ^=   ( LED1 | LED2 );              // Change LED1 and LED2 state
}
