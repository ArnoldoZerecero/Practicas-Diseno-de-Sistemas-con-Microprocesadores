`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:24:32 10/19/2017 
// Design Name: 
// Module Name:    flancos 
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
module flancos(
 input iClk, 
 input iReset, 
 input iExternalInput,
 output oFlancosP,
 output oFlancosN,
 output oFlancosX
    );
	 
/*3 flip flops de salida*/
reg rP_Q; /*Flancos positivos*/
reg rP_D;

reg rN_Q; /*Flancos negativos*/
reg rN_D;

reg rX_Q; /*Cualquier flanco*/
reg rX_D;

reg rEstado1_Q; /*2 flip flops para comparar el estado de los flancos, para saber cuando hubo una transiciòn*/
reg rEstado1_D;
reg rEstado2_Q;
reg rEstado2_D;
	
assign oFlancosP = rP_Q;
assign oFlancosN = rN_Q;
assign oFlancosX = rX_Q;
	
always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
	  rP_Q<=0; /*Todos los estados vuelven a cero*/
	  rN_Q<=0;
	  rX_Q<=0;
	  rEstado1_Q<=0;
	  rEstado2_Q<=0;
	end
	else
	begin
	  rP_Q<=rP_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
	  rN_Q<=rN_D;
	  rX_Q<=rX_D;
	  rEstado1_Q<=rEstado1_D;
	  rEstado2_Q<=rEstado2_D;
	end
end

always  @*
begin
  rEstado2_D = iExternalInput; 
  rEstado1_D = rEstado2_Q;
  
  rP_D = ~rEstado1_Q & rEstado2_Q; /*Se detectan transiciones de 0 a 1*/ 
  rN_D = ~rEstado2_Q & rEstado1_Q; /*Se detectan transiciones de 1 a 0*/ 
  rX_D = rEstado1_Q ^ rEstado2_Q; /*Se detecta cualquier transición*/  
end
	

endmodule 