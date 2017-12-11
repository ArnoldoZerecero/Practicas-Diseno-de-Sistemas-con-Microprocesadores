/*
 * UART.h
 *
 *  Created on: Jul 24, 2017
 *      Author: Alumnos
 */

#ifndef UART_H_
#define UART_H_

#define BAUD_RATE (7) /*SBR = Baud Clock / ((OSR+1)*Baud Rate Deseado)*/ /*Si Baud Clock = 20.97Mhz y Baud Rate Deseado = 115200, SBR = 7*/
#define OSR (25) /*Over Sampling Ratio*/

typedef void(* UartUserCallback_t)(unsigned char); /*Función de Callback, para la cual se creará un apuntador*/


typedef struct 
{
	unsigned char bStopBitNumber; /*Elige entre usar 1 o 2 stop bits*/ 
	unsigned short wBaudRate; /*Concatenación de 13 bits de high y low*/ /*High -> Bit 4 - 0 UARTx_BDH*/ /* Low -> Bit 7 - 0 UARTx_BDL*/
	unsigned char  bTamanoTrama; /*Elegir entre tramas de 8 y 9 bits de longitud*/ /*Bit 4 de UARTx_C1*/
	unsigned char  bParityEnable; /*Bit 1 del UARTx_C1*/
	unsigned char  bParityType; /*Bit 0 del UARTx_C1*/
	unsigned char  bOSR; /*Elegir valor de 5 bits de over sampling ratio*/
	UartUserCallback_t pfnCallback; /*Apuntador a función Callback*/
}UartConfigInit_t;

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

void vfnUARTCallback(unsigned char bDatosReceptor);

void vfnUartTransmision(unsigned char  * DataToSend, unsigned short  DataSize);

void vfnUartInit (UartConfigInit_t * pUartUserConfig);

#if defined(__cplusplus)
}
#endif // __cplusplus




#endif /* UART_H_ */
