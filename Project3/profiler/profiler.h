#ifndef INCLUDES_PROFILER_H_
#define INCLUDES_PROFILER_H_
#ifdef FRDM
#include <stdio.h>
#include <stdint.h>
#include "systick.h"
#include "DMA.h"
#include "profiler.h"
#include "MKL25Z4.h"

void profiler_run();
#endif

#endif /* INCLUDES_PROFILER_H_ */
