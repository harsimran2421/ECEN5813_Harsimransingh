/********************************************
 * *   Authors: Harsimransingh Bindra, Smitesh Modak
 * *   Date Edited: 10/01/2017
 * *
 * *   File: platform.h
 * *
 * *   Description: Header file for making the code platfrom independent
 * *
 * *
 * ********************************************************/
#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifdef KL25Z
#define printf(uint32_t) 0          //this statement is used to disable printf functions
#define print_memory(uint32_t ) 0   // This statement is used to disable the print_memory function
#endif
#endif
