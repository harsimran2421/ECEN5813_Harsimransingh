#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"
#include "non_block_logger.h"
#include "binary_logger.h"
#include "conversion.h"
#include "project2.h"
#include "FRDM.h"
#include "project3.h"

//#include "profiler.h"
#include "DMA.h"
/*Defining buffer lengths*/
uint8_t length_TXbuff=100;
uint8_t length_RXbuff=20;

#ifdef BBB
  #define UART_configure()
  #define init_rtc()
  #define FRDM_log_data(data,length) BBB_log_data(data,length)
  #define FRDM_log_integer(set,length) BBB_log_integer(set,length)
  #define FRDM_log_string(data) BBB_log_string(data)
  #define UART0_C2 (replace)
#endif

/*Compile time switch for HOST*/
#ifdef HOST
  #define UART_configure()
  #define init_rtc()
  #define FRDM_log_data(data,length) BBB_log_data(data,length)
  #define FRDM_log_integer(set,length) BBB_log_integer(set,length)
  #define FRDM_log_string(data) BBB_log_string(data)
  #define UART0_C2 (replace)
#endif

/*Compile time switch for FRDM*/
#ifdef FRDM
  #include "uart.h"
  #include "RTC.h"
  #include "MKL25Z4.h"
  #include "nrf.h"
  #include "spi.h"
  #define printf(...)
#endif
void project3()
{
/*Create log item*/
  system_log = create_log();
/*Create and Initialize Transmit Circular Buffer*/
  transbuf = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(transbuf, length_TXbuff);
  UART_configure();
  init_rtc();
  system_log->logID = RTC_INITIALIZED;
  log_item(system_log);
  init_spi();
#ifdef FRDM
//system_log->Timestamp=RTC_TSR;
#endif
#ifdef LOG_ON
	system_log->logID = SPI_INITIALIZED;
	log_item(system_log);
	system_log->logID = LOGGER_INITIALIZED;
	log_item(system_log);
	system_log->logID = SYSTEM_INITIALIZED;
	log_item(system_log);
#endif
/*Create and Initialize Receiver Circular Buffer*/
  recbuf = (CB_t *) calloc(1,sizeof(CB_t));
  CB_init(recbuf,length_RXbuff);
#ifdef LOG_ON
/*Testing log_data function*/
  uint8_t payload_string1[18] = "Testing log_data\n\r";
  system_log->logID = INFO;
  system_log->LogLength = 18;
  system_log->Payload = payload_string1;
  log_item(system_log);
  uint8_t test1[4]={'1','2','3','4'};
  uint8_t * data = test1;
  uint8_t length=(sizeof(test1)/sizeof(uint8_t));
  FRDM_log_data(data,length);
  printf("\n");
/*Testing log_string function*/
  uint8_t payload_string2[20] = "Testing log_string\n\r";
  system_log->logID = INFO;
  system_log->LogLength = 20;
  system_log->Payload = payload_string2;
  log_item(system_log);
  uint8_t test2[]="This is a string";
  data=test2;
  FRDM_log_string(data);
  printf("\n");
/*Testing log_integer function*/
  uint8_t payload_string3[21] = "Testing log_integer\n\r";
  system_log->logID = INFO;
  system_log->LogLength = 21;
  system_log->Payload = payload_string3;
  log_item(system_log);
  uint32_t test3=1234;
  length=sizeof((test3)/sizeof(uint8_t));
  FRDM_log_integer(test3,length);
  printf("\n");
  //profiler_run();
#else
#ifdef HOST
  printf("logging functionality is disabled");
#elif BBB
  printf("logging functionality is disabled");
#else
/*Print when logging is disabled*/
  uint8_t string3[34]=" Logging functionality is disabled";
  uint8_t *str_ptr=string3;
  uint8_t length=0;
  uint8_t state;
  while(*str_ptr!='\0'){
  length++;
  str_ptr++;
}
str_ptr=str_ptr-length;
state = CB_buffer_add_items(transbuf,str_ptr,length);
if(state == NULL_POINTER)
{
  uint8_t nullPointerError[] = "NULL Pointer\n\r";
  system_log->logID = LOG_ERROR;
  system_log->LogLength = 14;
  system_log->Payload = nullPointerError;
  log_item(system_log);
}
#endif
#endif

#ifdef FRDM

	//Write  and read to NRF CONFIG register
	#ifdef LOG_ON
		uint8_t payload_string11[21] = " Testing CONFIG R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 21;
		system_log->Payload = payload_string11;
		log_item(system_log);
	#endif

	nrf_write_config(CONFIG_PWR_UP | CONFIG_PRIM_RX);
	uint8_t configVal = nrf_read_config();
	FRDM_log_string("CONFIG Value: ");
	FRDM_log_integer((uint32_t)configVal,2);
	FRDM_log_string("\n\r");

	//Read NRF STATUS register
	#ifdef LOG_ON
		uint8_t payload_string22[19] = " Testing STATUS R\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 19;
		system_log->Payload = payload_string22;
		log_item(system_log);
	#endif

	uint8_t statusVal = nrf_read_status();
	FRDM_log_string("STATUS Value: ");
	FRDM_log_integer((uint32_t)statusVal,2);
	FRDM_log_string("\n\r");

	//Write and Read to NRF TX ADDR register
	#ifdef LOG_ON
		uint8_t payload_string33[22] = " Testing TX ADDR R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 22;
		system_log->Payload = payload_string33;
		log_item(system_log);
	#endif
    
  uint8_t tx_values[5] = { 10, 20, 30, 40, 50};
	nrf_write_TX_ADDR(tx_values);
	tx_array = nrf_read_TX_ADDR();

	for(uint8_t i=0;i<5;i++){
		FRDM_log_integer((uint32_t)tx_array[i],3);
		FRDM_log_string(" ");
	}

	//Write and Read to NRF RF SETUP register
	#ifdef LOG_ON
		uint8_t payload_string4[23] = " Testing RF SETUP R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 23;
		system_log->Payload = payload_string4;
		log_item(system_log);
	#endif

	nrf_write_rf_setup(RF_SETUP_VALUE);
	uint8_t rdSetupVal = nrf_read_rf_setup();
	FRDM_log_string("RF SETUP Value: ");
	FRDM_log_integer((uint32_t)rdSetupVal,2);
	FRDM_log_string("\n\r");

	//Write and Read to NRF RF CH register
	#ifdef LOG_ON
		uint8_t payload_string5[20] = " Testing RF CH R/W\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 20;
		system_log->Payload = payload_string5;
		log_item(system_log);
	#endif

	nrf_write_rf_ch(RF_CHANNEL_VALUE);
	uint8_t rfChVal = nrf_read_rf_ch();
	FRDM_log_string("RF CH Value: ");
	FRDM_log_integer((uint32_t)rfChVal,2);
	FRDM_log_string("\n\r");

	//Read NRF FIFO STATUS register
	#ifdef LOG_ON
		uint8_t payload_string6[24] = " Testing FIFO STATUS R\n\r";
		system_log->logID = INFO;
		system_log->LogLength = 24;
		system_log->Payload = payload_string6;
		log_item(system_log);
	#endif

	uint8_t fifoStatusVal = nrf_read_fifo_status();
	FRDM_log_string(" FIFO STATUS Value: ");
	FRDM_log_integer((uint32_t)fifoStatusVal,2);
	FRDM_log_string("\n\r");
	//destroy_log(system_log);
	//system_log = NULL;

#endif
#ifdef FRDM
	UART0_C2|=UART_C2_TIE_MASK;
	while(1)
	{
		if(recflag == 1)
		{
			project2();
		}
	}
#endif
}
