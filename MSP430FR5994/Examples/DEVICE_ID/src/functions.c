/**
 * @brief       functions.c
 * @details     Functions.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/April/2019
 * @version     13/April/2019   The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#include "functions.h"


/**
 * @brief       void conf_CLK  ( void )
 * @details     It configures the clock of the whole system.
 *
 *                  - MCLK = SMCLK = DCO = 1MHz
 *                  - ACLK:   VLOCLK ~ 9.4KHz
 *                  - HFXT and LFXT Clock disabled
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
void conf_CLK  ( void )
{
    /* Unblock the clock registers   */
    CSCTL0   =   CSKEY;

    /* DCO ~ 1MHz    */
    CSCTL1 &=  ~( DCORSEL | DCOFSEL );
    CSCTL1 |=   DCOFSEL_0;

    /* MCLK = SMCLK = DCO, ACLK = VLOCLK    */
    CSCTL2  &=  ~( SELS | SELM | SELA );
    CSCTL2  |=   ( SELS_3 | SELM_3 | SELA__VLOCLK );

    /* SMCLK/1, MCLK/1, ACLK = ACLK/1   */
    CSCTL3  &=  ~( DIVS | DIVM | DIVA );
    CSCTL3  |=   DIVA_0;

    /* SMCLK and VLO Clock enabled and HFXT, VLO and LFXT Clock disabled     */
    CSCTL4  &=  ~( SMCLKOFF | VLOOFF );
    CSCTL4  |=   ( HFXTOFF | LFXTOFF | VLOOFF_0 );

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
 * @date        14/April/2019
 * @version     14/April/2019      The ORIGIN
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
 * @date        14/April/2019
 * @version     14/April/2019   The ORIGIN
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
 *                  · BRCLK source clock: SMCLK = 1MHz.
 *                  · BuadRate = 115200:
 *
 *                      N = f_BRCLK/BaudRate = 1MHz/115200 ~ 8.68 = {INT} = 8
 *
 *                      N < 16 -->  Oversampling OFF (UCOS16 = 0)
 *
 *              Therefore:
 *
 *                  UCBRSx = N - INT(N) = 1MHz/115200 - INT(1MHz/115200) ~ 0.68056
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
 * @version     14/April/2019   The ORIGIN
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
    UCA0MCTLW   &=  ~( UCOS16 );
    UCA0MCTLW    =  (uint16_t)( 0xD6 << 8U );        // UCBRS = 0xD6 and oversampling disabled
    UCA0BRW      =   8U;

    /* UART0 Reset released for operation */
    UCA0CTLW0   &=  ~UCSWRST__ENABLE;

    /* Clean and Enable interrupts: Rx only  */
    UCA0IFG &=  ~( UCTXIFG | UCRXIFG );
    UCA0IE  |=   ( UCRXIE );
}



/**
 * @brief       void conf_TimerB  ( void )
 * @details     It configures the TimerB.
 *
 *                  Timer B0:
 *                      - Timer B0: Up mode
 *                      - ACLK clock ( f_TB0/1 = ACLK = VLOCLK ~ 9.4KHz )
 *                      - Interrupt enabled
 *                      - Timer B0 overflow ~ 1s ( Overflow: 9400/9.4kHz = 1s )
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
void conf_TimerB  ( void )
{
    /* Timer TB0:
     *  - Reset TimerB0 clock
     *  - Reset input divider
     *  - Stop TimerB0
     *  - Reset TimerB0 flag
     */
    TB0CTL  &=  ~( TBSSEL | ID | MC | TBIE | TBIFG );

    /* No capture mode
     * Set/Reset output mode   */
    TB0CCTL0    &=  ~( CM | OUTMOD );
    TB0CCTL0    |=   ( OUTMOD_3 );

    /* Timer TB0:
     *  - TimerB0 clock: ACLK
     *  - Internal divider: /1
     */
    TB0CTL  |=   ( TBSSEL__ACLK | ID_0 );
    TB0EX0  &=  ~( TBIDEX );

    /*  Capture/Compare register to generate a delay of about 1s   */
    TB0CCR0  =   9400;

    /* Timer TB0:
     *  - TimerB0 mode: Up mode
     *  - TimerB0 interrupt enabled
     */
    TB0CTL  |=   ( MC__UP | TBIE );
}
