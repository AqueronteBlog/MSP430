/**
 * @brief       main.c
 * @details     This example shows how to work with the internal temperature sensor triggered by Timer B.
 *              Every second a new temperature conversion is triggered, the data is
 *              processed and then, transmitted over the UART.
 *
 *              The UART is configured at 115200 baudrate.
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/April/2019
 * @version     13/April/2019    The ORIGIN
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
#define TX_BUFF_SIZE  32                                /*!< UART buffer size                                   */
#define CALADC12_12V_30C  *( (unsigned int *)0x1A1A )   /*!< Temperature Sensor Calibration-30 C                */
#define CALADC12_12V_85C  *( (unsigned int *)0x1A1C )   /*!< Temperature Sensor Calibration-85 C                */

/**@brief Variables.
 */
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

        case PACK_TEMPERATURE:
            /* Process the temperature   */
            myTemperatureC   = (float)( ( (float)myRawTemp - CALADC12_12V_30C ) * ( 85.0f - 30.0f ) ) / ( CALADC12_12V_85C - CALADC12_12V_30C ) + 30.0f;

            /* Pack the message  */
            sprintf ( (char*)myMessage, "Temp = %d mC\r\n", (int)( 100*myTemperatureC ) );

            /* Update the state  */
            myState  =   SEND_TEMP_OVER_UART;

        case SEND_TEMP_OVER_UART:
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
