/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     28/September/2018   The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"


/**
 * @brief       void conf_WDT  ( void )
 * @details     It disables the watchdog and GPIO power-on default high-impedance mode.
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
 * @date        28/September/2018
 * @version     28/September/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_WDT  ( void )
{
    /* The watchdog is disabled  */
    WDTCTL   =   ( WDTPW | WDTHOLD );   // stop watchdog timer

    /* Disable the GPIO power-on default high-impedance mode to activate previously configured port settings     */
    PM5CTL0 &=  ~LOCKLPM5;
}



/**
 * @brief       void conf_CLK  ( void )
 * @details     It configures the clock sources.
 *
 *                  ACLK:   VLOCLK ~ 9.4KHz
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
 * @date        2/October/2018
 * @version     2/October/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
    /* Unlock register  */
    CSCTL0_H   =   CSKEY_H;

    /* Enables VLO clock     */
    CSCTL4  &=  ~VLOOFF;
    CSCTL4  |=   VLOOFF_0;

    /* ACLK = VLOCLK    */
    CSCTL2  &=   ~SELA;
    CSCTL2  |=    SELA__VLOCLK;

    /* ACLK = ACLK/1    */
    CSCTL3  &=  ~DIVA;
    CSCTL3  |=   DIVA_0;

    /* Lock register     */
    CSCTL0_H   =   0x01;
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO.
 *
 *                  - PORT1:
 *                      -- P1.0:    LED1
 *                      -- P1.1:    LED2
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        28/September/2018
 * @version     2/October/2018      LED1 OFF, LED2 ON at the beginning
 *              28/September/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    /* Configure the LEDs ( output low ) on PORT1   */
    P1SEL0  &=  ~( LED1 | LED2 );
    P1SEL1  &=  ~( LED1 | LED2 );

    P1OUT   &=  ~( LED1 );
    P1OUT   |=   LED2;
    P1DIR   |=   ( LED1 | LED2 );
}



/**
 * @brief       void conf_TimerA  ( void )
 * @details     It configures the TimerA.
 *
 *                  Timer A0:
 *                      - Timer A0: Up mode
 *                      - ACLK clock ( f_TA0/1 = ACLK = VLOCLK ~ 9.4KHz )
 *                      - Interrupt enabled
 *                      - Timer A0 overflow ~ 0.15s ( Overflow: 1410/9.4kHz = 0.15s )
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
 * @version     4/October/2018         Overflow was changed to 0.15s instead of 0.25s
 *              30/September/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_TimerA  ( void )
{
    /* Timer TA0:
     *  - Reset TimerA clock
     *  - Reset input divider
     *  - Stop TimerA0
     *  - TimerA interrupt disabled
     *  - Reset TimerA flag
     */
    TA0CTL  &=  ~( TASSEL | ID | MC | TAIE | TAIFG );

    /* No capture mode   */
    TA0CCTL0    &=  ~( CM );

    /* Timer TA0:
     *  - TimerA0 clock: ACLK
     *  - Internal divider: /1
     *  - TimerA0 interrupt enabled
     */
    TA0CTL  |=   ( TASSEL__ACLK | ID_0 | TAIE );
    TA0EX0  &=  ~( TAIDEX );

    /*  Capture/Compare register to generate a delay of about 0.15s   */
    TA0CCR0  =   1410;

    /* Timer TA0:
     *  - TimerA0 mode: Up mode
     *  - TimerA0 clear
     */
    TA0CTL  |=   ( MC__UP | TACLR );
}



/**
 * @brief       void conf_TimerB  ( void )
 * @details     It configures the TimerB.
 *
 *                  Timer B0:
 *                      - Timer B0: Up mode
 *                      - ACLK clock ( f_TB0/1 = ACLK = VLOCLK ~ 9.4KHz )
 *                      - Interrupt enabled
 *                      - Timer B0 overflow ~ 0.15s ( Overflow: 1410/9.4kHz = 0.15s )
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
 * @date        1/October/2018
 * @version     4/October/2018      Overflow was changed to 0.15s instead of 0.25s
 *              1/October/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_TimerB  ( void )
{
    /* Timer TB0:
     *  - Reset TimerB0 clock
     *  - Reset input divider
     *  - Stop TimerB0
     *  - TimerB0 interrupt disabled
     *  - Reset TimerB0 flag
     */
    TB0CTL  &=  ~( TBSSEL | ID | MC | TBIE | TBIFG );

    /* No capture mode   */
    TB0CCTL0    &=  ~( CM );

    /* Timer TB0:
     *  - TimerB0 clock: ACLK
     *  - Internal divider: /1
     *  - TimerB0 interrupt enabled
     */
    TB0CTL  |=   ( TBSSEL__ACLK | ID_0 | TBIE );
    TB0EX0  &=  ~( TBIDEX );

    /*  Capture/Compare register to generate a delay of about 0.15s   */
    TB0CCR0  =   1410;

    /* Timer TB0:
     *  - TimerB0 mode: Up mode
     *  - TimerB0 clear
     */
    TB0CTL  |=   ( MC__UP | TBCLR );
}
