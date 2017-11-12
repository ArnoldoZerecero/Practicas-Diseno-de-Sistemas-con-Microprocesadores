`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    22:17:52 10/09/2017 
// Design Name: 
// Module Name:    input_mux 
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
module input_mux(
 input iClk, 
 input iReset, 
 input [2:0] ivSel, 
 input iFlancosP,
 input iFlancosN,
 input iFlancosX,
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
	 if (ivSel == 3'd4) /*Si se eligieron flancos positivos*/
	 begin
		  r_D = iFlancosP; 
	 end
	 else if (ivSel == 3'd3) /*Si se eligieron flancos negativos*/
	 begin
		  r_D = iFlancosN;
	 end
	 else if (ivSel == 3'd2) /*Si se eligió cualquier flanco*/
	 begin
		  r_D = iFlancosX;
	 end
	 else if (ivSel == 3'd1) /*Si se eligió el clk como entrada*/
	 begin
		  r_D = iClk;
	 end
	 else /*Si se eligió detener el contador (que este no tenga entrada)*/
	 begin
		  r_D = 0;
	 end
end

endmodule 