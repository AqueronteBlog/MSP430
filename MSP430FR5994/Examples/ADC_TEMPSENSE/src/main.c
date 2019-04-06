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
#define TX_BUFF_SIZE  32                                /*!<   UART buffer size                                       */


/**@brief Variables.
 */
volatile myCommands_t   myRX_cmd   =   CMD_WRONG;       /*!<   Command received from the UART                         */
volatile uint8_t        *myPtr;                         /*!<   Pointer to point out myMessage                         */
volatile system_states_t myState   =   STATE_LOW_POWER; /*!<   State of the system                                    */


/**@brief Function Prototypes.
 */



/**@brief Function for application main entry.
 */
int main(void)
{
    uint8_t  myMessage[ TX_BUFF_SIZE ];      /*!<   Message to be transmitted through the UART             */

    conf_WDT    ();
    conf_CLK    ();
    conf_GPIO   ();
    conf_UART   ();
    conf_ADC    ();
    conf_TimerA ();


    /* All interrupts are enabled    */
    __enable_interrupt();


    while ( 1 )
    {
        /*LPM1;

        if ( myState == STATE_ACTION )
        {
            switch ( myRX_cmd )
            {
                case CMD_LED1:
                    P1OUT   ^=   LED1;                          // Change state of LED1
                    sprintf ( (char*)myMessage, "LED1\r\n" );
                    break;

                case CMD_LED2:
                    P1OUT   ^=   LED2;                          // Change state of LED2
                    sprintf ( (char*)myMessage, "LED2\r\n" );
                    break;

                case CMD_WRONG:
                    sprintf ( (char*)myMessage, "Wrong command!\r\n" );
                    break;
            }

             Clean and Enable interrupts: Tx only
            UCA0IFG &=  ~( UCTXIFG );
            UCA0IE  &=  ~( UCRXIE );
            UCA0IE  |=   ( UCTXIE );

             Start transmitting data through the UART
            myPtr        =  &myMessage[0];
            UCA0TXBUF    =  *myPtr;
        }*/
    }
}
