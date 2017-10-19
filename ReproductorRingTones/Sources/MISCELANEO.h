/*
 * MISCELANEO.h
 *
 *  Created on: Aug 2, 2017
 *      Author: Alumnos
 */

#ifndef MISCELANEO_H_
#define MISCELANEO_H_

#include <stdint.h>

#define CLEAR_ALL_BUT_UNITS ~(0xFFF0)
#define CLEAR_ALL_BUT_TENS ~(0xFF0F)
#define CLEAR_ALL_BUT_HUNDREDS ~(0xF0FF)
#define DELAY_TIME 3000
#define ESC_CARACTER 27
#define ABRIR_CORCHETE_CARACTER 91
#define BACKSPACE_CARACTER 8
#define DEGREE_SYMBOL (248)
#define CERO_CARACTER 48
#define DOS_CARACTER 50
#define NUEVE_CARACTER 57
#define DOS_PUNTOS_CARACTER 59


#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

uint16_t wfnBCD(uint16_t wResultado);

uint32_t dwfnBCDADecimal(uint8_t bUnidades, uint8_t bDecenas, uint8_t bCentenas, uint8_t bMillares);

void vfnGPIOInit(void);

void vfnDelay (uint32_t dwDelay);

#if defined(__cplusplus)
}
#endif // __cplusplus


#endif /* MISCELANEO_H_ */
