/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

/*Link to video demonstration: https://photos.app.goo.gl/Jg1hbGo2Ihwpz46j2*/

#include "derivative.h" /* include peripheral declarations */
#include "LCD.h"
#include "MISCELANEO.h"
#include "ButtonDriver.h"
#include "LedDriver.h"
#include "PIT.h"
#include <stdlib.h>

#define ACTION_BUTTON 0
#define PAUSE_BUTTON 1
#define RED_LED 1

void vfnPitCallback(void); /*Funci�n a la que accede la interrupci�n del PIT cada que su cuenta base finaliza*/
void vfnMoveDog(void); /*Se accede a esta funci�n al presionar el bot�n de acci�n*/
void vfnPauseState(void); /*Se accede a esta funci�n mientras el juego est� en pausa*/
void vfnLifeLoss(void); /*Se accede a esta funci�n cuando se choca contra una serpiente*/
void vfnScore(void); /*Se accede a esta funci�n cuando se atrapa un hueso*/
void vfnGameStart(void); /*Interfaz de comienzo de juego*/
void vfnGameOver(void); /*Interfaz de fin del juego*/

volatile unsigned char gbSuperiorSpeedCounter = 0; /*Velocidad a la cual se recorrer�n los obst�culos del juego por la parte superior de la pantalla*/
volatile unsigned char gbInferiorSpeedCounter = 0; /*Velocidad a la cual se recorrer�n los obst�culos del juego por la parte inferior de la pantalla*/
volatile unsigned short gwScoreCounter = 0; /*Puntaje*/
volatile unsigned char gbLevel = 1; /*Nivel actual*/
volatile unsigned char gbSpeedMode = 12; /*Velocidad de movimiento de obst�culos*/

#if !LCD_16X2_OR_20X2
unsigned char gbaLCDSpaces[32] = {6,'3','L','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S','0','0','0',4,5,' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; /*Arreglo que se llenar� seg�n lo que se quiera pintar en cada uno de los 32 espacios del LCD*/
#else
unsigned char gbaLCDSpaces[40] = {6,'3','L','1',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S','0','0','0',4,5,' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}; /*Arreglo que se llenar� seg�n lo que se quiera pintar en cada uno de los 32 espacios del LCD*/
#endif

const unsigned char kbaDogOnGround1[8] =  /*Arreglos para crear nuevos caracterese en CGRAM*/
{
		0b00000,
		0b00000,
		0b00000,
		0b00000,
		0b01000,
		0b00111,
		0b00111,
		0b00100
};

const unsigned char kbaDogOnGround2[8] = 
{
		0b00000,
		0b00000,
		0b01100,
		0b01110,
		0b01110,
		0b11000,
		0b11000,
		0b01000
};

const unsigned char kbaFlyingDog1[8] = 
{
		0b00000,
		0b01100,
		0b00110,
		0b00011,
		0b01001,
		0b00111,
		0b11111,
		0b00000
};

const unsigned char kbaFlyingDog2[8] = 
{
		0b00000,
		0b00000,
		0b01100,
		0b01110,
		0b01110,
		0b11000,
		0b11110,
		0b00000
};

const unsigned char kbaBone[8] = 
{
		0b01110,
		0b10101,
		0b10001,
		0b01010,
		0b01010,
		0b10001,
		0b10101,
		0b01110
};

const unsigned char kbaSnake[8] = 
{
		0b11000,
		0b11100,
		0b00110,
		0b00010,
		0b01110,
		0b11000,
		0b10010,
		0b11110
};

const unsigned char kbaHeart[8] = 
{
		0b00000,
		0b01010,
		0b10101,
		0b10001,
		0b01010,
		0b00100,
		0b00000,
		0b00000
};


int main(void)
{	
	#if !LCD_16X2_OR_20X2
	static unsigned char _bSuperiorMoveIndex = 15; /*Indice para desplazar obstaculos de derecha a izquierda por la parte superior de la pantalla*/
	static unsigned char _bInferiorMoveIndex = 31; /*Indice para desplazar obstaculos de derecha a izquierda por la parte inferior de la pantalla*/
	#else
	static unsigned char _bSuperiorMoveIndex = 19; /*Indice para desplazar obstaculos de derecha a izquierda por la parte superior de la pantalla*/
	static unsigned char _bInferiorMoveIndex = 39; /*Indice para desplazar obstaculos de derecha a izquierda por la parte inferior de la pantalla*/
	#endif
	unsigned char bSuperiorRandomSprite = rand() % 2; /*Variable aleatoria que elige entre el hueso o la serpiente de la parte superior de la pantalla*/
	unsigned char bSuperiorRandomSpeed = rand() % 4; /*Variable aleatoria que altera ligeramente la velocidad de desplazamiento del obst�culo de la parte superior de la pantalla*/
	unsigned char bInferiorRandomSprite = rand() % 2; /*Variable aleatoria que elige entre el hueso o la serpiente de la parte inferior de la pantalla*/
	unsigned char bInferiorRandomSpeed = rand() % 4; /*Variable aleatoria que altera ligeramente la velocidad de desplazamiento del obst�culo de la parte inferior de la pantalla*/

	vfnButtonInit(); /*Inicializaci�n de botones*/
	vfnLCDGPIOInit();	/*Inicializaci�n de puertos de LCD*/
	vfnLedInit(); /*Inicializaci�n de LEDs*/
	vfnPitInit(TARGET_TIME_50MS,&vfnPitCallback); /*Inicializaci�n del PIT*/
	vfnPitStart(); /*Comienza el contador del PIT*/
	vfnNewCharacter(kbaBone, sizeof(kbaBone), 0); /*Se guardan en CGRAM los nuevos caracteres que se utilizar�n para el juego*/
	vfnNewCharacter(kbaSnake, sizeof(kbaSnake), 1);
	vfnNewCharacter(kbaFlyingDog1, sizeof(kbaFlyingDog1), 2);
	vfnNewCharacter(kbaFlyingDog2, sizeof(kbaFlyingDog2),  3);
	vfnNewCharacter(kbaDogOnGround1, sizeof(kbaDogOnGround1), 4);
	vfnNewCharacter(kbaDogOnGround2, sizeof(kbaDogOnGround2),  5);
	vfnNewCharacter(kbaHeart, sizeof(kbaHeart),  6);
	vfnLCDInitConfig(); /*Se inicializa el LCD en modo 4 bits y se limpia la pantalla*/
	vfnBacklightOn(); /*Se enciende el backlight*/
	vfnGameStart(); /*Comienza el juego*/
	gbSuperiorSpeedCounter = 0; /*La cuenta del PIT comienza en 0*/
	gbInferiorSpeedCounter = 0; /*La cuenta del PIT comienza en 0*/
	for(;;)
	{
		vfnLCDDriver(); /*Se accede al estado elegido*/
		vfnButtonDriver(); /*Se revisan los botones*/
		if(bfnButtonClick(ACTION_BUTTON)) /*Si se presiona el bot�n de acci�n*/
		{
			vfnMoveDog();
		}

		if(bfnButtonClick(PAUSE_BUTTON)) /*Si se presiona el bot�n de pausa*/
		{
			vfnPauseState();
		}

		while(bSuperiorRandomSpeed == bInferiorRandomSpeed) /*Si ambas velocidades son iguales*/
		{
			bSuperiorRandomSpeed = rand() % 4; /*Se asignan nuevas velocidades aleatorias, para evitar crear barreras de obst�culos imposibles de esquivar*/
			bInferiorRandomSpeed = rand() % 4; 
		}

		/*Fila superior*/
		if(gbSuperiorSpeedCounter == gbSpeedMode + bSuperiorRandomSpeed) /*Cada cierto tiempo, el obst�culo se mover� hacia la izquierda por la parte superior de la pantalla*/
		{
			if(_bSuperiorMoveIndex != 6) /*Si no se ha llegado al l�mite izquierdo*/
			{
				gbaLCDSpaces[_bSuperiorMoveIndex] = ' '; /*Se borra el espacio anterior*/
				gbaLCDSpaces[_bSuperiorMoveIndex - 1] = bSuperiorRandomSprite; /*En el espacio siguiente se pinta un obst�culo aleatorio*/
				_bSuperiorMoveIndex--;
			}
			else  /*Al llegar al l�mite izquierdo*/
			{
				if((gbaLCDSpaces[_bSuperiorMoveIndex] == 1 && gbaLCDSpaces[_bSuperiorMoveIndex - 1] != ' ')) /*Si se choca con una serpiente*/
				{
					vfnLifeLoss(); 
					gbaLCDSpaces[_bInferiorMoveIndex] = ' '; /*El obst�culo inferior volver� a iniciar a moverse desde la derecha*/
					#if !LCD_16X2_OR_20X2
					_bInferiorMoveIndex = 31; 
					#else
					_bInferiorMoveIndex = 39; 
					#endif
				}
				else if(gbaLCDSpaces[_bSuperiorMoveIndex] == 0 && gbaLCDSpaces[_bSuperiorMoveIndex - 1] != ' ') /*Si se atrapa un hueso*/
				{
					vfnScore();
				}
				gbaLCDSpaces[_bSuperiorMoveIndex] = ' '; /*Se borra el rastro del obst�culo*/
				#if !LCD_16X2_OR_20X2
				_bSuperiorMoveIndex = 15; /*El obst�culo superior volver� a iniciar a moverse desde la derecha*/
				#else
				_bSuperiorMoveIndex = 19; /*El obst�culo superior volver� a iniciar a moverse desde la derecha*/
				#endif
				bSuperiorRandomSprite = rand() % 2; /*Se asigna un nuevo obst�culo aleatorio*/
				bSuperiorRandomSpeed = rand() % 4; /*Se asigna una nueva velocidad aleatoria*/
			}
			vfnLCDUpdate(gbaLCDSpaces); /*Se actualiza la pantalla*/
			gbSuperiorSpeedCounter = 0; /*Se reinicia la cuenta del PIT*/
		}

		/*Fila inferior*/
		if(gbInferiorSpeedCounter == gbSpeedMode + bInferiorRandomSpeed) /*Cada cierto tiempo, el obst�culo se mover� hacia la izquierda por la parte inferior de la pantalla*/
		{
			#if !LCD_16X2_OR_20X2
			if(_bInferiorMoveIndex != 22) /*Si no se ha llegado al l�mite izquierdo*/
			#else
			if(_bInferiorMoveIndex != 26) /*Si no se ha llegado al l�mite izquierdo*/
			#endif
			{
				gbaLCDSpaces[_bInferiorMoveIndex] = ' '; /*Se borra el espacio anterior*/
				gbaLCDSpaces[_bInferiorMoveIndex - 1] = bInferiorRandomSprite; /*En el espacio siguiente se pinta un obst�culo aleatorio*/
				_bInferiorMoveIndex--;
			}
			else  /*Al llegar al l�mite izquierdo*/
			{
				if((gbaLCDSpaces[_bInferiorMoveIndex] == 1 && gbaLCDSpaces[_bInferiorMoveIndex - 1] != ' ')) /*Si se choca con una serpiente*/
				{
					vfnLifeLoss();
					gbaLCDSpaces[_bSuperiorMoveIndex] = ' '; /*El obst�culo superior volver� a iniciar a moverse desde la derecha*/
					#if !LCD_16X2_OR_20X2
					_bSuperiorMoveIndex = 15;
					#else
					_bSuperiorMoveIndex = 19;
					#endif
				}
				else if(gbaLCDSpaces[_bInferiorMoveIndex] == 0 && gbaLCDSpaces[_bInferiorMoveIndex - 1] != ' ') /*Si se atrapa un hueso*/
				{
					vfnScore();
				}
				gbaLCDSpaces[_bInferiorMoveIndex] = ' '; /*Se borra el rastro del obst�culo*/
				#if !LCD_16X2_OR_20X2
				_bInferiorMoveIndex = 31; /*El obst�culo volver� a iniciar a moverse desde la derecha*/
				#else
				_bInferiorMoveIndex = 39; /*El obst�culo volver� a iniciar a moverse desde la derecha*/
				#endif
				bInferiorRandomSprite = rand() % 2; /*Se asigna un nuevo obst�culo aleatorio*/
				bInferiorRandomSpeed = rand() % 4; /*Se asigna una nueva velocidad aleatoria*/
			}
			vfnLCDUpdate(gbaLCDSpaces); /*Se actualiza la pantalla*/
			gbInferiorSpeedCounter = 0; /*Se reinicia la cuenta del PIT*/
		}
	}

}

void vfnPitCallback(void)
{
	gbSuperiorSpeedCounter++;
	gbInferiorSpeedCounter++;
}

void vfnMoveDog(void)
{
	if(gbaLCDSpaces[5] == ' ') /*Si el perro no se encontraba en la parte superior*/
	{
		gbaLCDSpaces[4] = 2; /*Se pinta al perro en la parte superior y se borra de la parte inferior*/
		gbaLCDSpaces[5] = 3;
		#if !LCD_16X2_OR_20X2
		gbaLCDSpaces[20] = ' ';
		gbaLCDSpaces[21] = ' ';
		#else
		gbaLCDSpaces[24] = ' ';
		gbaLCDSpaces[25] = ' ';
		#endif
	}
	else
	{
		gbaLCDSpaces[4] = ' '; /*Se pinta al perro en la parte inferior y se borra de la parte superior*/
		gbaLCDSpaces[5] = ' ';
		#if !LCD_16X2_OR_20X2
		gbaLCDSpaces[20] = 4;
		gbaLCDSpaces[21] = 5;
		#else
		gbaLCDSpaces[24] = 4;
		gbaLCDSpaces[25] = 5;
		#endif
	}
	vfnLCDUpdate(gbaLCDSpaces); /*Se actualiza la pantalla*/
}

void vfnPauseState(void)
{
	unsigned char flgPauseState = 1; /*Bandera para saber si el juego est� pausado o no*/
	static unsigned char _bSuperiorSpeedSave = 0; /*Variable temporal para mantener el mismo valor de la cuenta global de velocidad superior del PIT al salir de la pausa*/
	static unsigned char _bInferiorSpeedSave = 0; /*Variable temporal para mantener el mismo valor de la cuenta global de velocidad superior del PIT al salir de la pausa*/

	_bSuperiorSpeedSave = gbSuperiorSpeedCounter; /*Se almacenan los valores de la velocidad en las variables temporales*/
	_bInferiorSpeedSave = gbInferiorSpeedCounter; 
	while(flgPauseState) /*Se saldr� del modo de pausa el volver a presionar el bot�n*/
	{
		vfnButtonDriver();
		vfnLedOn(RED_LED);
		if(bfnButtonClick(PAUSE_BUTTON))
		{
			vfnLedOff(RED_LED);
			flgPauseState = 0;
		}
	}
	gbSuperiorSpeedCounter = _bSuperiorSpeedSave; /*Se reanudan las cuentas del PIT*/
	gbInferiorSpeedCounter = _bInferiorSpeedSave; 
}

void vfnLifeLoss(void)
{
	static unsigned char _bLifeCounter = 3; /*N�mero de vidas restantes*/
	_bLifeCounter--; /*Se pierde una vida*/
	vfnBacklightOff(); /*La pantalla parpadea*/
	vfnDelay(500000);
	vfnBacklightOn();
	vfnDelay(500000);
	vfnBacklightOff();
	vfnDelay(500000);
	vfnBacklightOn();
	gbaLCDSpaces[1] = _bLifeCounter + 48; /*Se pinta el n�mero de vidas en la pantalla*/
	if(!_bLifeCounter) /*Si se terminan las vidas*/
	{
		vfnGameOver(); /*Se accede a la interfaz de fin del juego*/
		gbLevel = 1; /*Se reinician los valores para volver a jugar*/
		gbSpeedMode = 12;
		_bLifeCounter = 3;
		gwScoreCounter = 0;
		gbaLCDSpaces[1] = _bLifeCounter + 48; /*Se pinta el n�mero de vidas inicial la pantalla*/
		gbaLCDSpaces[3] = gbLevel + 48; /*Se pinta el nivel inicial en pantalla*/
		#if !LCD_16X2_OR_20X2
		gbaLCDSpaces[17] = CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwScoreCounter)) + 48; /*Se pinta el puntaje inicial*/
		gbaLCDSpaces[18] = CLEAR_ALL_BUT_TENS(wfnBCD(gwScoreCounter)) + 48;
		gbaLCDSpaces[19] = CLEAR_ALL_BUT_UNITS(wfnBCD(gwScoreCounter)) + 48;
		#else
		gbaLCDSpaces[21] = CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwScoreCounter)) + 48; /*Se pinta el puntaje inicial*/
		gbaLCDSpaces[22] = CLEAR_ALL_BUT_TENS(wfnBCD(gwScoreCounter)) + 48;
		gbaLCDSpaces[23] = CLEAR_ALL_BUT_UNITS(wfnBCD(gwScoreCounter)) + 48;
		#endif
	}
	gbSuperiorSpeedCounter = 0; /*Se reinician las cuentas del PIT para evitar desfasamientos con los tiempos*/
	gbInferiorSpeedCounter = 0;
}

void vfnScore(void)
{
	gwScoreCounter++; /*Se incrementa el puntaje*/
	
	/*Se pinta el puntaje actual*/
	#if !LCD_16X2_OR_20X2
	gbaLCDSpaces[17] = CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwScoreCounter)) + 48;
	gbaLCDSpaces[18] = CLEAR_ALL_BUT_TENS(wfnBCD(gwScoreCounter)) + 48;
	gbaLCDSpaces[19] = CLEAR_ALL_BUT_UNITS(wfnBCD(gwScoreCounter)) + 48;
	#else
	gbaLCDSpaces[21] = CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwScoreCounter)) + 48;
	gbaLCDSpaces[22] = CLEAR_ALL_BUT_TENS(wfnBCD(gwScoreCounter)) + 48;
	gbaLCDSpaces[23] = CLEAR_ALL_BUT_UNITS(wfnBCD(gwScoreCounter)) + 48;
	#endif

	if(gwScoreCounter == 5) /*Cada 5 puntos se sube de nivel y la velocidad incrementa*/
	{
		gbLevel = 2;
		gbSpeedMode = 7;
		gbSuperiorSpeedCounter = 0; /*Se reinician las cuentas del PIT para evitar desfasamientos con los tiempos*/
		gbInferiorSpeedCounter = 0;
	}
	else if (gwScoreCounter == 10)
	{
		gbLevel = 3;
		gbSpeedMode = 3;
		gbSuperiorSpeedCounter = 0; /*Se reinician las cuentas del PIT para evitar desfasamientos con los tiempos*/
		gbInferiorSpeedCounter = 0;
	}
	gbaLCDSpaces[3] = gbLevel + 48; /*Se pinta el nivel actual en pantalla*/
}

void vfnGameStart(void)
{
	unsigned char gwUserTimeSeed = 0; /*Semilla inicial para la generaci�n de n�meros aleatorios. Depende del tiempo que tarda el usuario en presionar alg�n bot�n para iniciar el juego*/
	#if !LCD_16X2_OR_20X2
	const unsigned char baGameStartScreen[32] = {'C','A','T','C','H',' ',0,' ','D','O','D','G','E',' ',1,' ','P','R','E','S','S',' ','A','N','Y',' ','B','U','T','T','O','N'}; /*Arreglo con el mensaje de comienzo de juego*/
	#else
	const unsigned char baGameStartScreen[40] = {'C','A','T','C','H',' ',0,' ','D','O','D','G','E',' ',1,' ',' ',' ',' ',' ','P','R','E','S','S',' ','A','N','Y',' ','B','U','T','T','O','N',' ',' ',' ',' '}; /*Arreglo con el mensaje de comienzo de juego*/
	#endif
	while(!bfnButtonClick(ACTION_BUTTON) && !bfnButtonClick(PAUSE_BUTTON)) /*Mientras no se presione alg�n bot�n para comenzar el juego*/
	{
		gwUserTimeSeed++; /*Se incrementa la cuenta para la semilla inicial*/
		vfnButtonDriver(); /*Se revisan los botones*/
		vfnLCDUpdate((unsigned char *)baGameStartScreen); /*Se actualiza la pantalla con el mensaje de comienzo de juego*/
	}
	srand(gwUserTimeSeed); /*Se asigna la semilla inicial con el tiempo que tard� el usuario en iniciar el juego*/
}


void vfnGameOver(void)
{
	#if !LCD_16X2_OR_20X2
	const unsigned char baGameOverScreen[32] = {' ',' ',' ','G','A','M','E',' ','O','V','E','R',' ',' ',' ',' ',' ',' ',' ','S','C','O','R','E',':',' ',CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwScoreCounter)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(gwScoreCounter)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(gwScoreCounter)) + 48,' ',' ',' '}; /*Arreglo con el mensaje de fin del juego*/
	#else
	const unsigned char baGameOverScreen[40] = {' ',' ',' ','G','A','M','E',' ','O','V','E','R',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S','C','O','R','E',':',' ',CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwScoreCounter)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(gwScoreCounter)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(gwScoreCounter)) + 48,' ',' ',' ',' ',' ',' ',' '}; /*Arreglo con el mensaje de fin del juego*/
	#endif
	while(!bfnButtonClick(ACTION_BUTTON) && !bfnButtonClick(PAUSE_BUTTON)) /*Mientras no se presione alg�n bot�n para reiniciar el juego*/
	{
		vfnButtonDriver(); /*Se revisan los botones*/
		vfnLCDUpdate((unsigned char *)baGameOverScreen); /*Se actualiza la pantalla con el mensaje de juego terminado*/
	}
	vfnGameStart(); /*Al abandonar esta interfaz, se accede a la interfaz de inicio del juego*/
}


