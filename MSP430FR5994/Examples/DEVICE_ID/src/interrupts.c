/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/April/2019
 * @version     14/April/2019    The ORIGIN
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
 * @date        14/April/2019
 * @version     14/April/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = EUSCI_A0_VECTOR
__interrupt void UART0_ISR ( void )
{
    switch ( __even_in_range ( UCA0IV, 18 ) )
    {
        case UCIV_0:
        /* Interrupt Source:  No interrupt pending  */
            break;

        case UCIV_2:
        /* Interrupt Source: Receive buffer full; Interrupt Flag: UCRXIFG ( Interrupt Priority: Highest )  */
            break;

        case UCIV_4:
        /* Interrupt Source: Transmit buffer empty; Interrupt Flag: UCTXIFG  */
            /* Stop transmitting data when that character is found */
            if ( *myPtr  == '\n' )
            {
                /* All data was transmitted already, restore UART Rx interrupt again     */
                UCA0IE  &=  ~( UCTXIE );
                UCA0IE  |=   ( UCRXIE );

                P1OUT   &=  ~LED2;              // LED2 on
            }
            else
            {
                /* Keep transmitting data through the UART   */
                UCA0TXBUF    =   *++myPtr;
            }

            myState  =   STATE_LOW_POWER;
            UCA0IFG &=  ~UCTXIFG;           // Reset flag
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
