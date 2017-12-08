/*************************************************************************
 * * Authors : Harsimransingh Bindra, Smitesh Modak
 * * Date : 11/25/2017
 * *
 * * File : binary_logger.h
 * * Description : Header file for Binary logger functions
 * *               -void FRDM_log_data(uint8_t * data,uint8_t length)
 * *               -void log_flush(void)
 * *               -void BBB_log_data(uint8_t * data,uint8_t length)
 * *               -void FRDM_log_string(uint8_t * data)
 * *               -void BBB_log_string(uint8_t * data)
 * *               -void FRDM_log_integer(uint32_t set,uint8_t length)
 * *               -void BBB_log_integer(uint32_t set,uint8_t length)
 * ***************************************************************************/
#ifndef BINARY_LOGGER_H_
#define BINARY_LOGGER_H_

#ifdef FRDM
#define printf(...)
#endif

/****************************************************************************
 * * This function is used as to add data to circular buffer and then transmit
 * * through uart for FRDM
 * * uint8_t * data - This pointer points to the array where the data is stored
 * * uint8_t length - This gives the length of bytes to be transmitted
 * *****************************************************************************/
void FRDM_log_data(uint8_t * data,uint8_t length);

/****************************************************************************
 * * This function is used to block until the logger buffer is empty
 * ****************************************************************************/
void log_flush(void);

/****************************************************************************
 * * This function is used to add string to circular buffer and then transmit
 * * through uart for FRDM
 * * uint8_t * data - This pointer points to the string to be transmitted
 * ****************************************************************************/
void FRDM_log_string(uint8_t * data);


/****************************************************************************
 * * This function is used as to add data to circular buffer and then display
 * * using printf for BBB and host machine
 * * uint8_t * data - This pointer points to the array where the data is stored
 * * uint8_t length - This gives the length of bytes to be transmitted
 * *****************************************************************************/
void BBB_log_data(uint8_t * data,uint8_t length);


/****************************************************************************
 * * This function is used to add string to circular buffer and then display
 * * using printf for BBB and host machine
 * * uint8_t * data - This pointer points to the string to be transmitted
 * ****************************************************************************/
void BBB_log_string(uint8_t * data);


/***************************************************************************
 * * This function is used to convert integer to ascii and then transmit
 * * through uart for FRDM
 * * uint32_t set - This variable has the integer variable which is to be
 *  convert to ascii
 *  * uint8_t length - This variable gives the length to be converted
 *  **************************************************************************/
void FRDM_log_integer(uint32_t set,uint8_t length);

/***************************************************************************
 * * This function is used to convert integer to ascii and then display
 * * using printf for BBB and host machine
 * * uint32_t set - This variable has the integer variable which is to be
 *  convert to ascii
 *  * uint8_t length - This variable gives the length to be converted
 *  **************************************************************************/
void BBB_log_integer(uint32_t set,uint8_t length);

#endif /* BINARY_LOGGER_H_ */
