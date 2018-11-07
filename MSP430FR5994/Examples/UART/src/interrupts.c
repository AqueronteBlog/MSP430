/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/November/2018
 * @version     7/November/2018    The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       PORT5_ISR interrupt service routine
 * @details     Subroutine for PORT5.
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
 * @date        2/November/2018
 * @version     2/November/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = PORT5_VECTOR
__interrupt void PORT5_ISR ( void )
{
    switch ( __even_in_range ( P5IV, P5IV__P5IFG7 ) )
    {
        case P5IV__P5IFG0:
        /* Interrupt Source: Port 5.0 interrupt; Interrupt Flag: P5IFG0 ( Interrupt Priority: Highest )  */
            break;

        case P5IV__P5IFG1:
        /* Interrupt Source: Port 5.1 interrupt; Interrupt Flag: P5IFG1  */
            break;

        case P5IV__P5IFG2:
        /* Interrupt Source: Port 5.2 interrupt; Interrupt Flag: P5IFG2  */
            break;

        case P5IV__P5IFG3:
        /* Interrupt Source: Port 5.3 interrupt; Interrupt Flag: P5IFG3  */
            break;

        case P5IV__P5IFG4:
        /* Interrupt Source: Port 5.4 interrupt; Interrupt Flag: P5IFG4  */
            break;

        case P5IV__P5IFG5:
        /* Interrupt Source: Port 5.5 interrupt; Interrupt Flag: P5IFG5  */
            P1OUT   ^=   LED2;              // Change LED2 state
            P5IFG   &=  ~( S2 );            // Reset flags
            break;

        case P5IV__P5IFG6:
        /* Interrupt Source: Port 5.6 interrupt; Interrupt Flag: P5IFG6  */
            P1OUT   ^=   LED1;              // Change LED1 state
            P5IFG   &=  ~( S1 );            // Reset flags
            break;

        case P5IV__P5IFG7:
        /* Interrupt Source: Port 5.7 interrupt; Interrupt Flag: P5IFG7 ( Interrupt Priority: Lowest )  */
            break;

        default:
            break;
    }
}
