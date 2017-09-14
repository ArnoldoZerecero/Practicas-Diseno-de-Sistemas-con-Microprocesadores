#include "Funciones.h"

void vfnMemCpy1 (void);
void vfnMemCpy2 (void);
void vfnMemCpy3 (void);

void vfnMemSet1(void);
void vfnMemSet2(void);
void vfnMemSet3(void);

void vfnFindMax1(void);
void vfnFindMax2(void);
void vfnFindMax3(void);

void vfnFindMin1(void);
void vfnFindMin2(void);
void vfnFindMin3(void);

void vfnStrCmp1(void);
void vfnStrCmp2(void);
void vfnStrCmp3(void);

void vfnByteAddress1(void);
void vfnByteAddress2(void);
void vfnByteAddress3(void);

void vfnSort1(void);
void vfnSort2(void);
void vfnSort3(void);

void vfnStrLen1(void);
void vfnStrLen2(void);
void vfnStrLen3(void);

void vfnSprintf1(void);
void vfnSprintf2(void);
void vfnSprintf3(void);


int main(void)
{
	/*3 casos de prueba para cada función*/
	vfnMemCpy1();
	vfnMemCpy2();
	vfnMemCpy3();

	vfnMemSet1();
	vfnMemSet2();
	vfnMemSet3();

	vfnFindMax1();
	vfnFindMax2();
	vfnFindMax3();

	vfnFindMin1();
	vfnFindMin2();
	vfnFindMin3();

	vfnStrCmp1();
	vfnStrCmp2();
	vfnStrCmp3();

	vfnByteAddress1();
	vfnByteAddress2();
	vfnByteAddress3();

	vfnSort1();
	vfnSort2();
	vfnSort3();

	vfnStrLen1();
	vfnStrLen2();
	vfnStrLen3();

	vfnSprintf1();
	vfnSprintf2();
	vfnSprintf3();

	return 0;
}

void vfnMemCpy1 (void)
{
	unsigned char baArregloFuente[10] = {1, 100, 50, 25, 0, 90, 95, 255, 255, 1}; /*Arreglo que contiene los elementos a pasar al arreglo destino*/
	unsigned char baArregloDestino[10]; /*Arreglo no inicializado en donde se copiarán los elementos del arreglo fuente*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/
	unsigned char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	vfnMemCpy (bpApuntadorFuente, bpApuntadorDestino, sizeof(baArregloFuente));
}

void vfnMemCpy2 (void)
{
	unsigned char baArregloFuente[1] = {5}; /*Arreglo que contiene los elementos a pasar al arreglo destino*/
	unsigned char baArregloDestino[1]; /*Arreglo no inicializado en donde se copiarán los elementos del arreglo fuente*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/
	unsigned char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	vfnMemCpy (bpApuntadorFuente, bpApuntadorDestino, sizeof(baArregloFuente));
}

void vfnMemCpy3 (void)
{
	unsigned char baArregloFuente[5] = {'a', 'b', 'c', '-', '.'}; /*Arreglo que contiene los elementos a pasar al arreglo destino*/
	unsigned char baArregloDestino[5]; /*Arreglo no inicializado en donde se copiarán los elementos del arreglo fuente*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/
	unsigned char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	vfnMemCpy (bpApuntadorFuente, bpApuntadorDestino, sizeof(baArregloFuente));
}

void vfnMemSet1(void)
{
	unsigned char baArregloFuente[5] = {'a', 'b', 'c', '-', '.'}; /*Arreglo a llenar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	vfnMemSet(bpApuntadorFuente, 0, sizeof(baArregloFuente));
}

void vfnMemSet2(void)
{
	unsigned char baArregloFuente[255]; /*Arreglo a llenar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	vfnMemSet(bpApuntadorFuente, 'a', sizeof(baArregloFuente));
}

void vfnMemSet3(void)
{
	unsigned char baArregloFuente[1]; /*Arreglo a llenar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	vfnMemSet(bpApuntadorFuente, '?', sizeof(baArregloFuente));
}

void vfnFindMax1(void)
{
	unsigned char bMax; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[5] = {'z', 'm', '/', '-', 'a'}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bMax = bfnFindMax(bpApuntadorFuente, sizeof(baArregloFuente));
	bMax = bMax;
}

void vfnFindMax2(void)
{
	unsigned char bMax; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[10] = {1,1,3,2,2,2,7,200,201,0}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bMax = bfnFindMax(bpApuntadorFuente, sizeof(baArregloFuente));
	bMax = bMax;
}

void vfnFindMax3(void)
{
	unsigned char bMax; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[1] = {3}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bMax = bfnFindMax(bpApuntadorFuente, sizeof(baArregloFuente));
	bMax = bMax;
}

void vfnFindMin1(void)
{
	unsigned char bMin; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[5] = {'z', 'm', '/', '-', 'a'}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bMin = bfnFindMin(bpApuntadorFuente, sizeof(baArregloFuente));
	bMin = bMin;
}

void vfnFindMin2(void)
{
	unsigned char bMin; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[10] = {1,1,3,2,2,2,7,200,201,0}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bMin = bfnFindMin(bpApuntadorFuente, sizeof(baArregloFuente));
	bMin = bMin;
}

void vfnFindMin3(void)
{
	unsigned char bMin; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[1] = {3}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bMin = bfnFindMin(bpApuntadorFuente, sizeof(baArregloFuente));
	bMin = bMin;
}

void vfnStrCmp1(void)
{
	unsigned char bResultado; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[10] = {1, 100, 50, 25, 0, 90, 95, 255, 255, 1}; /*Arreglo a comparar*/
	unsigned char baArregloDestino[10] = {0, 100, 50, 25, 0, 90, 95, 255, 255, 1}; /*Arreglo a comparar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/
	unsigned char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	bResultado = bfnStrCmp (bpApuntadorFuente, bpApuntadorDestino, sizeof(baArregloFuente));
	bResultado = bResultado;
}

void vfnStrCmp2(void)
{
	unsigned char bResultado; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[1] = {0}; /*Arreglo a comparar*/
	unsigned char baArregloDestino[1] = {1}; /*Arreglo a comparar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/
	unsigned char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	bResultado = bfnStrCmp (bpApuntadorFuente, bpApuntadorDestino, sizeof(baArregloFuente));
	bResultado = bResultado;
}

void vfnStrCmp3(void)
{
	unsigned char bResultado; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[5] = {'A', 'B', 'c', 'd', 'e'}; /*Arreglo a comparar*/
	unsigned char baArregloDestino[5] = {'A', 'B', 'c', 'd', 'e'}; /*Arreglo a comparar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/
	unsigned char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	bResultado = bfnStrCmp (bpApuntadorFuente, bpApuntadorDestino, sizeof(baArregloFuente));
	bResultado = bResultado;
}

void vfnByteAddress1(void)
{
	unsigned char *bpResultingAddress; /*Dirección para la dirección resultante retornado de la función*/
	unsigned char baArregloFuente[5] = {'a', 'b', 'c', '-', '.'}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bpResultingAddress = bpfnByteAddress(bpApuntadorFuente, 0, sizeof(baArregloFuente));
	bpResultingAddress = bpResultingAddress;
}

void vfnByteAddress2(void)
{
	unsigned char *bpResultingAddress; /*Apuntador para la dirección resultante retornado de la función*/
	unsigned char baArregloFuente[8] = {'z', 3, 'a', 'a', 200, 'a', 0, 0}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bpResultingAddress = bpfnByteAddress(bpApuntadorFuente, 'a', sizeof(baArregloFuente));
	bpResultingAddress = bpResultingAddress;
}

void vfnByteAddress3(void)
{
	unsigned char *bpResultingAddress; /*Apuntador para la dirección resultante retornado de la función*/
	unsigned char baArregloFuente[1] = {0}; /*Arreglo a buscar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	bpResultingAddress = bpfnByteAddress(bpApuntadorFuente, 20, sizeof(baArregloFuente));
	bpResultingAddress = bpResultingAddress;
}

void vfnSort1(void)
{
	unsigned char baArregloFuente[10] = {0, 3, 255, 0, 2, 5, 132, 'm', '.', 'T'}; /*Arreglo a ordenar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	vfnSort(bpApuntadorFuente,  sizeof(baArregloFuente));
}

void vfnSort2(void)
{
	unsigned char baArregloFuente[5] = {1, 1, 1, 0, 1}; /*Arreglo a ordenar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	vfnSort(bpApuntadorFuente,  sizeof(baArregloFuente));
}

void vfnSort3(void)
{
	unsigned char baArregloFuente[1] = {5}; /*Arreglo a ordenar*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	vfnSort(bpApuntadorFuente,  sizeof(baArregloFuente));
}

void vfnStrLen1(void)
{
	unsigned short wLongitud; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[] = "A"; /*Cadena a medir*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	wLongitud = wfnStrLen(bpApuntadorFuente);
	wLongitud = wLongitud;
}

void vfnStrLen2(void)
{
	unsigned short wLongitud; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[] = "Microcontroladores"; /*Cadena a medir*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	wLongitud = wfnStrLen(bpApuntadorFuente);
	wLongitud = wLongitud;
}

void vfnStrLen3(void)
{
	unsigned short wLongitud; /*Variable para el resultado retornado de la función*/
	unsigned char baArregloFuente[]= "Parangaricutirimicuaro"; /*Cadena a medir*/
	unsigned char *bpApuntadorFuente = &baArregloFuente[0]; /*Apuntador para el arreglo fuente*/

	wLongitud = wfnStrLen(bpApuntadorFuente);
	wLongitud = wLongitud;
}

void vfnSprintf1(void)
{
	unsigned char bVariableDecimal = 10; /*Argumento decimal*/
	void *vpaExtraArguments[] = {&bVariableDecimal, "blancos"}; /*Arreglo de apuntadores*/
	unsigned short wLongitud; /*Variable para el resultado retornado de la función*/
	char baCadenaFormato[] = "Tengo %d gatos %s"; /*Cadena a imprimir*/
	char baArregloDestino[300]; /*Arreglo para almacenar la cadena*/
	char *bpApuntadorFormato = &baCadenaFormato[0]; /*Apuntador para la cadena a imprimir*/
	char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	wLongitud = wfnSprintf (bpApuntadorDestino, bpApuntadorFormato, vpaExtraArguments);
	wLongitud = wLongitud;
}

void vfnSprintf2(void)
{
	unsigned char bVariableDecimal = 255; /*Argumento decimal*/
	void *vpaExtraArguments[] = {&bVariableDecimal, &bVariableDecimal, &bVariableDecimal}; /*Arreglo de apuntadores*/
	unsigned short wLongitud; /*Variable para el resultado retornado de la función*/
	char baCadenaFormato[] = "%d en decimal es %x en hexadecimal y %b en binario"; /*Cadena a imprimir*/
	char baArregloDestino[300]; /*Arreglo para almacenar la cadena*/
	char *bpApuntadorFormato = &baCadenaFormato[0]; /*Apuntador para la cadena a imprimir*/
	char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	wLongitud = wfnSprintf (bpApuntadorDestino, bpApuntadorFormato, vpaExtraArguments);
	wLongitud = wLongitud;
}

void vfnSprintf3(void)
{
	void *vpaExtraArguments[] = {"D", "D", "equivale", "D"}; /*Arreglo de apuntadores*/
	unsigned short wLongitud; /*Variable para el resultado retornado de la función*/
	char baCadenaFormato[] = "%c es igual a %x hexadecimal, lo cual %s a %b binario"; /*Cadena a imprimir*/
	char baArregloDestino[300]; /*Arreglo para almacenar la cadena*/
	char *bpApuntadorFormato = &baCadenaFormato[0]; /*Apuntador para la cadena a imprimir*/
	char *bpApuntadorDestino = &baArregloDestino[0]; /*Apuntador para el arreglo destino*/

	wLongitud = wfnSprintf (bpApuntadorDestino, bpApuntadorFormato, vpaExtraArguments);
	wLongitud = wLongitud;
}


