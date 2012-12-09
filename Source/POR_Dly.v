/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Created:   Tuesday, November 20, 2007 [Stephen Niedzielski]
// Modified:  Tuesday, November 20, 2007 [Stephen Niedzielski]
module POR_Dly
(
  input iClk27,
  input iClk100,
  output oDone
);

  reg [15:0] _Cnt;
  initial _Cnt = 16'd0;
  
  always_ff @( posedge iClk27 )
    if( _Cnt < 30_000 )
      _Cnt <= _Cnt + 1'd1;
  
  reg
  _DoneA,
  _DoneB,
  _DoneC,
  _Done;
  initial
  begin
    _DoneA = 1'b0;
    _DoneB = 1'b0;
    _DoneC = 1'b0;
    _Done  = 1'b0;
  end

  always_ff @( posedge iClk100 )
  begin
    _DoneA <= _Cnt >= 30_000;
    _DoneB <= _DoneA;
    _DoneC <= _DoneB;
    _Done  <= _DoneC;
  end

  assign oDone = _Done;

endmodule
