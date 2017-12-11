/*
 * I2C.h
 *
 *  Created on: Dec 2, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef I2C_H_
#define I2C_H_

#include "derivative.h" /* include peripheral declarations */

#endif /* I2C_H_ */

void vfnI2CInitConfig(void);

void vfnI2CPortsInit(void);

void vfnStartCondition(void);

void vfnStopCondition(void);

unsigned char bpfnMemorySearch(void);

unsigned char bfnWriteMode(unsigned char bSlaveAddress, unsigned short wMemoryAddress, unsigned char bSize, unsigned char *bpData);

unsigned char* bpfnReadMode(unsigned char bSlaveAddress, unsigned short wMemoryAddress, unsigned char bSize);

unsigned char bfnBusBusy(void);

void vfnWaitForTranfer(void);

void vfnWaitForWriteCycle(unsigned char bSlaveAddress);

void vfnTransmitData(unsigned char bData);

unsigned char bfnReceiveData(void);
