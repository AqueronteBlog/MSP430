/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the UART with interrupts.
 *              If the launchpad receives:
 *                  - '0': LED1 changes its state and it transmits "LED1" through the UART
 *                  - '1': LED2 changes its state and it transmits "LED2" through the UART
 *                  - Any other character received, it transmits ""Wrong command!" through the UART.
 *
 *              The UART is configured at 115200 baudrate.
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/November/2018
 * @version     17/November/2018    The ORIGIN
 * @pre         This firmware was tested on the MSP-EXP430FR5994 with CCS vs8.2.0.00007.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <msp430.h> 
#include <stdio.h>
#include "board.h"
#include "variables.h"
#include "functions.h"
#include "interrupts.h"


/**@brief Constants.
 */
#define TX_BUFF_SIZE  32                                /*!< UART buffer size                                   */
#define CALADC12_12V_30C  *( (unsigned int *)0x1A1A )   /*!< Temperature Sensor Calibration-30 C                */
#define CALADC12_12V_85C  *( (unsigned int *)0x1A1C )   /*!< Temperature Sensor Calibration-85 C                */

/**@brief Variables.
 */
volatile myCommands_t    myRX_cmd  =   CMD_WRONG;       /*!< Command received from the UART                     */
volatile uint8_t        *myPtr;                         /*!< Pointer to point out myMessage                     */
volatile system_states_t myState   =   STATE_LOW_POWER; /*!< State of the system                                */
volatile uint16_t        myRawTemp =   0U;              /*!< Variable to store the raw temperature              */


/**@brief Function Prototypes.
 */



/**@brief Function for application main entry.
 */
int main(void)
{
    float    myTemperatureC = 0.0f;              /*!<   Temperature in Celsius degrees                         */
    uint8_t  myMessage[ TX_BUFF_SIZE ] = { 0 }; /*!<   Message to be transmitted through the UART             */

    conf_WDT    ();
    conf_CLK    ();
    conf_GPIO   ();
    conf_UART   ();
    conf_REF_A  ();
    conf_ADC    ();
    conf_TimerA ();


    /* All interrupts are enabled    */
    __enable_interrupt();


    while ( 1 )
    {
        LPM3;

        if ( myState == STATE_ACTION )
        {
            myTemperatureC   = (float)( ( (float)myRawTemp - CALADC12_12V_30C ) * ( 85.0f - 30.0f ) ) / ( CALADC12_12V_85C - CALADC12_12V_30C ) + 30.0f;

            sprintf ( (char*)myMessage, "Temp = %d mC\r\n", (int)( 100*myTemperatureC ) );


            /*  Clean and Enable interrupts: Tx only     */
            UCA0IFG &=  ~( UCTXIFG );
            UCA0IE  &=  ~( UCRXIE );
            UCA0IE  |=   ( UCTXIE );

            /*  Start transmitting data through the UART     */
            myPtr        =  &myMessage[0];
            UCA0TXBUF    =  *myPtr;
        }
    }
}
