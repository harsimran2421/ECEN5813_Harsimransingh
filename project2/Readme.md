EN 5813- Principles of Embedded Softwares: Project 2

Authors: Harsimransingh Bindra, Smitesh Modak

Date: 10/29/2017

Supported Platforms: Freedom Freescale KL25Z, HOST LINUX-Ubuntu.

Goals:
1. Implementing an optimized circular buffer.
2. Unit testing data, memory and circular buffer functions using cmocka framework.
3. Transmission and reception using UART connection. 

File structure:
* Libraries: Consisting of Makefile and folders required to install and run unit tests in cmocka framework.

* Headers: Consisting of header files required for our project.
1. data.h – Header file for implementing data manipulation functions.
2. memory.h – Header file for implementing memory manipulation functions.
3. circbuff.h – Header file for implementing circular buffer functions.
6. uart.h - Header file for implementing uart module functions.
* SOURCES: Consisting of source files required for our project.
1. data.c - Source file for implementing data manipulation functions.
2. memory.h - Source file for implementing memory manipulation functions.
3. circbuff.c - Source file for implementing circular buffer functions.
6. uart.c - Source file for implementing uart module functions.
7. uinttest_data.c - Source file for unit testing data manipulation functions using cmocka.
8. test_memory.c - Source file for unit testing memory manipulation functions using cmocka.
9. unit_test_buffer.c - Source file for unit testing circular buffer functions using cmocka.
using cmocka.
11. main.c – main source file for running the project.
* Makefile1 – Makefile required to run unit test functions using cmocka framework.
* sources.mk – Contains path for source and header files.
