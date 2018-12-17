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
 * @date        17/November/2018
 * @version     27/November/2018      ACLK:   VLOCLK ~ 9.4KHz
 *              17/November/2018      The ORIGIN
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



/**
 * @brief       void conf_ADC  ( void )
 * @details     It configures the ADC.
 *
 *                  [todo]· BRCLK source clock: SMCLK = 8MHz.
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
 * @date        19/November/2018
 * @version     19/November/2018   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_ADC  ( void )
{
    /* ADC12_B Off and disabled   */
    ADC12CTL0   &=  ~( ADC12ON | ADC12ENC );

    /* ADC12_B:
     *  ADC12_B predivider by 1
     *  SAMPCON signal is sourced from the sample-input signal
     *  The sample-input signal is not inverted
     *  ADC12_B clock divider into 1
     *  ADC12_B clock source:  ADC12OSC ( MODOSC )
     *  Single-channel, single-conversion
     *  Binary unsigned
     *  ADC12_B resolution: 12 bit ( 14 clock cycle conversion time )
     *  Regular power mode where sample rate is not restricted
     *
     */
    ADC12CTL1   &=  ~( ADC12PDIV | ADC12SHP | ADC12ISSH | ADC12DIV | ADC12SSEL | ADC12CONSEQ );
    ADC12CTL2   &=  ~( ADC12RES | ADC12DF | ADC12PWRMD );
    ADC12CTL2   |=   ADC12RES__12BIT;

    /* ADC_B address 30
     *  Comparator window disabled
     *  Single-ended mode enabled
     *  VR+ = VREF buffered, VR- = AVSS
     *  A30 Input channel selected
     *    */
    ADC12MCTL30 &=  ~( ADC12WINC | ADC12DIF | ADC12VRSEL | ADC12INCH );
    ADC12MCTL30 |=   ( ADC12VRSEL_1 | ADC12INCH_30 );

    /* Internal temperature sensor selected and ADC12_B conversion start address on A30 ( Internal temperature sensor )   */
    ADC12CTL3   |=   ( ADC12TCMAP | ADC12CSTARTADD_30 );

    /* A30 ( internal temperature sensor ) interrupt enabled and clear flag */
    ADC12IFGR1  &=  ~( ADC12IFG30 );
    ADC12IER1   |=   ( ADC12IE30 );

    /* ADC12_B enabled   */
    ADC12CTL0   |=   ( ADC12ON | ADC12ENC );
}



/**
 * @brief       void conf_TimerA  ( void )
 * @details     It configures the TimerA.
 *
 *                  Timer A0:
 *                      - Timer A0: Up mode
 *                      - ACLK clock ( f_TA0/1 = ACLK = VLOCLK ~ 9.4KHz )
 *                      - Interrupt enabled
 *                      - Timer A0 overflow ~ 2s ( Overflow: 18800/9.4kHz = 2s )
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

    /*  Capture/Compare register to generate a delay of about 2s   */
    TA0CCR0  =   18800;

    /* Timer TA0:
     *  - TimerA0 mode: Up mode
     *  - TimerA0 clear
     */
    TA0CTL  |=   ( MC__UP | TACLR );
}
