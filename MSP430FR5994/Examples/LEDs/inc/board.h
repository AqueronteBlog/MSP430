/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): MSP-EXP430FR5994 LaunchPad.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/September/2018
 * @version     19/September/2018      The ORIGIN
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief LEDs.
 */
typedef enum{
  LED1  = 0x00,               /*!<   LED1: P1.0   */
  LED2  = 0x01                /*!<   LED2: P1.1   */
} EXP430FR5994_board_leds_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
