/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/October/2018
 * @version     7/October/2018   The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"


/**
 * @brief       void conf_WDT  ( void )
 * @details     Watchdog as an interval timer and GPIO power-on default high-impedance mode.
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
 * @version     9/October/2018      It configures all in just one line and some comments
 *                                  were updated.
 *              7/October/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_WDT  ( void )
{
    /* Watchdog timer interrupt enable   */
    SFRIE1  |=   WDTIE__ENABLE;

    /* Configure the Watchdog
     *  WDT clock: VLOCK
     *  WDT as an interval timer
     *  WDT timer counter clear
     *  WDT timer interval select: f_WDT/2^9 ~ 9.4KhZ/2^9 = 9.4KhZ/512 ( ~54.47ms at 9.4KHz )
     *  Start WDT timer
     */
    WDTCTL   =   ( WDTPW | WDTHOLD__UNHOLD | WDTSSEL__VLOCLK | WDTTMSEL_1 | WDTCNTCL_1 | WDTIS__512 );


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
 * @date        7/October/2018
 * @version     7/October/2018      The ORIGIN
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
    CSCTL2  &=  ~SELA;
    CSCTL2  |=   SELA__VLOCLK;

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
 * @date        7/October/2018
 * @version     7/October/2018   The ORIGIN
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
