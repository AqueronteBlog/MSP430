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

            myState  =   STATE_LOW_POWER;   // Update the new state
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



/**
 * @brief       TIMER0_B1_ISR interrupt service routine
 * @details     Subroutine for TimerB1.
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
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR ( void )
{
    switch ( __even_in_range ( TB0IV, TBIV__TBIFG ) )
    {
        case    0x00:
        /*  Vector 0:     No interrupt pending   */
            break;

        case    0x02:
        /*  Vector 2:     Interrupt Source: Capture/compare 1; Interrupt Flag: TBxCCR1 CCIFG; Interrupt Priority: Highest    */
            break;

        case    0x04:
        /*  Vector 4:     Interrupt Source: Capture/compare 2; Interrupt Flag: TBxCCR2 CCIFG     */
            break;

        case    0x06:
        /*  Vector 6:     Interrupt Source: Capture/compare 3; Interrupt Flag: TBxCCR3 CCIFG     */
            break;

        case    0x08:
        /*  Vector 8:     Interrupt Source: Capture/compare 4; Interrupt Flag: TBxCCR4 CCIFG     */
            break;

        case    0x0A:
        /*  Vector A:     Interrupt Source: Capture/compare 5; Interrupt Flag: TBxCCR5 CCIFG     */
            break;

        case    0x0C:
        /*  Vector C:     Interrupt Source: Capture/compare 6; Interrupt Flag: TBxCCR6 CCIFG     */
            break;

        case    0x0E:
        /*  Vector E:     Interrupt Source: Timer overflow; Interrupt Flag: TBxCTL TBIFG; Interrupt Priority: Lowest     */
            P1OUT   |=   LED2;                      // LED2 on
            __bic_SR_register_on_exit( LPM3_bits ); // Exit active CPU
            TB0CTL  &=  ~( TBIFG );                 // Reset flag
            myState  =   SEND_DATA_OVER_UART;       // Update the new state
            break;

        default:
            break;
    }
}
