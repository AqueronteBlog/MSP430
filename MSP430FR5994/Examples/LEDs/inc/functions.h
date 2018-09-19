/**
 * @brief       functions.h
 * @details     Functions's header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/September/2018
 * @version     19/September/2018   The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <msp430.h>

#include "board.h"
#include "variables.h"

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function prototypes.
 */
void conf_LFCLK  ( void );
void conf_GPIO   ( void );
void conf_RTC1   ( void );
void conf_UART   ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */
