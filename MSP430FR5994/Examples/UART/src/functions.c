/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/November/2018
 * @version     7/November/2018   The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"


/**
 * @brief       void conf_WDT  ( void )
 * @details     Watchdog is disabled and GPIO power-on default high-impedance mode.
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
 * @date        7/November/2018
 * @version     7/November/2018      The ORIGIN
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
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO.
 *
 *                  - PORT1:
 *                      -- P1.0:    LED1
 *                      -- P1.1:    LED2
 *
 *                  - PORT2:
 *                      -- P2.0:    UCA0 UART TX
 *                      -- P2.1:    UCA0 UART RX
 *
 *                  - PORT5: Interrupt enabled
 *                      -- P5.5:    S2  ( BUTTON1 )
 *                      -- P5.6:    S1  ( BUTTON2 )
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        7/November/2018
 * @version     8/November/2018   UART0 pin-out was defined
 *              7/November/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    /* Configure the Buttons on PORT5  */
    P5SEL0  &=  ~( S1 | S2 );
    P5SEL1  &=  ~( S1 | S2 );

    /* Input with pull-up resistors  */
    P5REN   |=   ( S1 | S2 );
    P5OUT   |=   ( S1 | S2 );

    P5DIR   &=  ~( S1 | S2 );

    /* Enable interrupts on P5.5 and P5.6 pins     */
    P5IES   |=   ( S1 | S2 );   // P5IFG  flag is set with a high-to-low transition
    P5IFG   &=  ~( S1 | S2 );   // Reset flags
    P5IE    |=   ( S1 | S2 );   // Enable interrupts on both pins

    /* Configure the LEDs ( output low ) on PORT1   */
    P1SEL0  &=  ~( LED1 | LED2 );
    P1SEL1  &=  ~( LED1 | LED2 );

    P1OUT   &=  ~( LED1 | LED2 );
    P1DIR   |=   ( LED1 | LED2 );

    /* Configure the UART0 on PORT2   */
    P2SEL0  &=  ~( UART0_TX | UART0_RX );
    P2SEL1  |=   ( UART0_TX | UART0_RX );
}



/**
 * @brief       void conf_UART  ( void )
 * @details     It configures the UART. [todo]
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
 * @date        7/November/2018
 * @version     7/November/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_UART  ( void )
{
    /* UART0 Software reset enable */
    UCA0CTLW0   |=   UCSWRST__ENABLE;

    /* UART0:
     *  - Parity disabled
     *  - MSB first select
     *  - 8-bit data
     *  - One stop bit
     *  - UART mode
     *  - Asynchronous mode
     *  - UCLK clock
     *  - Erroneous characters rejected and UCRXIFG is not set
     *  - Received break characters do not set UCRXIFG
     *  - Not dormant. All received characters set UCRXIFG
     *  - Next frame transmitted is data
     *  - Next frame transmitted is not a break
     */
    UCA0CTLW0   &=  ~( UCPEN | UC7BIT | UCSPB | UCMODE | UCSYNC | UCSSEL | UCRXEIE | UCBRKIE | UCDORM | UCTXADDR | UCTXBRK );
    UCA0CTLW0   |=   ( UCSWRST__ENABLE | UCMSB );

    /*  Baud-rate detection disabled    */
    UCA0ABCTL   &=  ~( UCABDEN );

    /*  IrDA encoder/decoder disabled    */
    UCA0IRCTL   &=  ~( UCIREN );


    /* UART0 Reset released for operation */
    UCA0CTLW0   &=  ~UCSWRST__ENABLE;

    /* Clean and Enable interrupts: Tx and Rx  */
    UCA0IFG &=  ~( UCTXIFG | UCRXIFG );
    UCA0IE  |=   ( UCTXIE | UCRXIE );
}
