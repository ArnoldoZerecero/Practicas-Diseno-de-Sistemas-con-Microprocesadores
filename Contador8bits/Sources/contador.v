`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    21:56:06 10/09/2017 
// Design Name: 
// Module Name:    contador 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module contador(
	input iClk,
	input iClkE,
	input iReset,
	input [7:0] ivCountLoad, 
	input iSenalCont, 
	output oCompareFlag,
	output [7:0] ovCuenta    
	);
	
reg [7:0] rvCont_Q = 0; /*Flip flop para la salida del contador. El contador comienza valiendo lo que indica el usuario*/
reg [7:0] rvCont_D = 0;

reg r_D = 0; /*Flip flop para la salida de la bandera que se activa cuando la comparación es true*/
reg r_Q = 0;

assign ovCuenta = rvCont_Q;
assign oCompareFlag = r_Q;

always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
		rvCont_Q<=ivCountLoad; /*Se recarga/resetea la cuenta*/
		r_Q<=0;
	end
	else 
	begin
		if (iClkE)
		begin
			rvCont_Q<=rvCont_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
			r_Q<=r_D;
		end
		else
		begin
			rvCont_Q<=rvCont_Q; /*No hay cambios*/
			r_Q<=r_Q;
		end
	end
end

always @*
begin
	if(rvCont_Q == 0) /*Si el contador ya contó lo esperado (se llegó a cero)*/
	begin
		rvCont_D = ivCountLoad; /*Se reinicia la cuenta con el valor asignado por el usuario*/
		r_D = 1'b1; /*Se setea la compare flag*/
	end
	else if (iSenalCont) /*Cada que entre un evento o clk según se definió por el multiplexor*/
	begin
		rvCont_D = rvCont_Q - 1; /*Se cuenta en forma descendente*/
		r_D = 1'b0;
	end
	else
	begin
		rvCont_D = rvCont_Q; /*No hay cambio*/
		r_D = 1'b0; /*Se matiene en cero mientras no sea 0 la cuenta*/
	end
end
endmodule
