/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/April/2019
 * @version     13/April/2019     The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */
#include <stdint.h>

#ifndef VARIABLES_H_
#define VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Constants.
 */


/**@brief States of the system.
 */
typedef enum{
  STATE_LOW_POWER     = BIT0,   /*!<   Low power state          */
  PACK_TEMPERATURE    = BIT1,   /*!<   Process the temperature  */
  SEND_TEMP_OVER_UART = BIT2    /*!<   Send data over UART      */
} system_states_t;

/**@brief Variables.
 */


#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */
