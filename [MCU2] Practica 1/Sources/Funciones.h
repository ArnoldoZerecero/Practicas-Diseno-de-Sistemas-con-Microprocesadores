/*

 * Funciones.h
 *
 *  Created on: Sep 10, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

void vfnMemCpy (unsigned char * bpSource, unsigned char * bpDest, unsigned short wSize);

void vfnMemSet(unsigned char * bpDest, unsigned char bByteToFill, unsigned short wSize);

unsigned char bfnFindMax(unsigned char * bpDest, unsigned short wSize);

unsigned char bfnFindMin(unsigned char * bpDest, unsigned short wSize);

unsigned char bfnStrCmp(unsigned char * bpSource, unsigned char * bpDest, unsigned short wSize);

unsigned char * bpfnByteAddress(unsigned char * bpString, unsigned char bCharToFind, unsigned short
wSize);

void vfnSort (unsigned char * bpString, unsigned short wStringSize);

unsigned short wfnStrLen (unsigned char * bpString);

unsigned short wfnSprintf (char * bpString, const char * bpFormat, void * vpaExtraArguments[]);


#endif /* FUNCIONES_H_ */
