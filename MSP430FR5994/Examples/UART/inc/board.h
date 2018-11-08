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
  LED1  = BIT0,               /*!<   LED1: P1.0   */
  LED2  = BIT1                /*!<   LED2: P1.1   */
} EXP430FR5994_board_leds_t;


/**@brief Buttons.
 */
typedef enum{
  S1  = BIT6,                /*!<   S1: P5.6     */
  S2  = BIT5                 /*!<   S2: P5.5     */
} EXP430FR5994_board_buttons_t;


/**@brief UCA0: UART0.
 */
typedef enum{
  UART0_TX  = BIT0,          /*!<   TX: P2.0     */
  UART0_RX  = BIT1           /*!<   RX: P2.1     */
} EXP430FR5994_board_uart0_t;


#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */
