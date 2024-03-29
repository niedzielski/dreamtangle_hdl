/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// VERIFIED.
// Created:   ~Friday, June 1, 2007 [Stephen Niedzielski]
// Modified:  Wednesday, October 31, 2007 [Stephen Niedzielski]
module ISP1362Ctrl
(
  // Intermodule lines.
  input         iClk200,
  input         iRead,
  input         iCmd,
  input [15:0]  iD,
  input         iGo,
  output        oDone,
  output [15:0] oQ,

  // ISP1362 lines.
  inout [15:0]  ioD,
  output        oRESET_,
  output [1:0]  oA,
  output        oRD_,
  output        oWR_,
  output        oCS_,
  output        oOTG_DP1,
  output        oOTG_DM1
);

  reg
  _A0,
  _RD_,
  _WR_,
  _CS_;
  initial
  begin
    _A0  = 1'b1;
    _RD_ = 1'b1;
    _WR_ = 1'b1;
    _CS_ = 1'b1;
  end
  assign
  oA[0]= _A0,
  oRD_ = _RD_,
  oWR_ = _WR_,
  oCS_ = _CS_;

  reg _Done;
  initial
    _Done = 1'b1;
  assign oDone = _Done;

  reg [15:0] _Q;
  initial
    _Q = 16'h0000;
  assign oQ = _Q;

  // Enable USB full speed.
  assign oOTG_DP1 = 1'b1;

  // Disable USB low speed.
  assign oOTG_DM1 = 1'b0;
  
  // Disable reset.
  assign oRESET_ = 1'b1;

  // Device controller selected.
  assign oA[1] = 1'b1;

  wire Write = !iRead | iCmd;

  reg _WrEn;
  initial
    _WrEn = 1'b0;

  // Manage use of the bi-directional data bus.
  assign ioD = _WrEn
             ? iD
             : 16'bz;

  reg [77:0] _S;
  initial
  begin
    // Initialize to idle state.
    _S[76:0] = 77'h0;
    _S[77]   = 1'b1;
  end

  always_ff @( posedge iClk200 )
  begin
    // Defaults.
    _S <= _S << 1;

    unique case( 1'b1 )
      |_S[04:00]:
      begin
        // Enable buffer / register access.
        _CS_ <= 1'b0;

        // Command or data mode.
        _A0 <= iCmd;

        // Send a write request.
        _WR_ <= ~Write;
        
        // Send a read request.
        _RD_ <= ~iRead;

        // Owns bus.
        _WrEn <= Write;
      end
      _S[05]:
      begin
        // End write request.
        _WR_ <= 1'b1;
        
        // If read data phase, receive D.
        if( iRead )
          _Q <= ioD;
        
        // If command phase or write data phase, disable buffer / register
        // access.
        if( Write )
          _CS_ <= 1'b1;
      end
      _S[06]:
      begin
        // End read request.
        _RD_ <= 1;

        // Disable buffer / register access (read case).
        _CS_ <= 1;
      end
      |_S[35:07]:
      begin
        // Terminate bus ownership.
        _WrEn <= 1'b0;
      end
      _S[36]:
      begin
        if( !iCmd )
        begin
          // Data mode, skip the wait.
          _S <= 0;
          _S[77] <= 1'b1;

          // Done.
          _Done <= 1'b1;
        end
      end
      |_S[76:37]:
      begin
        // Wait for command to data phase transistion.
      end
      _S[77]:
      begin
        if( iGo )
        begin
          // Jump to the start condition.
          _Done <= 1'b0;
          _S[0] <= iGo;
        end
        else
        begin
          // Done.
          _Done <= 1'b1;

          // Stay idle in this state.
          _S[77] <= !iGo;
        end
      end
    endcase

  end

endmodule
