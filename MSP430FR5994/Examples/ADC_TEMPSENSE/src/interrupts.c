/**
 * @brief       interrupts.h
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/November/2018
 * @version     17/November/2018    The ORIGIN
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
 * @date        28/November/2018
 * @version     28/November/2018      The ORIGIN
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
            /*[todo] Start ADC12_B conversion     */
            P1OUT   ^=   LED1;              // Change LED1 state
            TA0CTL  &=  ~( TAIFG );         // Reset flag
            break;

        default:
            break;
    }
}



/**
 * @brief       ADC12_B_ISR interrupt service routine
 * @details     Subroutine for ADC12_B.
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
 * @date        25/November/2018
 * @version     25/November/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_B_ISR ( void )
{
    switch ( __even_in_range ( ADC12IV, ADC12IV_76 ) )
    {
        case ADC12IV_0:
        /* Interrupt Source: No interrupt pending, Interrupt Flag: None  */
            break;

        case ADC12IV_2:
        /* Interrupt Source: ADC12MEMx overflow, Interrupt Flag: ADC12OVIFG, Interrupt Priority: Highest     */
            break;

        case ADC12IV_4:
        /* Interrupt Source: Conversion time overflow, Interrupt Flag: ADC12TOVIFG   */
            break;

        case ADC12IV_6:
        /* Interrupt Source: ADC12 window high interrupt flag, Interrupt Flag: ADC12HIIFG */
            break;

        case ADC12IV_8:
        /*  Interrupt Source: ADC12 window low interrupt flag, Interrupt Flag: ADC12LOIFG  */
            break;

        case ADC12IV_10:
        /*  Interrupt Source: ADC12 in-window interrupt flag, Interrupt Flag: ADC12INIFG  */
            break;

        case ADC12IV_12:
        /*  Interrupt Source: ADC12MEM0 interrupt flag, Interrupt Flag: ADC12IFG0  */
            break;

        case ADC12IV_14:
        /*  Interrupt Source: ADC12MEM1 interrupt flag, Interrupt Flag: ADC12IFG1  */
            break;

        case ADC12IV_16:
        /*  Interrupt Source: ADC12MEM2 interrupt flag, Interrupt Flag: ADC12IFG2  */
            break;

        case ADC12IV_18:
        /*  Interrupt Source: ADC12MEM3 interrupt flag, Interrupt Flag: ADC12IFG3  */
            break;

        case ADC12IV_20:
        /*  Interrupt Source: ADC12MEM4 interrupt flag, Interrupt Flag: ADC12IFG4  */
            break;

        case ADC12IV_22:
        /*  Interrupt Source: ADC12MEM5 interrupt flag, Interrupt Flag: ADC12IFG5  */
            break;

        case ADC12IV_24:
        /*  Interrupt Source: ADC12MEM6 interrupt flag, Interrupt Flag: ADC12IFG6  */
            break;

        case ADC12IV_26:
        /*  Interrupt Source: ADC12MEM7 interrupt flag, Interrupt Flag: ADC12IFG7  */
            break;

        case ADC12IV_28:
        /*  Interrupt Source: ADC12MEM8 interrupt flag, Interrupt Flag: ADC12IFG8  */
            break;

        case ADC12IV_30:
        /* Interrupt Source: ADC12MEM9 interrupt flag, Interrupt Flag: ADC12IFG9  */
            break;

        case ADC12IV_32:
        /*  Interrupt Source: ADC12MEM10 interrupt flag, Interrupt Flag: ADC12IFG10  */
            break;

        case ADC12IV_34:
        /*  Interrupt Source: ADC12MEM11 interrupt flag, Interrupt Flag: ADC12IFG11  */
            break;

        case ADC12IV_36:
        /* Interrupt Source: ADC12MEM12 interrupt flag, Interrupt Flag: ADC12IFG12  */
            break;

        case ADC12IV_38:
        /*  Interrupt Source: ADC12MEM13 interrupt flag, Interrupt Flag: ADC12IFG13  */
            break;

        case ADC12IV_40:
        /* Interrupt Source: ADC12MEM14 interrupt flag, Interrupt Flag: ADC12IFG14  */
            break;

        case ADC12IV_42:
        /* Interrupt Source: ADC12MEM15 interrupt flag, Interrupt Flag: ADC12IFG15  */
            break;

        case ADC12IV_44:
        /*  Interrupt Source: ADC12MEM16 interrupt flag, Interrupt Flag: ADC12IFG16  */
            break;

        case ADC12IV_46:
        /*  Interrupt Source: ADC12MEM17 interrupt flag, Interrupt Flag: ADC12IFG1  */
            break;

        case ADC12IV_48:
        /* Interrupt Source: ADC12MEM18 interrupt flag, Interrupt Flag: ADC12IFG18  */
            break;

        case ADC12IV_50:
        /*  Interrupt Source: ADC12MEM19 interrupt flag, Interrupt Flag: ADC12IFG19  */
            break;

        case ADC12IV_52:
        /*  Interrupt Source: ADC12MEM20 interrupt flag, Interrupt Flag: ADC12IFG20  */
            break;

        case ADC12IV_54:
        /* Interrupt Source: ADC12MEM21 interrupt flag, Interrupt Flag: ADC12IFG21  */
            break;

        case ADC12IV_56:
        /*  Interrupt Source: ADC12MEM22 interrupt flag, Interrupt Flag: ADC12IFG22  */
            break;

        case ADC12IV_58:
        /*  Interrupt Source: ADC12MEM23 interrupt flag, Interrupt Flag: ADC12IFG23  */
            break;

        case ADC12IV_60:
        /*  Interrupt Source: ADC12MEM24 interrupt flag, Interrupt Flag: ADC12IFG24  */
            break;

        case ADC12IV_62:
        /*  Interrupt Source: ADC12MEM25 interrupt flag, Interrupt Flag: ADC12IFG25  */
            break;

        case ADC12IV_64:
        /*  Interrupt Source: ADC12MEM26 interrupt flag, Interrupt Flag: ADC12IFG26  */
            break;

        case ADC12IV_66:
        /*  Interrupt Source: ADC12MEM27 interrupt flag, Interrupt Flag: ADC12IFG27  */
            break;

        case ADC12IV_68:
        /* Interrupt Source: ADC12MEM28 interrupt flag, Interrupt Flag: ADC12IFG28  */
            break;

        case ADC12IV_70:
        /*  Interrupt Source: ADC12MEM29 interrupt flag, Interrupt Flag: ADC12IFG29  */
            break;

        case ADC12IV_72:
        /*  Interrupt Source: ADC12MEM30 interrupt flag, Interrupt Flag: ADC12IFG30  */

            ADC12IFGR1  &=  ~( ADC12IFG30 );        // Clear the flag
            break;

        case ADC12IV_74:
        /*  Interrupt Source: ADC12MEM31 interrupt flag, Interrupt Flag: ADC12IFG31  */
            break;

        case ADC12IV_76:
        /*  Interrupt Source: ADC12RDYIFG interrupt flag, Interrupt Flag: ADC12RDYIFG  */
            break;

        default:
            break;
    }
}
