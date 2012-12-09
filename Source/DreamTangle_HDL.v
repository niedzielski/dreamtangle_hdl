/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Topmost synthesis model.
// Created:   Tuesday, October 30, 2007 [Stephen Niedzielski]
// Modified:  Tuesday, October 30, 2007 [Stephen Niedzielski]
module DreamTangle_HDL
(
  // Clocks.
  input iClk27,
  input iClk50,

  // LEDs.
  output [17:0] oLEDR,
//  output [08:0] oLEDG,
  // Buttons amd switches.
  input [17:0]  iSwitch,
  input [03:0]  iButton_,

  // Hex display.
  output [06:0] oHex7,
  output [06:0] oHex6,
  output [06:0] oHex5,
  output [06:0] oHex4,
  output [06:0] oHex3,
  output [06:0] oHex2,
  output [06:0] oHex1,
  output [06:0] oHex0,

  // USB ISP1362.
  input           iUSB_INT1,
  input           iUSB_INT2,
  input           iUSB_DACK1_,
  input           iUSB_DACK2_,
  inout   [15:0]  ioUSB_D,
  output          oUSB_OTG_DP1,
  output          oUSB_OTG_DM1,
  output  [01:0]  oUSB_A,
  output          oUSB_RD_,
  output          oUSB_WR_,
  output          oUSB_CS_,
  output          oUSB_RESET_,
  output          oUSB_DREQ1,
  output          oUSB_DREQ2,
/*
  // General purpose IO.
  inout [35:0]  ioGPIO1,
  inout [35:0]  ioGPIO0,

  // SRAM.
  output [17:00]  oSRAM_A,
  inout  [15:00]  ioSRAM_IO,
  output          oSRAM_CE_,
  output          oSRAM_WE_,
  output          oSRAM_LB_,
  output          oSRAM_UB_,
  output          oSRAM_OE_,
*/
  // SDRAM.
  inout [15:0]  ioSDRAM_DQ,
  output [11:0] oSDRAM_A,
  output        oSDRAM_LDQM,
  output        oSDRAM_DQM,
  output        oSDRAM_WE_,
  output        oSDRAM_CAS_,
  output        oSDRAM_RAS_,
  output        oSDRAM_CS_,
  output [1:0]  oSDRAM_BA_,
  output        oSDRAM_CLK,
  output        oSDRAM_CKE,

  // I2C.
  output  oI2C_SCLK,
  inout   ioI2C_SDAT,

  // VGA ADV7123.
  output        oVGA_CLK,
  output        oVGA_HS,  // Connected to display HSYNC.
  output        oVGA_VS,  // Connected to display VSYNC.
  output        oVGA_BLANK,
  output        oVGA_SYNC,
  output [29:0] oVGA_RGB,

  // TV Decoder ADV7181B.
  input [7:0] iTD_DATA,   // Connects to P[8:15].
  input       iTD_HS,
  input       iTD_VS,
  input       iTD_CLK,
  output      oTD_RESET
);

  wire
  Clk100,
  Clk200;

  reg [8 * 4 - 1: 0] _SSHLEDMDCtrlD;
  initial _SSHLEDMDCtrlD = 32'h12345678;
  wire [8 * 7 - 1: 0] SSHLEDMDCtrlQ;

  wire VideoFound;
  wire VideoWrEn;
  wire [29:0] VGA_RGB;
  wire [10:0] VideoX;
  wire [10:0] VideoY;

  // Generate the system clocks.
  PLL_Sys
  PLL_Sys0
  (
    .inclk0( iClk50 ),
    .c0( Clk100 ),
    .c1( Clk200 )
  );

  // Debug.
  assign { oHex7,
           oHex6,
           oHex5,
           oHex4,
           oHex3,
           oHex2,
           oHex1,
           oHex0 } = SSHLEDMDCtrlQ;
  generate
    genvar gCnt;
    for( gCnt = 0; gCnt < 8; gCnt = gCnt + 1 )
    begin: gSSHLEDMDCtrl
      SSHLEDMDCtrl Digit
      (
        .iBCD( _SSHLEDMDCtrlD[gCnt * 4 +: 4] ), // Get number to display in four bit
                                                // widths (Start +: width).
        .oMatrix( SSHLEDMDCtrlQ[gCnt * 7 +: 7] ) // Get matrix in seven bit widths.
      );
    end
  endgenerate 

  wire POR_DlyDone;
  POR_Dly
  POR_Dly0
  (
    .iClk27( iClk27 ),
    .iClk100( Clk100 ),
    .oDone( POR_DlyDone )
  );

  
  Video Video0
  (
    .iClk27( iClk27 ),
    .iClk50( iClk50 ),

    .iRst( iButton_[0] ),

    .ioSDRAM_DQ( ioSDRAM_DQ ),
    .oSDRAM_A( oSDRAM_A ),
    .oSDRAM_LDQM( oSDRAM_LDQM ),
    .oSDRAM_DQM( oSDRAM_DQM ),
    .oSDRAM_WE_( oSDRAM_WE_ ),
    .oSDRAM_CAS_( oSDRAM_CAS_ ),
    .oSDRAM_RAS_( oSDRAM_RAS_ ),
    .oSDRAM_CS_( oSDRAM_CS_ ),
    .oSDRAM_BA_( oSDRAM_BA_ ),
    .oSDRAM_CLK( oSDRAM_CLK ),
    .oSDRAM_CKE( oSDRAM_CKE ),

    .oI2C_SCLK( oI2C_SCLK ),
    .ioI2C_SDAT( ioI2C_SDAT ),

    .oVGA_CLK( oVGA_CLK ),
    .oVGA_HS( oVGA_HS ),
    .oVGA_VS( oVGA_VS ),
    .oVGA_BLANK( oVGA_BLANK ),
    .oVGA_SYNC( oVGA_SYNC ),
    .oVGA_RGB( oVGA_RGB ),
    .oVGA_X( VideoX ),
    .oVGA_Y( VideoY ),

    .iTD_DATA( iTD_DATA ),
    .iTD_HS( iTD_HS ),
    .iTD_VS( iTD_VS ),
    .oTD_RESET( oTD_RESET ),
    .iTD_CLK( iTD_CLK ) 
  );

  reg _USB_Go;
  initial _USB_Go = 1'b0;
  reg [5:0] _USB_Cnt;
  initial _USB_Cnt = 6'd0;
  wire USB_Pop;

  USB_FIFO
  USB_FIFO0
  (
  	.clock( Clk100 ),
  	.data( _FIFO_D ),
  	.rdreq( USB_Pop ),
  	.wrreq( _FIFO_Push ),
  	.empty( FIFO_Empty ),
  	.full( FIFO_Full ),
  	.q( FIFO_Q ),
  	.usedw( dbgFIFO_Used )
  );
  
  wire [9:0] AvgRGB = (oVGA_RGB[29:20] + oVGA_RGB[19:10] + oVGA_RGB[9:0]) / 3;
  
  reg _Set;
  initial _Set = 1'bx;
    
  reg _Y;
  initial _Y = 1'b0;
  
  reg [9:0] _VideoY;
  initial _VideoY = 10'hxxx;
  
  wire OK;
  Debounce
  Debounce00
  (
    .iClk( iClk27 ),
    .iD( !iButton_[1] ),
    .oQ( OK )
  );
    
  always_ff @( posedge iClk27 )
  begin
    // Defaults.
    _FIFO_Push  <= 1'b0;
    _USB_Go     <= 1'b0;
    
    //if( OK )
    begin
      if( ( (!_Set && AvgRGB > iSwitch[9:0]) || (_Set && AvgRGB < {iSwitch[17:10], iButton_[3:2]} )) && !_Y )
      begin
        if( _USB_Cnt == 6'd32 )
          _USB_Cnt <= 6'd0;
        else
          _USB_Cnt <= _USB_Cnt + 1'd1;
  
        _Set <= ~_Set;
        _FIFO_Push  <= 1'b1;
        _FIFO_D     <= { ~_Set, 1'b1, 4'hx, VideoX[9:0] };
        _VideoY <= VideoY[9:0];
        _Y <= 1'b1;
      end
      else if( _Y )
      begin
        _Y <= 1'b0;

        if( _USB_Cnt == 6'd32 )
          _USB_Cnt <= 6'd0;
        else
          _USB_Cnt <= _USB_Cnt + 1'd1;
  
        _FIFO_Push  <= 1'b1;
        _FIFO_D     <= { _Set, 1'b0, 4'hx, _VideoY };
        
        if( _USB_Cnt == 6'd31 )
          _USB_Go <= 1'b1;
      end
    end
  end
  
  assign oLEDR[0] = FIFO_Full;

  reg [15:0] _FIFO_D = 16'd1234;
  initial
  begin
    _FIFO_D = 16'd1234;
  end
  
  reg _FIFO_Push;
  initial _FIFO_Push = 1'b0;
    
  wire
  FIFO_Empty,
  FIFO_Full;
  wire [15:0] FIFO_Q;
  wire USB_Done;
  
	wire [9:0] dbgFIFO_Used;
  
  // USB control.
  wire [15:0] Dbg;
  USB
  USB0
  (
    .iClk( Clk100 ),
    .iDly_( POR_DlyDone ),
    
    // FIFO lines.
    .iGo( _USB_Go ),
    .iD( FIFO_Q ),
    .iCnt( _USB_Cnt ),
    .oPop( USB_Pop ),
    .oDone( USB_Done ),

    // ISP1362 lines.
    .iClk200( Clk200 ),
    .iINT2( iUSB_INT2 ),
    .ioD( ioUSB_D ),
    .oRESET_( oUSB_RESET_ ),
    .oA( oUSB_A ),
    .oRD_( oUSB_RD_ ),
    .oWR_( oUSB_WR_ ),
    .oCS_( oUSB_CS_ ),
    .oOTG_DP1( oUSB_OTG_DP1 ),
    .oOTG_DM1( oUSB_OTG_DM1 ),

    .oDbg( Dbg )
  );
  
  always_ff @( posedge Clk100 )
  begin
    _SSHLEDMDCtrlD[15:0] <= _Y;
  end
  
endmodule
