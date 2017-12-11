/*
 * LCD.h
 *
 *   Created on: Oct 27, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef LCD_H_
#define LCD_H_

/*Comandos*/
#define MSB_CLEAR (0xF0)
#define CLEAR_DISPLAY (0x01)
#define FOUR_BIT_TWO_LINES (0x28)
#define DISPLAY_OFF (0x08)
#define CURSOR_ON (0x0E)
#define CURSOR_OFF (0x0C)
#define CURSOR_BLINK (0x0F)
#define SHIFT_DISPLAY_LEFT (0x18)
#define SHIFT_DISPLAY_RIGHT (0x1C)
#define MOVE_CURSOR_RIGHT (0x14)
#define MOVE_CURSOR_LEFT (0x10)
#define FIRST_ROW_BEGIN (0x80)
#define SECOND_ROW_BEGIN (0xC0)
#define CGRAM_ADDRESS (0x40)

#define DATA_SENT 32

/*Configuración inicial*/
#define LCD_16X2_OR_20X2 0 /*Se selecciona el tamaño del LCD. 0: 16X2, 1: 20X2*/

#define PORTA_ENABLE 0 /*Se seleccionan los puertos que se usarán*/
#define PORTB_ENABLE 0
#define PORTC_ENABLE 1
#define PORTD_ENABLE 0
#define PORTE_ENABLE 1

#define RS_PORT_PCR PORTC_PCR1 /*Se asignan los puertos y pines para las conexiones del LCD*/
#define RS_PORT_PDDR GPIOC_PDDR
#define RS_PORT_PDOR GPIOC_PDOR
#define RS_PIN 2

#define ENABLE_PORT_PCR PORTC_PCR2
#define ENABLE_PORT_PDDR GPIOC_PDDR
#define ENABLE_PORT_PDOR GPIOC_PDOR
#define ENABLE_PIN 1 

#define DATA1_PORT_PCR PORTE_PCR20
#define DATA1_PORT_PDDR GPIOE_PDDR
#define DATA1_PORT_PDOR GPIOE_PDOR
#define DATA1_PIN 20

#define DATA2_PORT_PCR PORTE_PCR21
#define DATA2_PORT_PDDR GPIOE_PDDR
#define DATA2_PORT_PDOR GPIOE_PDOR
#define DATA2_PIN 21	

#define DATA3_PORT_PCR PORTE_PCR22
#define DATA3_PORT_PDDR GPIOE_PDDR
#define DATA3_PORT_PDOR GPIOE_PDOR
#define DATA3_PIN 22

#define DATA4_PORT_PCR PORTE_PCR23
#define DATA4_PORT_PDDR GPIOE_PDDR
#define DATA4_PORT_PDOR GPIOE_PDOR
#define DATA4_PIN 23

#define BACKLIGHT_PORT_PCR PORTE_PCR29
#define BACKLIGHT_PORT_PDDR GPIOE_PDDR
#define BACKLIGHT_PORT_PDOR GPIOE_PDOR
#define BACKLIGHT_PIN 29


typedef struct /*Variables de estado*/
{
	unsigned char bEstadoActual;
	unsigned char bEstadoSiguiente;
	unsigned char bEstadoAnterior;
	unsigned char bEstadoError;
}VariablesEstado_t;

VariablesEstado_t tVariablesEstados;

enum /*Lista de contadores que se utilizarán*/
{
	IDLE_STATE,
	DELAY_STATE,
	RS_SET_STATE,
	RS_CLEAR_STATE,
	ENABLE_SET_STATE,
	ENABLE_CLEAR_STATE,
	PREV_DATA_CLEAR_STATE,
	DATA_SEND_STATE,
	MAX_STATES /*Número total de estados*/
};

void vfnLCDGPIOInit(void);

void vfnBacklightOn(void);

void vfnBacklightOff(void);

void vfnLCDUpdate(unsigned char *bpLCDArray);

void vfnSendLCDCommand(unsigned char bCommand);

void vfnSendLCDCharacter(unsigned char bCharacter);

void vfnLCDInitConfig(void);

void vfnDisplayOn(void);

void vfnDisplayOff(void);

void vfnCursorOn(void);

void vfnCursorOff(void);

void vfnCursorBlink(void);

void vfnLCDDriver(void);

void vfnNewCharacter(const unsigned char *bpDibujo,  unsigned char bSize, unsigned char bAddress);

unsigned char bfnLCDBusy(void);

void vfnIdle(void);

void vfnLCDDelay(void);

void vfnRSSet(void);

void vfnRSClear(void);

void vfnEnableSet(void);

void vfnEnableClear(void);

void vfnPrevDataClear(void);

void vfnDataSend(void);

#endif /* LCD_H_ */
