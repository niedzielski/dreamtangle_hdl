/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"

 
// Topmost simulation model.
// Created:   Friday, September 7, 2007   [Stephen Niedzielski]
// Modified:  Saturday, September 8, 2007 [Stephen Niedzielski]
module tbDreamTangle_HDL
(
);
  // Generate clock signals.
  wire  Clk50,
        Clk27;
  tbClk
  #(
    .Frequency_kHz( 50_000 )
  )
  tbClk0
  (
    ._oClk( Clk50 )
  );

  tbClk
  #(
    .Frequency_kHz( 27_000 )
  )
  tbClk1
  (
    ._oClk( Clk27 )
  );

  // Instantiate topmost synthesis module.
  DreamTangle_HDL
  DreamTangle_HDL0
  (
    // Clocks.
    .iClk50( Clk50 ),
    .iClk27( Clk27 ),

    // LEDs.
    .oLEDR(),
    // .oLEDG(),

    // Buttons amd switches.
    .iSwitch(),
    .iButton_(),
  
    // Hex display.
    .oHex7(),
    .oHex6(),
    .oHex5(),
    .oHex4(),
    .oHex3(),
    .oHex2(),
    .oHex1(),
    .oHex0(),
  
    // USB ISP1362.
    .iUSB_INT1(),
    .iUSB_INT2(),
    .iUSB_DACK1_(),
    .iUSB_DACK2_(),
    .ioUSB_D(),
    .oUSB_OTG_DP1(),
    .oUSB_OTG_DM1(),
    .oUSB_A(),
    .oUSB_RD_(),
    .oUSB_WR_(),
    .oUSB_CS_(),
    .oUSB_RESET_(),
    .oUSB_DREQ1(),
    .oUSB_DREQ2(),
  /*
    // General purpose IO.
    .ioGPIO1(),
    .ioGPIO0(),

    // SRAM.
    .oSRAM_A(),
    .ioSRAM_IO(),
    .oSRAM_CE_(),
    .oSRAM_WE_(),
    .oSRAM_LB_(),
    .oSRAM_UB_(),
    .oSRAM_OE_(),
*/
    // SDRAM.
    .ioSDRAM_DQ(),
    .oSDRAM_A(),
    .oSDRAM_LDQM(),
    .oSDRAM_DQM(),
    .oSDRAM_WE_(),
    .oSDRAM_CAS_(),
    .oSDRAM_RAS_(),
    .oSDRAM_CS_(),
    .oSDRAM_BA_(),
    .oSDRAM_CLK(),
    .oSDRAM_CKE(),
  
    // I2C.
    .oI2C_SCLK(),
    .ioI2C_SDAT(),
  
    // VGA ADV7123.
    .oVGA_CLK(),
    .oVGA_HS(),  // Connected to display HSYNC.
    .oVGA_VS(),  // Connected to display VSYNC.
    .oVGA_BLANK(),
    .oVGA_SYNC(),
    .oVGA_RGB(),
  
    // TV Decoder ADV7181B.
    .iTD_DATA(),   // Connects to P[8:15].
    .iTD_HS(),
    .iTD_VS(),
    .iTD_CLK(),
    .oTD_RESET()
  );

  initial
  begin
    #5000000 $finish; 
  end

endmodule
