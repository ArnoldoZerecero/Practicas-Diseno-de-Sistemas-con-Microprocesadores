/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Includes Section
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "derivative.h" 
#include "LedDriver.h"
#include "ButtonDriver.h" 
#include "DisplayDriver.h"
#include "MISCELANEO.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Defines & Macros Section
///////////////////////////////////////////////////////////////////////////////////////////////////
#define BOTON_HOLD 0
#define FREQ_IN 1
#define AZUL 0
#define ROJO 1
#define VERDE 2


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                       Typedef Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                  Function Prototypes Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Constants Section
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Global Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long gdwFrecuenciaIn = 0; /*Acumulador para saber cuántos ciclos están entrando por segundo (frecuencia)*/

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                   Static Variables Section
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
//                                      Functions Section
///////////////////////////////////////////////////////////////////////////////////////////////////


int main(void){
	static unsigned char bLedCounter = 0; /*Contador para saber cuándo actualizar el driver de los leds*/
	static unsigned char bButtonCounter = 0; /*Contador para saber cuándo actualizar el driver de los botones*/
	static unsigned char bDisplayCounter = 0; /*Contador para saber cuándo actualizar el driver de los displays*/
	static unsigned short wFrequencyCounter = 0; /*Contador para saber cuándo mandar el valor de frecuencia leído a los displays*/
	static unsigned long dwAcumulador = 0; /*Acumulador para la frecuencia entrante*/
	static unsigned char bModoHoldFlag = 0; /*Bandera para saber si se está en modo hold*/

	vfnButtonInit(); /*Se inicializan los módulos*/
	vfnDisplayInit();
	vfnLedInit();
	for(;;)
	{
		bLedCounter++; /*Se incrementa cada contador*/
		bButtonCounter++;
		bDisplayCounter++;
		wFrequencyCounter++;
		
		bfnLedBlink(AZUL,165,165,1); /*El led azul parpadea una vez cada segundo para demostrar que el sistema funciona*/

		if(bfnButtonClick(BOTON_HOLD) == 1) /*Si se presiona el botón de hold*/
		{
			bModoHoldFlag ^= 1; /*Se togglea el modo hold*/
		}

		if(bModoHoldFlag) /*Si se encuentra en modo hold*/
		{
			gdwFrecuenciaIn = dwAcumulador; /*Se manda el valor en que se quedó el acumulador*/
			bfnLedBlink(VERDE,83, 83, 1); /*El led verde parpadea 2 veces por segundo*/
		}
		if(dwAcumulador) /*Si está entrando una frecuencia*/
		{
			bfnLedBlink(ROJO,42,42,1); /*El led rojo parpadea 4 veces por segundo*/
		}

		if(bfnButtonClick(FREQ_IN) && !bModoHoldFlag) /*Si se está recibiendo una frecuencia y el sistema no se encuentra en modo hold*/
		{
			dwAcumulador++; /*Se incrementa el acumulador*/
		}
		if(bLedCounter == 75) /*Cada 75 ciclos*/
		{
			vfnLedDriver(); /*Se actualizan los leds*/
			bLedCounter = 0; /*Se reinicia el contador*/
		}
		if(bButtonCounter == 1)  /*Cada ciclo. Debe realizarse lo más rápido posible para poder captar las frecuencias altas*/
		{
			vfnButtonDriver(); /*Se actualizan los botones*/
			bButtonCounter = 0; /*Se reinicia el contador*/
		}
		if(bDisplayCounter == 80) /*Cada 80 ciclos*/
		{
			vfnDisplayDriver(); /*Se actualizan los displays*/
			bDisplayCounter = 0; /*Se reinicia el contador*/
		}
		if(wFrequencyCounter == 11600) /*Se encontró que cada 11600 ciclos se obtiene la frecuencia más exacta*/
		{
			gdwFrecuenciaIn = dwAcumulador; /*Se manda el valor en que se quedó el acumulador*/ 
			dwAcumulador = 0; /*Se reinicia el acumulador*/
			wFrequencyCounter = 0; /*Se reinicia el contador*/
		}
	}
	return 0;
}
