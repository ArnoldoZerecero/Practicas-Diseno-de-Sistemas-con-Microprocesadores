/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "derivative.h" /* include peripheral declarations */
#include "FloatFunctions.h"


int main(void)
{
	float fResultadoInt2Float1 = ffnInt2Float(0);
	float fResultadoInt2Float2 = ffnInt2Float(171);
	float fResultadoInt2Float3 = ffnInt2Float(-32768);

	short iResultadoFloat2Int1 = ifnFloat2Int(2147418112); /*INFINITY+*/
	short iResultadoFloat2Int2 = ifnFloat2Int(-956301312);	/*-32768*/
	short iResultadoFloat2Int3 = ifnFloat2Int(-695361234); /*INFINITY-*/
	
	float fResultadoFloatAdd1 = ffnFloatAdd (1190788608, -956695040); /*31999, -31999*/
	float fResultadoFloatAdd2 = ffnFloatAdd (1181376512, 1176256512); /*15000, 10000*/
	float fResultadoFloatAdd3 = ffnFloatAdd (2147418112, 1124532224); /*INFINITY+*/

	float fResultadoFloatSub1 = ffnFloatSub (1190788608,-956695040); /*31999, -31999*/
	float fResultadoFloatSub2 = ffnFloatSub (0, 1176256512); /*0, 10000*/
	float fResultadoFloatSub3 = ffnFloatSub (1181376512, -655360000); /*INFINITY-*/
	
	char bResultadoFloatCmp1 = bfnFloatCmp (0,0);
	char bResultadoFloatCmp2 = bfnFloatCmp (1181376512,1176256512); /*15000, 10000*/
	char bResultadoFloatCmp3 = bfnFloatCmp (1176256512, 1181376512); /*10000, 15000*/
	
	float fResultadoFloatMpy1 = ffnFloatMpy (-973078528, -973078528); /*-8192, -8192*/
	float fResultadoFloatMpy2 = ffnFloatMpy (0, 1176256512); /*0, 10000*/
	float fResultadoFloatMpy3 = ffnFloatMpy (1181376512, -956695040); /*15000, -31999*/
	
	float fResultadoFloatDiv1 = ffnFloatDiv (-973078528, -973078528); /*-8192, -8192*/
	float fResultadoFloatDiv2 = ffnFloatDiv (0, 1176256512); /*0, 10000*/
	float fResultadoFloatDiv3 = ffnFloatDiv (-956695040, 1181376512 ); /*-31999, 15000*/
	
	float fResultadoFloatMod1 = ffnFloatMod (-973078528, -973078528); /*-8192, -8192*/
	float fResultadoFloatMod2 = ffnFloatMod (0, 1176256512); /*0, 10000*/
	float fResultadoFloatMod3 = ffnFloatMod (-956695040, 1181376512 ); /*-31999, 15000*/
	
	return 0;
}
