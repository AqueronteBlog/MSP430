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
 * @brief       UART0_ISR interrupt service routine
 * @details     Subroutine for UART0.
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
 * @date        10/November/2018
 * @version     10/November/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = EUSCI_A0_VECTOR
__interrupt void UART0_ISR ( void )
{
    switch ( __even_in_range ( UCIV, UCIV_8 ) )
    {
        case UCIV_0:
        /* Interrupt Source:  No interrupt pending  */
            break;

        case UCIV_2:
        /* Interrupt Source: Receive buffer full; Interrupt Flag: UCRXIFG ( Interrupt Priority: Highest )  */

            UCA0IFG &=  ~UCRXIFG;       // Reset flag
            break;

        case UCIV_4:
        /* Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG  */

            UCA0IFG &=  ~UCTXIFG;       // Reset flag
            break;

        case UCIV_6:
        /* Interrupt Source: Start bit received; Interrupt Flag: UCSTTIFG  */
            break;

        case UCIV_8:
        /* Interrupt Source: Transmit complete; Interrupt Flag: UCTXCPTIFG ( Interrupt Priority: Lowest )  */
            break;

        default:
            break;
    }
}
