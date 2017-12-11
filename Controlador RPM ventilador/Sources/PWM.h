/*
 * PWM.h
 *
 *  Created on: Nov 12, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>

#define PERIODO (10000)

typedef void(* PWMCallback)(void);


#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus
void vfnPWMInit(PWMCallback ApplicationCallback);

void vfnPWMDriver(void);


#if defined(__cplusplus)
}
#endif // __cplusplus

#endif /* PWM_H_ */
