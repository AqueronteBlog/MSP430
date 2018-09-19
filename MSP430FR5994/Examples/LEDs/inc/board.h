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
  LED1  = 21,               /*!<   LED1: P0.21   */
  LED2  = 22,               /*!<   LED2: P0.22   */
  LED3  = 23,               /*!<   LED3: P0.23   */
  LED4  = 24                /*!<   LED4: P0.24   */
} NRF51DK_board_leds_t;


/**@brief UART0.
 */
typedef enum{
  UART0_TX  =   9,          /*!<   UART TX: P0.9    */
  UART0_RX  =   11          /*!<   UART RX: P0.11   */
} NRF51DK_board_uart0_t;


/**@brief TWI0.
 */
typedef enum{
  TWI0_SCL  =   7,          /*!<   TWI0 SCL: P0.7    */
  TWI0_SDA  =   30          /*!<   TWI0 SDA: P0.30   */
} NRF51DK_board_twi0_t;


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
