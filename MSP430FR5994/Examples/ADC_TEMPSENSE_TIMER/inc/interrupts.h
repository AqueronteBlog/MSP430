/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/April/2019
 * @version     13/April/2019    The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <msp430.h>

#include "board.h"
#include "variables.h"


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
__interrupt void ADC12_B_ISR    ( void );
__interrupt void UART0_ISR      ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint8_t         *myPtr;
extern volatile system_states_t myState;
extern volatile uint16_t        myRawTemp;


#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
