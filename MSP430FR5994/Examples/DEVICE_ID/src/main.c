/**
 * @brief       main.c
 * @details     [TODO]This example shows how to read the Device ID, hardware revision and
 *              firmware revision parameters. Every second, these data are transmitted over the UART.
 *
 *              The UART is configured at 115200 baudrate.
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/April/2019
 * @version     14/April/2019    The ORIGIN
 * @pre         This firmware was tested on the MSP-EXP430FR5994 with CCS vs9.0.0.00018.
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
#define TX_BUFF_SIZE  32                                /*!< UART buffer size           */
#define DEVICE_ID         *( (unsigned int *)0x1A04 )   /*!< Device ID                  */
#define HARDWARE_REVISION *( (unsigned int *)0x1A06 )   /*!< Hardware revision          */
#define FIRMWARE_REVISION *( (unsigned int *)0x1A07 )   /*!< Firmware revision          */


/**@brief Variables.
 */
volatile uint8_t        *myPtr;                         /*!< Pointer to point out myMessage                     */
volatile system_states_t myState   =   STATE_LOW_POWER; /*!< State of the system                                */



/**@brief Function Prototypes.
 */



/**@brief Function for application main entry.
 */
int main(void)
{
    uint8_t  myMessage[ TX_BUFF_SIZE ] = { 0 }; /*!<   Message to be transmitted through the UART             */

    conf_WDT    ();
    conf_CLK    ();
    conf_GPIO   ();
    conf_UART   ();
    conf_TimerB ();


    /* All interrupts are enabled    */
    __enable_interrupt();


    while ( 1 )
    {
        switch ( myState )
        {
        default:
        case STATE_LOW_POWER:
            LPM3;
            break;

        case SEND_DATA_OVER_UART:
            /* Pack the message  */
            sprintf ( (char*)myMessage, "Device ID = 0x%x (0x82A1) | HW revision: 0x%x | FW revision: 0x%x\r\n", (uint16_t)DEVICE_ID, (uint16_t)HARDWARE_REVISION, (uint16_t)FIRMWARE_REVISION );

            /*  Clean and Enable interrupts: Tx only     */
            UCA0IFG &=  ~( UCTXIFG );
            UCA0IE  &=  ~( UCRXIE );
            UCA0IE  |=   ( UCTXIE );

            /*  Start transmitting data through the UART     */
            myPtr        =  &myMessage[0];
            UCA0TXBUF    =  *myPtr;

            /* Update the state  */
            myState  =   STATE_LOW_POWER;
            break;
        }
    }
}
