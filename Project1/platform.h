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

#ifdef KL25z
#define printf(uint32_t) 0
#define print_memory(uint32_t ) 0
#endif
#endif
