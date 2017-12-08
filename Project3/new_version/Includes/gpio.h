/*************************************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 11/27/2017
 * *
 * * File : gpio.h
 * * Description : Header file for GPIO initialize functions
 * *               - void init_GPIO_nrf()
 * *               - void init_GPIO_led()
 * ***************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#define AL_MODE (0x0000200)

/*Function to initialize gpio pins for NRF module*/
/*********************************************************************
 * * GPIO_nrf_init() - Function to initialize GPIO pins for NRF module
 * *
 * *********************************************************************/
void init_GPIO_nrf();


#define PIN18  (0x400000)

/*********************************************************************
 * * GPIO_led_init() - Function to initialize gpio pins for RED LED module
 * *
 * *********************************************************************/
void init_GPIO_led();


#endif /* GPIO_H_ */
