/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/October/2018
 * @version     31/October/2018    The ORIGIN
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
__interrupt void PORT5_ISR ( void );



/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */
