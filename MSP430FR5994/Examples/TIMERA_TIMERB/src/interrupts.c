/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     28/September/2018    The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "interrupts.h"


/**
 * @brief       TA0_ISR TimerA0 ( TA0 ) interrupt service routine
 * @details     Subroutine for TimerA0.
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
 * @date        30/September/2018
 * @version     30/September/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR ( void )
{
    switch ( __even_in_range ( TA0IV, TAIV__TAIFG ) )
    {
        case    0x00:
        /*  Vector 0:     No interrupt pending   */
            break;

        case    0x02:
        /*  Vector 2:     Interrupt Source: Capture/compare 1; Interrupt Flag: TAxCCR1 CCIFG; Interrupt Priority: Highest    */
            break;

        case    0x04:
        /*  Vector 4:     Interrupt Source: Capture/compare 2; Interrupt Flag: TAxCCR2 CCIFG     */
            break;

        case    0x06:
        /*  Vector 6:     Interrupt Source: Capture/compare 3; Interrupt Flag: TAxCCR3 CCIFG     */
            break;

        case    0x08:
        /*  Vector 8:     Interrupt Source: Capture/compare 4; Interrupt Flag: TAxCCR4 CCIFG     */
            break;

        case    0x0A:
        /*  Vector A:     Interrupt Source: Capture/compare 5; Interrupt Flag: TAxCCR5 CCIFG     */
            break;

        case    0x0C:
        /*  Vector C:     Interrupt Source: Capture/compare 6; Interrupt Flag: TAxCCR6 CCIFG     */
            break;

        case    0x0E:
        /*  Vector E:     Interrupt Source: Timer overflow; Interrupt Flag: TAxCTL TAIFG; Interrupt Priority: Lowest     */
            TA0CTL      &=  ~( TAIFG );
            break;

        default:
            break;
    }
}
