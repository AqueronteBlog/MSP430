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
 * @brief       TIMER0_A1_ISR interrupt service routine
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
 * @date        7/October/2018
 * @version     7/October/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR ( void )
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
            P1OUT   ^=   LED1;              // Change LED1 state
            TA0CTL  &=  ~( TAIFG );         // Reset flag
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
 * @date        7/October/2018
 * @version     7/October/2018      The ORIGIN
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
            P1OUT   ^=   LED2;              // Change LED2 state
            TB0CTL  &=  ~( TBIFG );         // Reset flag
            break;

        default:
            break;
    }
}
