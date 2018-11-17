/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/November/2018
 * @version     17/November/2018   The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"


/**
 * @brief       void conf_CLK  ( void )
 * @details     It configures the clock of the whole system.
 *
 *                  - MCLK = SMCLK = DCO = 8MHz
 *                  - HFXT, VLO and LFXT Clock disabled
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
 * @date        17/November/2018
 * @version     17/November/2018      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
    /* Unblock the clock registers   */
    CSCTL0   =   CSKEY;

    /* DCO ~ 8MHz    */
    CSCTL1 &=  ~( DCORSEL | DCOFSEL );
    CSCTL1 |=   DCOFSEL_6;

    /* MCLK = SMCLK = DCO    */
    CSCTL2  &=  ~( SELS | SELM );
    CSCTL2  |=   ( SELS_3 | SELM_3 );

    /* SMCLK/1, MCLK/1   */
    CSCTL3  &=  ~( DIVS | DIVM );

    /* SMCLK Clock enabled and HFXT, VLO and LFXT Clock disabled     */
    CSCTL4  &=  ~( SMCLKOFF );
    CSCTL4  |=   ( HFXTOFF | VLOOFF | LFXTOFF );

    /* Block the clock registers     */
    CSCTL0_H =   0x01;
}



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
 * @date        17/November/2018
 * @version     17/November/2018      The ORIGIN
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
 * @date        17/November/2018
 * @version     17/November/2018   The ORIGIN
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
 * @details     It configures the UART.
 *
 *                  · BRCLK source clock: SMCLK = 8MHz.
 *                  · BuadRate = 115200:
 *
 *                      N = f_BRCLK/BaudRate = 8MHz/115200 ~ 69.444 = {INT} = 69
 *
 *                      N >= 16 -->  Oversampling ON (UCOS16 = 1)
 *
 *              Therefore:
 *
 *                  UCBRx = INT(N/16) = INT(69/16) = 4
 *                  UCBRFx = ROUND[((N/16) - INT(N/16))·16] = ROUND[((8MHz/115200)/16 - INT((8MHz/115200)/16))·16] ~ 5.44 = 5
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
 * @date        17/November/2018
 * @version     17/November/2018   The ORIGIN
 * @pre         For more info about Baud rates calculation, check out: Table 30-5. Recommended Settings for Typical Crystals and Baud Rates
 *              in the User Guide ( SLAU367O )
 * @warning     N/A
 */
void conf_UART  ( void )
{
    /* UART0 Software reset enable */
    UCA0CTLW0   |=   UCSWRST__ENABLE;

    /* UART0:
     *  - Parity disabled
     *  - LSB first select
     *  - 8-bit data
     *  - One stop bit
     *  - UART mode
     *  - Asynchronous mode
     *  - SMCLK clock
     *  - Erroneous characters rejected and UCRXIFG is not set
     *  - Received break characters do not set UCRXIFG
     *  - Not dormant. All received characters set UCRXIFG
     *  - Next frame transmitted is data
     *  - Next frame transmitted is not a break
     */
    UCA0CTLW0   &=  ~( UCPEN | UC7BIT | UCSPB | UCMODE | UCSYNC | UCSSEL | UCRXEIE | UCBRKIE | UCDORM | UCTXADDR | UCTXBRK );
    UCA0CTLW0   |=   ( UCSWRST__ENABLE | UCSSEL__SMCLK );

    /* Baud-rate detection disabled    */
    UCA0ABCTL   &=  ~( UCABDEN );

    /* IrDA encoder/decoder disabled    */
    UCA0IRCTL   &=  ~( UCIREN );

    /* Clock prescaler setting of the Baud rate generator    */
    UCA0MCTLW    =   ( ( 0x55 << 8U ) | ( 5U << 4U ) | UCOS16 );        // UCBRS = 0x55, UCBRF = 5 and oversampling enabled
    UCA0BRW      =   4U;

    /* UART0 Reset released for operation */
    UCA0CTLW0   &=  ~UCSWRST__ENABLE;

    /* Clean and Enable interrupts: Rx only  */
    UCA0IFG &=  ~( UCTXIFG | UCRXIFG );
    UCA0IE  |=   ( UCRXIE );
}
