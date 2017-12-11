/*
 * longFunctions.h
 *
 *  Created on: Nov 19, 2017
 *      Author: Windows 8.1
 */

#ifndef longFUNCTIONS_H_
#define longFUNCTIONS_H_

#define CLEAR_UPPER_16_BITS ~((1<<31) + (1<<30) + (1<<29) + (1<<28) + (1<<27) + (1<<26) + (1<<25) + (1<<24) + (1<<23) + (1<<22) + (1<<21) + (1<<20) + (1<<19) + (1<<18) + (1<<17) + (1<<16))
#define CLEAR_UPPER_9_BITS ~((1<<31) + (1<<30) + (1<<29) + (1<<28) + (1<<27) + (1<<26) + (1<<25) + (1<<24) + (1<<23))

float ffnInt2Float (short iNum);

float ffnLong2Float (long iNum);

short ifnFloat2Int (float fNum);

float ffnFloatAdd (float fA, float fB);

float ffnFloatSub (float fA, float fB);

char bfnFloatCmp (float fA, float fB);

float ffnFloatMpy (float fA, float fB);

float ffnFloatDiv (float fA, float fB);

float ffnFloatMod (float fA, float fB);

#endif /* longFUNCTIONS_H_ */
