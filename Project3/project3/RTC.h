/*Authors : Harsimransingh Bindra, Smitesh Modak
* * Date : 11/26/2017
* *
* * File : RTC.h
* * Description : Header file for RTC initialization functions
* *             -void init_rtc(void)
  * ***************************************************************************/

#ifndef RTC_H_
#define RTC_H_

#include <time.h>

#define ADJUSTMENT (0)

  uint8_t * ctime_string;
  void init_rtc(void);

#endif /* RTC_H_ */
