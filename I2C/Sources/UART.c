/*
 * UART.c
 *
 *  Created on: Jul 24, 2017
 *      Author: Alumnos
 */

#include "derivative.h"
#include "UART.h"
#include "MISCELANEO.h"


static unsigned char *gbpDataToSend; /*Apuntador global al arreglo de datos que da el usuario*/

static unsigned short gwDataSize; /*Variable global para la cantidad de datos*/

static unsigned short gwIndex = 0; /*Variable global para el índice*/

static UartUserCallback_t gpfnCallback; /*Apuntador global a función Callback*/



void vfnUartInit(UartConfigInit_t * pUartUserConfig) /*Inicialización, se recibe el apuntador a la estructura*/
{
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; /*Inicializo system clk para uart0*/
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); /*Selecciono MCGFLLCLK*/
	NVIC_ISER |= (1<<12); /*Activación del módulo de interrupciones, para el UART0*/

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Activo clk para puerto A*/
	PORTA_PCR1 = PORT_PCR_MUX(2); /*Activación de PTA1 para UART0_RX*/
	PORTA_PCR2 = PORT_PCR_MUX(2); /*Activación de PTA2 para UART0_TX*/

	UART0_C2 &= ~(UART0_C2_RE_MASK | UART0_C2_TE_MASK); /*Me aseguro que el receptor y emisor estén apagados antes de cambiar la configuración*/

	UART0_C4 = UART0_C4_OSR(pUartUserConfig -> bOSR); /*Over sampling ratio*/
			
	UART0_BDH |=(pUartUserConfig -> bStopBitNumber << UART0_BDH_SBNS_SHIFT); /*Numero de stop bits definido por el usuario*/
	UART0_BDH |= UART0_BDH_SBR(pUartUserConfig -> wBaudRate >> 8); /*Baud rate high definido por el valor del usuario (bits 12-8)*/

	UART0_BDL = UART0_BDL_SBR(pUartUserConfig -> wBaudRate); /*Baud rate low definido por el valor del usuario (bits 7-0)*/

	UART0_C1 |= pUartUserConfig->bTamanoTrama << UARTLP_C1_M_SHIFT; /*Tamaño de la trama, 8 o 9 bits*/


	if(pUartUserConfig->bParityEnable) /*Si se desea activar la paridad*/
	{
		UART0_C1 |= (UART0_C1_PE_MASK); /*Se pone en 1 el bit PE*/
		UART0_C1 |= pUartUserConfig->bParityType << UART0_C1_PT_SHIFT;
	}

	UART0_C2 |= (UART0_C2_RE_MASK | UART0_C2_RIE_MASK); /*Activar receiver enable y receiver interrupt*/

	if(pUartUserConfig->pfnCallback != 0)
	{
		gpfnCallback = pUartUserConfig->pfnCallback; /*Si existe función de Callback, se iguala el apuntador de función global al de la estructura, para acceder al callback de main*/
	}
}

void vfnUartTransmision(unsigned char * bpDataToSend, unsigned short wDataSize) /*Función de transmisión, recibe el apuntador al arreglo de datos y el número de datos a transmitir*/
{
	if(!(UART0_C2 & UART0_C2_TIE_MASK)) /*Si la interrupción para el transmisor no está activada (aun no se comienza a mandar dato alguno)*/
	{
		gbpDataToSend = bpDataToSend; /*Se almacena en la variable global, el arreglo de datos de entrada*/
		gwDataSize = wDataSize; /*Se almacena en la variable global, la cantidad de datos*/

		gwIndex = 0; /*Cada que se realize una nueva transmisión, se reinicia el índice en 0*/
		
		UART0_D = gbpDataToSend[gwIndex]; /*Se escribe en UART0_D el primer dato*/
		gwIndex++; /*Se incrementa el índice*/

		UART0_C2 |= (UART0_C2_TIE_MASK | UART0_C2_TE_MASK); /*Se activa el interrupt del transmisor y el enable del transmisor al comenzar a mandar datos*/
	}
}

void UART0_IRQHandler(void) /*Función de interrupción. Se entra aquí cada que las banderas de Transmission Buffer Empty y Receiver Buffer Full, para escribir un nuevo dato en el transmisor y leerlo en el receptor. Se comparten variables globales*/
{
	unsigned char bDatoRecibido;

	if((UART0_S1 & UART0_S1_TDRE_MASK) || (UART0_S1 & UART_S1_TC_MASK))  /*Si el Buffer del transmisor está vacío o si la transmisión fue completada*/
	{
		if (gwIndex < gwDataSize) /*Si aun faltan datos por enviar*/
		{
			UART0_D = gbpDataToSend[gwIndex]; /*Se escribe en el UART0_D el dato actual*/
			gwIndex++; /*Se incrementa el índice*/ 
		}
		else
		{
			UART0_C2 &= ~UART0_C2_TIE_MASK; /*Se apaga el interrupt del transmisor, finalizando el paso de datos*/
		}
	}

	if(UART0_S1 & UART0_S1_RDRF_MASK) /*Si el Buffer del receptor está lleno*/
	{
		bDatoRecibido = UART0_D; /*Se lee el dato que se recibió*/
		gpfnCallback(bDatoRecibido); /*Se llama la función de Callback y se le manda el dato recibido como parámetro*/
	}
}
