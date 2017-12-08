
#ifndef NON_BLOCK_LOGGER_H_
#define NON_BLOCK_LOGGER_H_

#define NO_ERROR (0)

/*Enums to be used by Binary Logger*/
typedef enum LogID_VARIABLES{
  RTC_INITIALIZED = 1,
  LOGGER_INITIALIZED,
  GPIO_INITIALIZED,
  SPI_INITIALIZED,
  SYSTEM_INITIALIZED,
  SYSTEM_HALTED,
  INFO,
  WARNING,
  LOG_ERROR,
  DATA_RECEIVED,
  DATA_ANALYSIS_STARTED,
  DATA_ALPHA_COUNT,
  NUMERIC_COUNT,
  DATA_PUNCTUATION_COUNT,
  DATA_MISC_COUNT,
  DATA_ANALYSIS_COMPLETED,
  HEARTBEAT
}LogID;

/******************************************
 * * Binary Logger Structure
 * * logID : Indicates the log type
 * * LogLength : Gives the length of payload
 * * in bytes
 * * *Payload : Pointer to the payload data
 * ******************************************/
typedef struct struct_LOG{
  uint16_t  logID;
  uint32_t  Timestamp;
  uint8_t   LogLength;
  uint8_t * Payload;
  uint8_t *checksum;
}LOG_t;

LOG_t *system_log;
/*********************************************************************
 * * create_log() - Function to allocate memory in heap to the
 * *                    Binary Log structure
 * * LOG_t *(return_value)- Pointer of type Log_t which points to the location
 * *                  in heap memory where structure is created.
 * *********************************************************************/
LOG_t *create_log();

/**********************************************************************
 * * log_item() - Function to call the logger functions which push
 * *         the binary log data to serial output
 * * Log_t *ptr - Structure pointer which stores the log data that
 * *           needs to be logged on the serial output
 * * uint8_t(return_value)- Return NO_ERROR when all the data is logged
 * **********************************************************************/
uint8_t log_item(LOG_t *ptr);

/**********************************************************************
 * * destroy_log() - Function to free the structure memory from heap
 * * Log_t *ptr - Pointer of the structure that needs to be freed
 * * uint8_t(return_value)- Return NOERROR when structure is freed from memory
 * **********************************************************************/
uint8_t destroy_log(LOG_t *ptr);

#endif /* NON_BLOCK_LOGGER_H_ */
