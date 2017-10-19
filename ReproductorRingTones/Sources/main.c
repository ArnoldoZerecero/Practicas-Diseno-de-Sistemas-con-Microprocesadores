/*
 * main implementation: use this 'C' sample to create your own application
 *
 */


#include "TimerDriver.h"
#include "MISCELANEO.h"
#include "PIT.h"
#include "ButtonDriver.h"
#include "LedDriver.h"
#include "derivative.h" /* include peripheral declarations */

#define START_STOP_BTN 0

void vfnRingtone (unsigned char * bpRingtone); /*Función para leer el ringtone*/

volatile unsigned long gdwDivisorCntReload; /*Variable global para recargar la cuenta del divisor*/

volatile unsigned char gflgCountEnable = 0; /*Bandera pasa comenzar a reproducir el ringtone con el botón*/


int main(void)
{	
	static unsigned char _baRingtone[] = "8e6 8#d6 8e6 8#d6 8e6 8b5 8d6 8c6 4#a5 4- 8c5 8e5 8a5 4b5 4- 8e5 8#g5 8b5 4c6 4- 8e5 8e6 8#d6 8e6 8#d6 8e6 8b5 8d6 8c6 4#a5 4- 8c5 8e5 8a5 4b5 4- 8e5 8c6 8b5 4#a5"; /*Cadena con ringtone deseado (Beethoven - Für Elise)*/
	
	vfnPitInit(TARGET_TIME_30US,&vfnPitCallback); /*Inicialización del PIT*/
	vfnPitStart(); /*Comienza el contador del PIT*/
	vfnGPIOInit(); /*Inicialización de GPIO para el buzzer*/
	vfnLedInit(); /*Inicialización para el led*/
	vfnButtonInit(); /*Inicialización de GPIO para el botón*/
	
	for(;;) 
	{	   	
		vfnRingtone(_baRingtone); /*Se accede a la función que lee el ringtone deseado*/
		vfnTimerDriver(); /*Se accede al driver para revisar si se debe reducir en uno las cuentas*/
		
		if(!gflgCountEnable && !bfnTimeTargetReached(DURACION_CNT)) /*Mientras no se haya hecho click en el botón y ya haya terminado el ringtone anterior*/
		{
			vfnButtonDriver(); /*Se accede al driver para leer el estado del botón*/
			if(bfnButtonClick(START_STOP_BTN)) /*Si se presiona el botón*/
			{
				gflgCountEnable = 1; /*Se setea la bandera*/
			}
		}
		
		if(!bfnTimeTargetReached(DIVISOR_CNT) && bfnTimeTargetReached(DURACION_CNT)) /*Si la cuenta del divisor se acabó pero aun queda duración para el tono*/
		{
			vfnCntLoadAssign(gdwDivisorCntReload, DIVISOR_CNT); /*Se recarga la cuenta del divisor*/

		}
	}
	return 0;
}


void vfnRingtone (unsigned char * bpRingtone)
{	
	if(gflgCountEnable && !bfnTimeTargetReached(DURACION_CNT)) /*Solo se accede a la función si se activa la bandera global al presionarse el botón y la duración del tono ya terminó. Así se escribirá el siguiente tono*/
	{
		static unsigned long dwDuracionCnt; /*Variable para asignar la cuenta de duración*/
		static unsigned short _wOffset = 0; /*Variable para volver a la posición de la cadena donde se estaba leyendo*/
		bpRingtone = bpRingtone + _wOffset;
		
		do
		{
			if(*bpRingtone == ' ') /*Si se encuentra un espacio, quiere decir que los datos para un tono ya fueron escritos, se debe esperar a que se reproduzca ese tono, se regresa al for infinito*/
			{
				_wOffset++; /*Se incrementa el offset para avanzar un espacio la próxima vez*/
				return;
			}
			
			/*Se lee la duración del tono y se asigna el valor elegido a la cuenta de duración*/
			if(*bpRingtone == '1' && *(bpRingtone + 1) != ' ' && *(bpRingtone + 1) != '6')
			{
				dwDuracionCnt = 33333;
			}
			else if(*bpRingtone == '2' && *(bpRingtone + 1) != ' ') 
			{
				dwDuracionCnt = 16666;
			}
			else if(*bpRingtone == '4' && *(bpRingtone + 1) != ' ') 
			{
				dwDuracionCnt = 8333;
			}
			else if(*bpRingtone == '8' && *(bpRingtone + 1) != ' ') 
			{
				dwDuracionCnt = 4166;
			}
			else if(*bpRingtone == '1' && *(bpRingtone + 1) == '6') 
			{
				dwDuracionCnt = 2083;
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '3' && *(bpRingtone + 1) == '2') 
			{
				dwDuracionCnt = 1041;
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '-' ) /*Si se decidió el silencio*/
			{
				gdwDivisorCntReload = dwDuracionCnt; /*Se asigna la cuenta de duración a la cuenta de división para que ambas terminen a la vez y no se mande ningún uno al buzzer*/
			}
			/*Se lee la nota y escala elegida y se asigna la cuenta correspondiente a su frecuencia a la cuenta de divisor*/
			else if(*bpRingtone == 'c')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 2039;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 1019;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 510;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 255;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 127;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 64;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 32;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 16;
				}
				else if(*(bpRingtone + 1) == '9')
				{
					gdwDivisorCntReload = 8;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '#' && *(bpRingtone + 1) == 'c')
			{
				if(*(bpRingtone + 2) == '1')
				{
					gdwDivisorCntReload = 1924;
				}
				else if(*(bpRingtone + 2) == '2')
				{
					gdwDivisorCntReload = 962;
				}
				else if(*(bpRingtone + 2) == '3')
				{
					gdwDivisorCntReload = 481;
				}
				else if(*(bpRingtone + 2) == '4')
				{
					gdwDivisorCntReload = 240;
				}
				else if(*(bpRingtone + 2) == '5')
				{
					gdwDivisorCntReload = 120;
				}
				else if(*(bpRingtone + 2) == '6')
				{
					gdwDivisorCntReload = 60;
				}
				else if(*(bpRingtone + 2) == '7')
				{
					gdwDivisorCntReload = 30;
				}
				else if(*(bpRingtone + 2) == '8')
				{
					gdwDivisorCntReload = 15;
				}
				else if(*(bpRingtone + 2) == '9')
				{
					gdwDivisorCntReload = 8;
				}
				_wOffset = _wOffset + 2; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo y el tercer caracter*/
				bpRingtone = bpRingtone + 2;
			}
			else if(*bpRingtone == 'd')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 1817;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 908;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 454;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 227;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 114;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 57;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 28;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 14;
				}
				else if(*(bpRingtone + 1) == '9')
				{
					gdwDivisorCntReload = 7;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '#' && *(bpRingtone + 1) == 'd')
			{
				if(*(bpRingtone + 2) == '1')
				{
					gdwDivisorCntReload = 1714;
				}
				else if(*(bpRingtone + 2) == '2')
				{
					gdwDivisorCntReload = 857;
				}
				else if(*(bpRingtone + 2) == '3')
				{
					gdwDivisorCntReload = 428;
				}
				else if(*(bpRingtone + 2) == '4')
				{
					gdwDivisorCntReload = 214;
				}
				else if(*(bpRingtone + 2) == '5')
				{
					gdwDivisorCntReload = 107;
				}
				else if(*(bpRingtone + 2) == '6')
				{
					gdwDivisorCntReload = 54;
				}
				else if(*(bpRingtone + 2) == '7')
				{
					gdwDivisorCntReload = 27;
				}
				else if(*(bpRingtone + 2) == '8')
				{
					gdwDivisorCntReload = 13;
				}
				else if(*(bpRingtone + 2) == '9')
				{
					gdwDivisorCntReload = 7;
				}
				_wOffset = _wOffset + 2; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo y el tercer caracter*/
				bpRingtone = bpRingtone + 2;
			}
			else if(*bpRingtone == 'e')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 1618;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 809;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 405;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 202;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 101;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 51;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 25;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 13;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == 'f')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 1527;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 763;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 382;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 191;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 95;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 48;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 24;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 12;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '#' && *(bpRingtone + 1) == 'f')
			{
				if(*(bpRingtone + 2) == '1')
				{
					gdwDivisorCntReload = 1442;
				}
				else if(*(bpRingtone + 2) == '2')
				{
					gdwDivisorCntReload = 721;
				}
				else if(*(bpRingtone + 2) == '3')
				{
					gdwDivisorCntReload = 360;
				}
				else if(*(bpRingtone + 2) == '4')
				{
					gdwDivisorCntReload = 180;
				}
				else if(*(bpRingtone + 2) == '5')
				{
					gdwDivisorCntReload = 90;
				}
				else if(*(bpRingtone + 2) == '6')
				{
					gdwDivisorCntReload = 45;
				}
				else if(*(bpRingtone + 2) == '7')
				{
					gdwDivisorCntReload = 23;
				}
				else if(*(bpRingtone + 2) == '8')
				{
					gdwDivisorCntReload = 11;
				}
				_wOffset = _wOffset + 2; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo y el tercer caracter*/
				bpRingtone = bpRingtone + 2;
			}
			else if(*bpRingtone == 'g')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 1361;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 680;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 340;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 170;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 85;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 43;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 21;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 11;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '#' && *(bpRingtone + 1) == 'g')
			{
				if(*(bpRingtone + 2) == '1')
				{
					gdwDivisorCntReload = 1286;
				}
				else if(*(bpRingtone + 2) == '2')
				{
					gdwDivisorCntReload = 643;
				}
				else if(*(bpRingtone + 2) == '3')
				{
					gdwDivisorCntReload = 321;
				}
				else if(*(bpRingtone + 2) == '4')
				{
					gdwDivisorCntReload = 161;
				}
				else if(*(bpRingtone + 2) == '5')
				{
					gdwDivisorCntReload = 80;
				}
				else if(*(bpRingtone + 2) == '6')
				{
					gdwDivisorCntReload = 40;
				}
				else if(*(bpRingtone + 2) == '7')
				{
					gdwDivisorCntReload = 20;
				}
				else if(*(bpRingtone + 2) == '8')
				{
					gdwDivisorCntReload = 10;
				}
				_wOffset = _wOffset + 2; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo y el tercer caracter*/
				bpRingtone = bpRingtone + 2;
			}
			else if(*bpRingtone == 'a')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 1212;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 606;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 303;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 152;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 76;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 38;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 19;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 9;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			else if(*bpRingtone == '#' && *(bpRingtone + 1) == 'a')
			{
				if(*(bpRingtone + 2) == '1')
				{
					gdwDivisorCntReload = 1144;
				}
				else if(*(bpRingtone + 2) == '2')
				{
					gdwDivisorCntReload = 572;
				}
				else if(*(bpRingtone + 2) == '3')
				{
					gdwDivisorCntReload = 286;
				}
				else if(*(bpRingtone + 2) == '4')
				{
					gdwDivisorCntReload = 143;
				}
				else if(*(bpRingtone + 2) == '5')
				{
					gdwDivisorCntReload = 76;
				}
				else if(*(bpRingtone + 2) == '6')
				{
					gdwDivisorCntReload = 36;
				}
				else if(*(bpRingtone + 2) == '7')
				{
					gdwDivisorCntReload = 18;
				}
				else if(*(bpRingtone + 2) == '8')
				{
					gdwDivisorCntReload = 9;
				}
				_wOffset = _wOffset + 2; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo y el tercer caracter*/
				bpRingtone = bpRingtone + 2;
			}
			else if(*bpRingtone == 'b')
			{
				if(*(bpRingtone + 1) == '1')
				{
					gdwDivisorCntReload = 1080;
				}
				else if(*(bpRingtone + 1) == '2')
				{
					gdwDivisorCntReload = 540;
				}
				else if(*(bpRingtone + 1) == '3')
				{
					gdwDivisorCntReload = 270;
				}
				else if(*(bpRingtone + 1) == '4')
				{
					gdwDivisorCntReload = 135;
				}
				else if(*(bpRingtone + 1) == '5')
				{
					gdwDivisorCntReload = 67;
				}
				else if(*(bpRingtone + 1) == '6')
				{
					gdwDivisorCntReload = 34;
				}
				else if(*(bpRingtone + 1) == '7')
				{
					gdwDivisorCntReload = 17;
				}
				else if(*(bpRingtone + 1) == '8')
				{
					gdwDivisorCntReload = 8;
				}
				_wOffset++; /*Se incrementan el offset y la posición de la cadena para saltarse el segundo caracter*/
				bpRingtone++;
			}
			if(!bfnTimeTargetReached(DURACION_CNT)) /*Si la cuenta de duración está vacía*/
			{
				vfnCntLoadAssign(dwDuracionCnt, DURACION_CNT); /*Se escribe el valor de duración elegida*/
			}
			_wOffset++;
		}while(*bpRingtone++ != '\0'); /*Hasta que la cadena llegue a nulo*/
		gflgCountEnable = 0; /*Se apaga la bandera global para indicar que ya se acabó el ringtone y está listo para volver a ser reproducido*/ 
		_wOffset = 0; /*Se reinicia el offset para volver a leer la cadena desde cero*/
	}
}
