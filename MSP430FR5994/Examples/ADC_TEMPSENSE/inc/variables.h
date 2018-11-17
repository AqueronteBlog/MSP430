/**
 * @brief       variables.h
 * @details     Constants and variables used by the example.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/November/2018
 * @version     17/November/2018     The ORIGIN
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
/**@brief Commands.
 */
typedef enum{
  CMD_LED1  = BIT0,         /*!<   Command: LED1   */
  CMD_LED2  = BIT1,         /*!<   Command: LED2   */
  CMD_WRONG = BIT2          /*!<   Command: Wrong  */
} myCommands_t;


/**@brief States of the system.
 */
typedef enum{
  STATE_LOW_POWER   = BIT0, /*!<   Low power state   */
  STATE_ACTION      = BIT1  /*!<   Do something!     */
} system_states_t;

/**@brief Variables.
 */


#ifdef __cplusplus
}
#endif

#endif /* VARIABLES_H_ */
