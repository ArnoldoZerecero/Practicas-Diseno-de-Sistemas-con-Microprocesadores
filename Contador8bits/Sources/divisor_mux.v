`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:39:28 10/19/2017 
// Design Name: 
// Module Name:    divisor_mux 
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
module divisor_mux(
	input iClk,
	input iReset,
	input [2:0] ivSel,
	input iClk2,
	input iClk4,
	input iClk8,
	input iClk16,
	output oSalida
    );
	 
reg r_Q; /*Un solo flip flop de salida*/
reg r_D;

assign oSalida = r_Q;
	
always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
	  r_Q<=0; /*Todos los estados vuelven a cero*/
	end
	else
	begin
	  r_Q<=r_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
	end
end

always  @*
begin
	 if (ivSel == 3'd4) /*Si se eligió clk/16*/
	 begin
		  r_D = iClk16; 
	 end
	 else if (ivSel == 3'd3) /*Si se eligió clk/8*/
	 begin
		  r_D = iClk8;
	 end
	 else if (ivSel == 3'd2) /*Si se eligió clk/4*/
	 begin
		  r_D = iClk4;
	 end
	 else if (ivSel == 3'd1) /*Si se eligió clk/2*/
	 begin
		  r_D = iClk2;
	 end
	 else /*Si se eligió clk normal*/
	 begin
		  r_D = iClk;
	 end
end

endmodule 
