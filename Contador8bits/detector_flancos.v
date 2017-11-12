`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:20:56 10/23/2017 
// Design Name: 
// Module Name:    detector_flancos 
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
module detector_flancos(
	input iClk ,
	input iReset,
	input iSenal,
	output oFlanco 
    );
	 
reg r_Q; /*Un solo flip flop de salida*/
reg r_D;

reg rEstado1_Q; /*2 flip flops para comparar el estado de los flancos, para saber cuando hubo una transiciòn*/
reg rEstado1_D;
reg rEstado2_Q;
reg rEstado2_D;

assign oFlanco = r_Q;

always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
	  r_Q<=0; /*Todos los estados vuelven a cero*/
	  rEstado1_Q<=0;
	  rEstado2_Q<=0;
	end
	else
	begin
	  r_Q<=r_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
	  rEstado1_Q<=rEstado1_D;
	  rEstado2_Q<=rEstado2_D;
	end
end

always  @*
begin
  rEstado2_D = iSenal; 
  rEstado1_D = rEstado2_Q;
  r_D = ~rEstado1_Q & rEstado2_Q; /*Se detectan transiciones de 0 a 1*/ 
end

endmodule
