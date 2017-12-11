/*
 * MISCELANEO.h
 *
 *  Created on: Aug 2, 2017
 *      Author: Alumnos
 */

#ifndef MISCELANEO_H_
#define MISCELANEO_H_

#include <stdint.h>

#define CLEAR_ALL_BUT_UNITS(x) ((x) & ~(0xFFF0))
#define CLEAR_ALL_BUT_TENS(x) (((x) & ~(0xFF0F)) >> 4)
#define CLEAR_ALL_BUT_HUNDREDS(x) (((x) & ~(0xF0FF)) >> 8)
#define ESC_CARACTER 27
#define ABRIR_CORCHETE_CARACTER 91
#define BACKSPACE_CARACTER 8
#define DEGREE_SYMBOL (248)


#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

uint16_t wfnBCD(uint16_t wResultado);

uint32_t dwfnBCDADecimal(uint8_t bUnidades, uint8_t bDecenas, uint8_t bCentenas, uint8_t bMillares);

void vfnDelay (uint32_t dwDelay);

#if defined(__cplusplus)
}
#endif // __cplusplus


#endif /* MISCELANEO_H_ */
