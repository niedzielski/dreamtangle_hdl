/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu

The following source has been modified from the Altera DE2 TV Box Demonstration.
The original file header appears below.
*******************************************************************************/

// --------------------------------------------------------------------
// Copyright (c) 2005 by Terasic Technologies Inc. 
// --------------------------------------------------------------------
//
// Permission:
//
//   Terasic grants permission to use and modify this code for use
//   in synthesis for all Terasic Development Boards and Altera Development 
//   Kits made by Terasic.  Other use of this code, including the selling 
//   ,duplication, or modification of any portion is strictly prohibited.
//
// Disclaimer:
//
//   This VHDL/Verilog or C/C++ source code is intended as a design reference
//   which illustrates how these types of functions can be implemented.
//   It is the user's responsibility to verify their design for
//   consistency and functionality through the use of formal
//   verification methods.  Terasic provides no warranty regarding the use 
//   or functionality of this code.
//
// --------------------------------------------------------------------
//           
//                     Terasic Technologies Inc
//                     356 Fu-Shin E. Rd Sec. 1. JhuBei City,
//                     HsinChu County, Taiwan
//                     302
//
//                     web: http://www.terasic.com/
//                     email: support@terasic.com
//
// --------------------------------------------------------------------
// Major Functions:  DE2 TV Box
// --------------------------------------------------------------------
//
// Revision History :
// --------------------------------------------------------------------
//   Ver  :| Author            :| Mod. Date :| Changes Made:
//   V1.0 :| Joe Yang         :| 05/07/05  :| Initial Revision
//   V1.1 :| Johnny Chen       :| 05/09/05  :| Changed YCbCr2RGB Block,
//                         RGB output 8 Bits => 10 Bits
//   V1.2 :| Johnny Chen     :| 05/10/05  :| H_SYNC & V_SYNC Timing fixed.
//   V1.3 :| Johnny Chen       :| 05/11/16  :| Added FLASH Address FL_ADDR[21:20]
//   V1.4 :| Joe Yang         :| 06/07/20  :| Modify Output Color
//   V2.0 :| Johnny Chen     :| 06/11/20  :| New Version for DE2 v2.X PCB.
// --------------------------------------------------------------------

module Video
(
  input iClk27,
  input iClk50,

  input iRst,

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

  // VGA ADV7123.
  output        oVGA_CLK,
  output        oVGA_HS,  // Connected to display HSYNC.
  output        oVGA_VS,  // Connected to display VSYNC.
  output        oVGA_BLANK,
  output        oVGA_SYNC,
  output [29:0] oVGA_RGB,
  output [10:0] oVGA_X,
  output [10:0] oVGA_Y,

  // TV Decoder ADV7181B.
  output      oI2C_SCLK,
  inout       ioI2C_SDAT,
  input [7:0] iTD_DATA,   // Connects to P[8:15].
  input       iTD_HS,
  input       iTD_VS,
  input       iTD_CLK,
  output      oTD_RESET
);

//  For ITU-R 656 Decoder
wire  [15:0]  YCbCr;
wire  [9:0]  TV_X;
wire      TV_DVAL;

//  For VGA Controller
wire  [9:0]  mRed;
wire  [9:0]  mGreen;
wire  [9:0]  mBlue;
wire      VGA_Read;  //  VGA data request
wire      m1VGA_Read;  //  Read odd field
wire      m2VGA_Read;  //  Read even field

//  For YUV 4:2:2 to YUV 4:4:4
wire  [7:0]  mY;
wire  [7:0]  mCb;
wire  [7:0]  mCr;

//  For field select
wire  [15:0]  mYCbCr;
wire  [15:0]  mYCbCr_d;
wire  [15:0]  m1YCbCr;
wire  [15:0]  m2YCbCr;
wire  [15:0]  m3YCbCr;

//  For Delay Timer
wire      TD_Stable;
wire      DLY0;
wire      DLY1;
wire      DLY2;

//  For Down Sample
wire  [3:0]  Remain;
wire  [9:0]  Quotient;

wire      mDVAL;

wire  [15:0]  m4YCbCr;
wire  [15:0]  m5YCbCr;
wire  [8:0]  Tmp1,Tmp2;
wire  [7:0]  Tmp3,Tmp4;

assign  Tmp1  =  m4YCbCr[7:0]+mYCbCr_d[7:0];
assign  Tmp2  =  m4YCbCr[15:8]+mYCbCr_d[15:8];
assign  Tmp3  =  Tmp1[8:2]+m3YCbCr[7:1];
assign  Tmp4  =  Tmp2[8:2]+m3YCbCr[15:9];
assign  m5YCbCr  =  {Tmp4,Tmp3};

wire AUD_CTRL_CLK;
wire WR1_FULL;
assign  m1VGA_Read  =  oVGA_Y[0]    ?  1'b0    :  VGA_Read  ;
assign  m2VGA_Read  =  oVGA_Y[0]    ?  VGA_Read  :  1'b0    ;
assign  mYCbCr_d  =  !oVGA_Y[0]    ?  m1YCbCr    :
                      m2YCbCr    ;
assign  mYCbCr    =  m5YCbCr;

//  Line buffer, delay one line
Line_Buffer u10  (  .clken(VGA_Read),
          .clock(iClk27),
          .shiftin(mYCbCr_d),
          .shiftout(m3YCbCr),
          .taps());
          
Line_Buffer u11  (  .clken(VGA_Read),
          .clock(iClk27),
          .shiftin(m3YCbCr),
          .shiftout(m4YCbCr),
          .taps());

//  Enable TV Decoder
assign oTD_RESET = iRst;

//  Audio CODEC and video decoder setting
I2C_AV_Config     u1  (  //  Host Side
              .iCLK(iClk50),
              .iRST_N(iRst),
              //  I2C Side
              .I2C_SCLK(oI2C_SCLK),
              .I2C_SDAT(ioI2C_SDAT)  );

//  TV Decoder Stable Check
TD_Detect      u2  (  .oTD_Stable(TD_Stable),
              .iTD_VS(iTD_VS),
              .iTD_HS(iTD_HS),
              .iRST_N(iRst)  );

//  Reset Delay Timer
Reset_Delay      u3  (  .iCLK(iClk50),
              .iRST(TD_Stable),
              .oRST_0(DLY0),
              .oRST_1(DLY1),
              .oRST_2(DLY2));

//  ITU-R 656 to YUV 4:2:2
ITU_656_Decoder    u4  (  //  TV Decoder Input
              .iTD_DATA(iTD_DATA),
              //  Position Output
              .oTV_X(TV_X),
							.oTV_Y(  ),
							.oTV_Cont(  ),
              //  YUV 4:2:2 Output
              .oYCbCr(YCbCr),
              .oDVAL(TV_DVAL),
              //  Control Signals
              .iSwap_CbCr(Quotient[0]),
              .iSkip(Remain==4'h0),
              .iRST_N(DLY1),
              .iCLK_27(iTD_CLK)  );
//  For Down Sample 720 to 640
DIV         u5  (  .aclr(!DLY0),  
              .clock(iTD_CLK),
              .denom(4'h9),
              .numer(TV_X),
              .quotient(Quotient),
              .remain(Remain));
		
//  SDRAM frame buffer
Sdram_Control_4Port  u6  (  //  HOST Side
                .REF_CLK(iClk27),
              .CLK_18(AUD_CTRL_CLK),
              .RESET_N(1'b1),
              .CLK(),
              //  FIFO Write Side 1
                .WR1_DATA(YCbCr),
              .WR1(TV_DVAL),
              .WR1_FULL(WR1_FULL),
              .WR1_ADDR(0),
              .WR1_MAX_ADDR(640*507),    //  525-18
              .WR1_LENGTH(9'h80),
              .WR1_LOAD(!DLY0),
              .WR1_CLK(iTD_CLK),
              .WR1_USE(),
          		//	FIFO Write Side 2
              .WR2_DATA(  ),
          		.WR2(  ),
          		.WR2_ADDR(  ),
          		.WR2_MAX_ADDR(  ),
          		.WR2_LENGTH(  ),
          		.WR2_LOAD(  ),
          		.WR2_CLK(  ),
          		.WR2_FULL(  ),
          		.WR2_USE(  ),

              //  FIFO Read Side 1
                .RD1_DATA(m1YCbCr),
                  .RD1(m1VGA_Read),
                  .RD1_ADDR(640*13),      //  Read odd field and bypess blanking
              .RD1_MAX_ADDR(640*253),
              .RD1_LENGTH(9'h80),
                  .RD1_LOAD(!DLY0),
              .RD1_CLK(iClk27),
              .RD1_EMPTY(),
              .RD1_USE(),
              //  FIFO Read Side 2
                .RD2_DATA(m2YCbCr),
                  .RD2(m2VGA_Read),
                  .RD2_ADDR(640*267),      //  Read even field and bypess blanking
              .RD2_MAX_ADDR(640*507),
              .RD2_LENGTH(9'h80),
                  .RD2_LOAD(!DLY0),
              .RD2_CLK(iClk27),
              .RD2_EMPTY(),
              .RD2_USE(),

              //  SDRAM Side
                .SA(oSDRAM_A),
                .BA(oSDRAM_BA_),
                .CS_N(oSDRAM_CS_),
                .CKE(oSDRAM_CKE),
                .RAS_N(oSDRAM_RAS_),
                    .CAS_N(oSDRAM_CAS_),
                    .WE_N(oSDRAM_WE_),
                .DQ(ioSDRAM_DQ),
                    .DQM({oSDRAM_DQM,oSDRAM_LDQM}),
              .SDR_CLK(oSDRAM_CLK)  );

//  YUV 4:2:2 to YUV 4:4:4
YUV422_to_444    u7  (  //  YUV 4:2:2 Input
              .iYCbCr(mYCbCr),
              //  YUV  4:4:4 Output
              .oY(mY),
              .oCb(mCb),
              .oCr(mCr),
              //  Control Signals
              .iX(oVGA_X),
              .iCLK(iClk27),
              .iRST_N(DLY0));

//  YCbCr 8-bit to RGB-10 bit 
YCbCr2RGB       u8  (  //  Output Side
              .Red(mRed),
              .Green(mGreen),
              .Blue(mBlue),
              .oDVAL(mDVAL),
              //  Input Side
              .iY(mY),
              .iCb(mCb),
              .iCr(mCr),
              .iDVAL(VGA_Read),
              //  Control Signal
              .iRESET(!DLY2),
              .iCLK(iClk27));

//  VGA Controller
VGA_Ctrl      u9  (  //  Host Side
              .iRed(mRed),
              .iGreen(mGreen),
              .iBlue(mBlue),
              .oCurrent_X(oVGA_X),
              .oCurrent_Y(oVGA_Y),
              .oAddress(),
              .oRequest(VGA_Read),

              //  VGA Side
              .oVGA_R(oVGA_RGB[29:20]),
              .oVGA_G(oVGA_RGB[19:10]),
              .oVGA_B(oVGA_RGB[9:0]),
              .oVGA_HS(oVGA_HS),
              .oVGA_VS(oVGA_VS),
              .oVGA_SYNC(oVGA_SYNC),
              .oVGA_BLANK(oVGA_BLANK),
              .oVGA_CLOCK(oVGA_CLK),
              //  Control Signal
              .iCLK(iClk27),
              .iRST_N(DLY2)  );

endmodule
