/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "ISP1362Ctrl.h"
`include "USBCtrl.h"

localparam
romCmd = 17,
romRd  = 16,
romD   = 15;

`ifdef ALDEC
  reg [17:0] romStall [0:3];
  initial
  begin
  				      //  Cmd,  Rd,   Data
    romStall[0] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romStall[1] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romStall[2] = { 1'b1, 1'b0, 8'hxx, `Stall_control_IN_endpoint };
    romStall[3] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romStall [0:3] =
  '{
  //  Cmd,  Rd,   Data
    { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
    { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
    { 1'b1, 1'b0, 8'hxx, `Stall_control_IN_endpoint },
    { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif

`ifdef ALDEC
  reg [17:0] romInit [0:45];
  initial
  begin
  		          //  Cmd,  Rd,   Data
  	romInit[00] = { 1'b1, 1'b0, 8'hxx, `Unlock_device };
  	romInit[01] = { 1'b0, 1'b0, 16'hAA37 }; // Unlock code.
  	romInit[02] = { 1'b1, 1'b0, 8'hxx, `Write_device_address }; // Enable the device controller.
  	romInit[03] = { 1'b0, 1'b0, 8'h00,	{
        				                        	1'b1,        // DEVEN
        				                        	7'b000_0000  // DEVADR
                              					}
  				        };
  	romInit[04] = { 1'b1, 1'b0, 8'hxx, `Write_control_OUT_configuration };
  	romInit[05] = { 1'b0, 1'b0, 8'h00,	{
        					                        1'b1,   // FIFOEN
        					                        1'b0,   // EPDIR
        					                        1'b0,   // DBLBUF
        					                        1'b0,   // FFOISO
        					                        4'b0011 // FFOSZ
          					                    }
  				        };
  	romInit[06] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_configuration };
  	romInit[07] = { 1'b0, 1'b0, 8'h00,	{
        					                        1'b1,   // FIFOEN
        					                        1'b1,   // EPDIR
        					                        1'b0,   // DBLBUF
        					                        1'b0,   // FFOISO
        					                        4'b0011 // FFOSZ
          					                    }
  				        };
  	romInit[08] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_1_configuration };
  	romInit[09] = { 1'b0, 1'b0, 8'h00,	{
        					                        1'b1,   // FIFOEN
        					                        1'b1,   // EPDIR
        					                        1'b0,   // DBLBUF
        					                        1'b0,   // FFOISO
        					                        4'b0011 // FFOSZ
        					                      }
  				        };
  	romInit[10] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_2_configuration }; // Disable endpoints 2 - 14.
  	romInit[11] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[12] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_3_configuration };
  	romInit[13] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[14] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_4_configuration };
  	romInit[15] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[16] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_5_configuration };
  	romInit[17] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[18] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_6_configuration };
  	romInit[19] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[20] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_7_configuration };
  	romInit[21] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[22] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_8_configuration };
  	romInit[23] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[24] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_9_configuration };
  	romInit[25] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[26] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_10_configuration };
  	romInit[27] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[28] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_11_configuration };
  	romInit[29] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[30] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_12_configuration };
  	romInit[31] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[32] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_13_configuration };
  	romInit[33] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
  	romInit[34] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_14_configuration };
  	romInit[35] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b0,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0000 // FFOSZ
                                        }
                  };
    romInit[36] = { 1'b1, 1'b0, 8'hxx, `Write_Mode_register };
  	romInit[37] = { 1'b0, 1'b0, 8'h00,  {
                                          2'b0, // reserved
                                          1'b0, // GOSUSP
                                          1'b0, // reserved
                                          1'b1, // INTENA
                                          1'b0, // DBGMOD
                                          1'b0, // reserved
                                          1'b0  // SOFTCT
                                        }
                  };
  	romInit[38] = { 1'b1, 1'b0, 8'hxx, `Write_hardware_configuration };
  	romInit[39] = { 1'b0, 1'b0, {
                                  1'b0,   // reserved
                                  1'b1,   // EXTPUL
                                  1'b1,   // NOLAZY
                                  1'b1,   // CLKRUN
                                  4'b0000,// CKDIV
                                  1'b0,   // DAKOLY
                                  1'b1,   // DRQPOL
                                  1'b1,   // DAKPOL
                                  1'b0,   // reserved
                                  1'b0,   // WKUPCS
                                  1'b0,   // reserved
                                  1'b1,   // INTLVL
                                  1'b1    // INTPOL
                                }
                  };
    romInit[40] = { 1'b1, 1'b0, 8'hxx, `Write_DcInterruptEnable_register };
  	romInit[41] = { 1'b0, 1'b0, { // Low word.
                                  6'b00_0001, // IEP6-1
                                  1'b1,       // IEP0IN
                                  1'b1,       // IEP0OUT
                                  1'b0,       // reserved
                                  1'b0,       // SP_IEEOT
                                  1'b0,       // IEPSOF
                                  1'b0,       // IESOF
                                  1'b0,       // IEEOT
                                  1'b0,       // IESUSP
                                  1'b0,       // IERESM
                                  1'b1        // IERST
                                } 
                  };
  	romInit[42] = { 1'b0, 1'b0, { // High word.
                                  8'b0000_0000, // reserved, must write logic 0
                                  8'b0000_0000  // IEP14-7
                                }
                  };
  	romInit[43] = { 1'b1, 1'b0, 8'hxx, `Write_DMA_configuration };
  	romInit[44] = { 1'b0, 1'b0, {
                                  1'b0,       // CNTREN
                                  1'b0,       // SHORTP
                                  6'b00_0000, // reserved
                                  4'b1111,    // EPDIX
                                  1'b0,       // DMAEN
                                  1'b0,       // reserved
                                  2'b11       // BURSTL
                                }
                  };
  	romInit[45] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romInit [0:45] =
  '{
  //  Cmd,  Rd,   Data
    { 1'b1, 1'b0, 8'hxx, `Unlock_device },
    { 1'b0, 1'b0, 16'hAA37 }, // Unlock code.
    { 1'b1, 1'b0, 8'hxx, `Write_device_address }, // Enable the device controller.
    { 1'b0, 1'b0, 8'h00,	{
	                        	1'b1,        // DEVEN
	                        	7'b000_0000  // DEVADR
                					}
    },
    { 1'b1, 1'b0, 8'hxx, `Write_control_OUT_configuration },
    { 1'b0, 1'b0, 8'h00,	{
		                        1'b1,   // FIFOEN
		                        1'b0,   // EPDIR
		                        1'b0,   // DBLBUF
		                        1'b0,   // FFOISO
		                        4'b0011 // FFOSZ
			                    }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_control_IN_configuration },
    { 1'b0, 1'b0, 8'h00,	{
		                        1'b1,   // FIFOEN
		                        1'b1,   // EPDIR
		                        1'b0,   // DBLBUF
		                        1'b0,   // FFOISO
		                        4'b0011 // FFOSZ
			                    }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_1_configuration },
    { 1'b0, 1'b0, 8'h00,	{
		                        1'b1,   // FIFOEN
		                        1'b1,   // EPDIR
		                        1'b0,   // DBLBUF
		                        1'b0,   // FFOISO
		                        4'b0011 // FFOSZ
		                      }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_2_configuration }, // Disable endpoints 2 - 14.
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_3_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_4_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_5_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_6_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_7_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_8_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_9_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_10_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_11_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_12_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_13_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_endpoint_14_configuration },
    { 1'b0, 1'b0, 8'h00,  {
                            1'b0,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0000 // FFOSZ
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_Mode_register },
    { 1'b0, 1'b0, 8'h00,  {
                            2'b0, // reserved
                            1'b0, // GOSUSP
                            1'b0, // reserved
                            1'b1, // INTENA
                            1'b0, // DBGMOD
                            1'b0, // reserved
                            1'b0  // SOFTCT
                          }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_hardware_configuration },
    { 1'b0, 1'b0, {
                    1'b0,   // reserved
                    1'b1,   // EXTPUL
                    1'b1,   // NOLAZY
                    1'b1,   // CLKRUN
                    4'b0000,// CKDIV
                    1'b0,   // DAKOLY
                    1'b1,   // DRQPOL
                    1'b1,   // DAKPOL
                    1'b0,   // reserved
                    1'b0,   // WKUPCS
                    1'b0,   // reserved
                    1'b1,   // INTLVL
                    1'b1    // INTPOL
                  }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_DcInterruptEnable_register },
    { 1'b0, 1'b0, { // Low word.
                    6'b00_0001, // IEP6-1
                    1'b1,       // IEP0IN
                    1'b1,       // IEP0OUT
                    1'b0,       // reserved
                    1'b0,       // SP_IEEOT
                    1'b0,       // IEPSOF
                    1'b0,       // IESOF
                    1'b0,       // IEEOT
                    1'b0,       // IESUSP
                    1'b0,       // IERESM
                    1'b1        // IERST
                  } 
    },
    { 1'b0, 1'b0, { // High word.
                    8'b0000_0000, // reserved, must write logic 0
                    8'b0000_0000  // IEP14-7
                  }
    },
    { 1'b1, 1'b0, 8'hxx, `Write_DMA_configuration },
    { 1'b0, 1'b0, {
                    1'b0,       // CNTREN
                    1'b0,       // SHORTP
                    6'b00_0000, // reserved
                    4'b1111,    // EPDIX
                    1'b0,       // DMAEN
                    1'b0,       // reserved
                    2'b11       // BURSTL
                  }
    },
    { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif

`ifdef ALDEC
  reg [17:0] romGetDevice [0:14];
  initial
  begin
                     //  Cmd,  Rd,   Data
    romGetDevice[00] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romGetDevice[01] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romGetDevice[02] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer };
    romGetDevice[03] = { 1'b0, 1'b0, 16'd18 }; // Packet length.
    romGetDevice[04] = { 1'b0, 1'b0, 8'h01, 8'h12 }; // Packet.
    romGetDevice[05] = { 1'b0, 1'b0, 16'h0210 };
    romGetDevice[06] = { 1'b0, 1'b0, 8'h00, 8'h00 };
    romGetDevice[07] = { 1'b0, 1'b0, 8'h40, 8'h00 };
    romGetDevice[08] = { 1'b0, 1'b0, `USB_ID_Vendor };
    romGetDevice[09] = { 1'b0, 1'b0, `USB_ID_Product };
    romGetDevice[10] = { 1'b0, 1'b0, 16'h0000 };
    romGetDevice[11] = { 1'b0, 1'b0, 8'h02, 8'h01 };
    romGetDevice[12] = { 1'b0, 1'b0, 8'h01, 8'h00 };
    romGetDevice[13] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romGetDevice[14] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romGetDevice [0:14] =
  '{
   //  Cmd,  Rd,   Data
     { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
     { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
     { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer },
     { 1'b0, 1'b0, 16'd18 }, // Packet length.
     { 1'b0, 1'b0, 8'h01, 8'h12 }, // Packet.
     { 1'b0, 1'b0, 16'h0210 },
     { 1'b0, 1'b0, 8'h00, 8'h00 },
     { 1'b0, 1'b0, 8'h40, 8'h00 },
     { 1'b0, 1'b0, `USB_ID_Vendor },
     { 1'b0, 1'b0, `USB_ID_Product },
     { 1'b0, 1'b0, 16'h0000 },
     { 1'b0, 1'b0, 8'h02, 8'h01 },
     { 1'b0, 1'b0, 8'h01, 8'h00 },
     { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
     { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif

`ifdef ALDEC
  reg [17:0] romSetAdr [0:6];
  initial
  begin
  				       //  Cmd,  Rd,   Data
  	romSetAdr[0] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };        // Send empty packet.
  	romSetAdr[1] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };  // ''
  	romSetAdr[2] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer };   // ''
  	romSetAdr[3] = { 1'b0, 1'b0, 16'h0000 };                          // ''
  	romSetAdr[4] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };// ''
    romSetAdr[5] = { 1'b1, 1'b0, 8'hxx, `Write_device_address };
    romSetAdr[6] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romSetAdr [0:6] =
  '{
    { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },        // Send empty packet.
    { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },  // ''
    { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer },   // ''
    { 1'b0, 1'b0, 16'h0000 },                          // ''
    { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },// ''
    { 1'b1, 1'b0, 8'hxx, `Write_device_address },
    { 1'b1, 1'b1, 16'hxxxx } // End.
  };
`endif

`ifdef ALDEC
  reg [17:0] romGetCfg [0:18];
  initial
  begin
                  //  Cmd,  Rd,   Data
    romGetCfg[00] = { 1'b0, 1'b0, 8'h02, 8'h09 };
    romGetCfg[01] = { 1'b0, 1'b0, 16'h0022 };
    romGetCfg[02] = { 1'b0, 1'b0, 8'h01, 8'h01 };
    romGetCfg[03] = { 1'b0, 1'b0, 8'h80, 8'h00 };
    romGetCfg[04] = { 1'b0, 1'b0, 8'h09, 8'h32 };
    romGetCfg[05] = { 1'b0, 1'b0, 8'h00, 8'h04 };
    romGetCfg[06] = { 1'b0, 1'b0, 8'h01, 8'h00 };
    romGetCfg[07] = { 1'b0, 1'b0, 8'h00, 8'h03 };
    romGetCfg[08] = { 1'b0, 1'b0, 8'h00, 8'h00 };
    romGetCfg[09] = { 1'b0, 1'b0, 8'h21, 8'h09 };
    romGetCfg[10] = { 1'b0, 1'b0, 16'h0111 };
    romGetCfg[11] = { 1'b0, 1'b0, 8'h01, 8'h00 };
    romGetCfg[12] = { 1'b0, 1'b0, 8'h15, 8'h22 };
    romGetCfg[13] = { 1'b0, 1'b0, 8'h07, 8'h00 };
    romGetCfg[14] = { 1'b0, 1'b0, 8'h81, 8'h05 };
    romGetCfg[15] = { 1'b0, 1'b0, 8'h40, 8'h03 };
    romGetCfg[16] = { 1'b0, 1'b0, 8'h01, 8'h00 };
    romGetCfg[17] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romGetCfg[18] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romGetCfg [0:18] =
  '{
  //  Cmd,  Rd,   Data
    { 1'b0, 1'b0, 8'h02, 8'h09 },
    { 1'b0, 1'b0, 16'h0022 },
    { 1'b0, 1'b0, 8'h01, 8'h01 },
    { 1'b0, 1'b0, 8'h80, 8'h00 },
    { 1'b0, 1'b0, 8'h09, 8'h32 },
    { 1'b0, 1'b0, 8'h00, 8'h04 },
    { 1'b0, 1'b0, 8'h01, 8'h00 },
    { 1'b0, 1'b0, 8'h00, 8'h03 },
    { 1'b0, 1'b0, 8'h00, 8'h00 },
    { 1'b0, 1'b0, 8'h21, 8'h09 },
    { 1'b0, 1'b0, 16'h0111 },
    { 1'b0, 1'b0, 8'h01, 8'h00 },
    { 1'b0, 1'b0, 8'h15, 8'h22 },
    { 1'b0, 1'b0, 8'h07, 8'h00 },
    { 1'b0, 1'b0, 8'h81, 8'h05 },
    { 1'b0, 1'b0, 8'h40, 8'h03 },
    { 1'b0, 1'b0, 8'h01, 8'h00 },
    { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
    { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif

`ifdef ALDEC
  reg [17:0] romGetReport [0:16];
  initial
  begin
                     //  Cmd,  Rd,   Data
    romGetReport[00] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romGetReport[01] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romGetReport[02] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer };
    romGetReport[03] = { 1'b0, 1'b0, 16'h0015 }; // Packet length.
    romGetReport[04] = { 1'b0, 1'b0, 8'h00, 8'h06 }; // Packet.
    romGetReport[05] = { 1'b0, 1'b0, 8'h09, 8'hFF };
    romGetReport[06] = { 1'b0, 1'b0, 8'hA1, 8'h01 };
    romGetReport[07] = { 1'b0, 1'b0, 8'h09, 8'h01 };
    romGetReport[08] = { 1'b0, 1'b0, 8'h15, 8'h01 };
    romGetReport[09] = { 1'b0, 1'b0, 8'h26, 8'h00 };
    romGetReport[10] = { 1'b0, 1'b0, 8'h00, 8'hFF };
    romGetReport[11] = { 1'b0, 1'b0, 8'h08, 8'h75 };
    romGetReport[12] = { 1'b0, 1'b0, 8'h40, 8'h95 };
    romGetReport[13] = { 1'b0, 1'b0, 8'h02, 8'h81 };
    romGetReport[14] = { 1'b0, 1'b0, 8'h00, 8'hC0 };
    romGetReport[15] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romGetReport[16] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romGetReport [0:16] =
  '{
  //  Cmd,  Rd,   Data
    { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
    { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
    { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer },
    { 1'b0, 1'b0, 16'h0015 }, // Packet length.
    { 1'b0, 1'b0, 8'h00, 8'h06 }, // Packet.
    { 1'b0, 1'b0, 8'h09, 8'hFF },
    { 1'b0, 1'b0, 8'hA1, 8'h01 },
    { 1'b0, 1'b0, 8'h09, 8'h01 },
    { 1'b0, 1'b0, 8'h15, 8'h01 },
    { 1'b0, 1'b0, 8'h26, 8'h00 },
    { 1'b0, 1'b0, 8'h00, 8'hFF },
    { 1'b0, 1'b0, 8'h08, 8'h75 },
    { 1'b0, 1'b0, 8'h40, 8'h95 },
    { 1'b0, 1'b0, 8'h02, 8'h81 },
    { 1'b0, 1'b0, 8'h00, 8'hC0 },
    { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
    { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif

`ifdef ALDEC
  reg [17:0] romString0 [0:7];
  initial
  begin
                  //  Cmd,  Rd,   Data
    romString0[0] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romString0[1] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romString0[2] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer };
    romString0[3] = { 1'b0, 1'b0, 16'd4 }; // Packet size.
    romString0[4] = { 1'b0, 1'b0, { 8'h03, 8'h04 } }; // Packet.
    romString0[5] = { 1'b0, 1'b0, 16'h0409 };
    romString0[6] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romString0[7] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romString0 [0:7] =
  '{
    //  Cmd,  Rd,   Data
      { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
      { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
      { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer },
      { 1'b0, 1'b0, 16'd4 }, // Packet size.
      { 1'b0, 1'b0, { 8'h03, 8'h04 } }, // Packet.
      { 1'b0, 1'b0, 16'h0409 },
      { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
      { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif


`ifdef ALDEC
  reg [17:0] romString1 [0:37];
  initial
  begin
                  //  Cmd,  Rd,   Data
    romString1[00] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romString1[01] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romString1[02] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer };
    romString1[03] = { 1'b0, 1'b0, 16'd64 }; // Packet size.
    romString1[04] = { 1'b0, 1'b0, { 8'h03, 8'h40 } }; // Packet.
    romString1[05] = { 1'b0, 1'b0, 8'h00, "D" };
    romString1[06] = { 1'b0, 1'b0, 8'h00, "i" };
    romString1[07] = { 1'b0, 1'b0, 8'h00, "g" };
    romString1[08] = { 1'b0, 1'b0, 8'h00, "i" };
    romString1[09] = { 1'b0, 1'b0, 8'h00, "P" };
    romString1[10] = { 1'b0, 1'b0, 8'h00, "e" };
    romString1[11] = { 1'b0, 1'b0, 8'h00, "n" };
    romString1[12] = { 1'b0, 1'b0, 8'h00, " " };
    romString1[13] = { 1'b0, 1'b0, 8'h00, "I" };
    romString1[14] = { 1'b0, 1'b0, 8'h00, "n" };
    romString1[15] = { 1'b0, 1'b0, 8'h00, "s" };
    romString1[16] = { 1'b0, 1'b0, 8'h00, "t" };
    romString1[17] = { 1'b0, 1'b0, 8'h00, "i" };
    romString1[18] = { 1'b0, 1'b0, 8'h00, "t" };
    romString1[19] = { 1'b0, 1'b0, 8'h00, "u" };
    romString1[20] = { 1'b0, 1'b0, 8'h00, "t" };
    romString1[21] = { 1'b0, 1'b0, 8'h00, "e" };
    romString1[22] = { 1'b0, 1'b0, 8'h00, " " };
    romString1[23] = { 1'b0, 1'b0, 8'h00, "o" };
    romString1[24] = { 1'b0, 1'b0, 8'h00, "f" };
    romString1[25] = { 1'b0, 1'b0, 8'h00, " " };
    romString1[26] = { 1'b0, 1'b0, 8'h00, "T" };
    romString1[27] = { 1'b0, 1'b0, 8'h00, "e" };
    romString1[28] = { 1'b0, 1'b0, 8'h00, "c" };
    romString1[29] = { 1'b0, 1'b0, 8'h00, "h" };
    romString1[30] = { 1'b0, 1'b0, 8'h00, "n" };
    romString1[31] = { 1'b0, 1'b0, 8'h00, "o" };
    romString1[32] = { 1'b0, 1'b0, 8'h00, "l" };
    romString1[33] = { 1'b0, 1'b0, 8'h00, "o" };
    romString1[34] = { 1'b0, 1'b0, 8'h00, "g" };
    romString1[35] = { 1'b0, 1'b0, 8'h00, "y" };
    romString1[36] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romString1[37] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romString1 [0:37] =
  '{
   //  Cmd,  Rd,   Data
     { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
     { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
     { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer },
     { 1'b0, 1'b0, 16'd64 }, // Packet size.
     { 1'b0, 1'b0, { 8'h03, 8'h40 } }, // Packet.
     { 1'b0, 1'b0, 8'h00, "D" },
     { 1'b0, 1'b0, 8'h00, "i" },
     { 1'b0, 1'b0, 8'h00, "g" },
     { 1'b0, 1'b0, 8'h00, "i" },
     { 1'b0, 1'b0, 8'h00, "P" },
     { 1'b0, 1'b0, 8'h00, "e" },
     { 1'b0, 1'b0, 8'h00, "n" },
     { 1'b0, 1'b0, 8'h00, " " },
     { 1'b0, 1'b0, 8'h00, "I" },
     { 1'b0, 1'b0, 8'h00, "n" },
     { 1'b0, 1'b0, 8'h00, "s" },
     { 1'b0, 1'b0, 8'h00, "t" },
     { 1'b0, 1'b0, 8'h00, "i" },
     { 1'b0, 1'b0, 8'h00, "t" },
     { 1'b0, 1'b0, 8'h00, "u" },
     { 1'b0, 1'b0, 8'h00, "t" },
     { 1'b0, 1'b0, 8'h00, "e" },
     { 1'b0, 1'b0, 8'h00, " " },
     { 1'b0, 1'b0, 8'h00, "o" },
     { 1'b0, 1'b0, 8'h00, "f" },
     { 1'b0, 1'b0, 8'h00, " " },
     { 1'b0, 1'b0, 8'h00, "T" },
     { 1'b0, 1'b0, 8'h00, "e" },
     { 1'b0, 1'b0, 8'h00, "c" },
     { 1'b0, 1'b0, 8'h00, "h" },
     { 1'b0, 1'b0, 8'h00, "n" },
     { 1'b0, 1'b0, 8'h00, "o" },
     { 1'b0, 1'b0, 8'h00, "l" },
     { 1'b0, 1'b0, 8'h00, "o" },
     { 1'b0, 1'b0, 8'h00, "g" },
     { 1'b0, 1'b0, 8'h00, "y" },
     { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
     { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif


`ifdef ALDEC
  reg [17:0] romString2 [0:17];
  initial
  begin
                  //  Cmd,  Rd,   Data
    romString2[00] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romString2[01] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romString2[02] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer };
    romString2[03] = { 1'b0, 1'b0, 16'd24 }; // Packet size.
    romString2[04] = { 1'b0, 1'b0, { 8'h03, 8'h18 } }; // Packet.
    romString2[05] = { 1'b0, 1'b0, 8'h00, "D" };
    romString2[06] = { 1'b0, 1'b0, 8'h00, "r" };
    romString2[07] = { 1'b0, 1'b0, 8'h00, "e" };
    romString2[08] = { 1'b0, 1'b0, 8'h00, "a" };
    romString2[09] = { 1'b0, 1'b0, 8'h00, "m" };
    romString2[10] = { 1'b0, 1'b0, 8'h00, "T" };
    romString2[11] = { 1'b0, 1'b0, 8'h00, "a" };
    romString2[12] = { 1'b0, 1'b0, 8'h00, "n" };
    romString2[13] = { 1'b0, 1'b0, 8'h00, "g" };
    romString2[14] = { 1'b0, 1'b0, 8'h00, "l" };
    romString2[15] = { 1'b0, 1'b0, 8'h00, "e" };
    romString2[16] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romString2[17] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romString2 [0:17] =
  '{
   //  Cmd,  Rd,   Data
     { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
     { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
     { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer },
     { 1'b0, 1'b0, 16'd24 }, // Packet size.
     { 1'b0, 1'b0, { 8'h03, 8'h18 } }, // Packet.
     { 1'b0, 1'b0, 8'h00, "D" },
     { 1'b0, 1'b0, 8'h00, "r" },
     { 1'b0, 1'b0, 8'h00, "e" },
     { 1'b0, 1'b0, 8'h00, "a" },
     { 1'b0, 1'b0, 8'h00, "m" },
     { 1'b0, 1'b0, 8'h00, "T" },
     { 1'b0, 1'b0, 8'h00, "a" },
     { 1'b0, 1'b0, 8'h00, "n" },
     { 1'b0, 1'b0, 8'h00, "g" },
     { 1'b0, 1'b0, 8'h00, "l" },
     { 1'b0, 1'b0, 8'h00, "e" },
     { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
     { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif


`ifdef ALDEC
  reg [17:0] romSetCfg [0:12];
  initial
  begin
                  //  Cmd,  Rd,   Data
    romSetCfg[00] = { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up };
    romSetCfg[01] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romSetCfg[02] = { 1'b1, 1'b0, 8'hxx, `Write_control_OUT_configuration }; // Configure EP0O.
    romSetCfg[03] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b1,   // FIFOEN
                                          1'b0,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0011 // FFOSZ
                                        }
                    };
    romSetCfg[04] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_configuration }; // Configure EP0I.
    romSetCfg[05] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b1,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0011 // FFOSZ
                                        }
                    };
    romSetCfg[06] = { 1'b1, 1'b0, 8'hxx, `Write_endpoint_1_configuration }; // Configure EP1I.
    romSetCfg[07] = { 1'b0, 1'b0, 8'h00,  {
                                          1'b1,   // FIFOEN
                                          1'b1,   // EPDIR
                                          1'b0,   // DBLBUF
                                          1'b0,   // FFOISO
                                          4'b0011 // FFOSZ
                                        }
                    };
    romSetCfg[08] = { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer }; // Send an empty packet.
    romSetCfg[09] = { 1'b0, 1'b0, 16'h0000 };
    romSetCfg[10] = { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer };
    romSetCfg[11] = { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer };
    romSetCfg[12] = { 1'b1, 1'b1, 16'hxxxx }; // End.
  end
`endif
`ifndef ALDEC
  localparam [17:0] romSetCfg [0:12] =
  '{
    //  Cmd,  Rd,   Data
      { 1'b1, 1'b0, 8'hxx, `Acknowledge_set_up },
      { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
      { 1'b1, 1'b0, 8'hxx, `Write_control_OUT_configuration }, // Configure EP0O.
      { 1'b0, 1'b0, 8'h00,  {
                            1'b1,   // FIFOEN
                            1'b0,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0011 // FFOSZ
                          }
      },
      { 1'b1, 1'b0, 8'hxx, `Write_control_IN_configuration }, // Configure EP0I.
      { 1'b0, 1'b0, 8'h00,  {
                            1'b1,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0011 // FFOSZ
                          }
      },
      { 1'b1, 1'b0, 8'hxx, `Write_endpoint_1_configuration }, // Configure EP1I.
      { 1'b0, 1'b0, 8'h00,  {
                            1'b1,   // FIFOEN
                            1'b1,   // EPDIR
                            1'b0,   // DBLBUF
                            1'b0,   // FFOISO
                            4'b0011 // FFOSZ
                          }
      },
      { 1'b1, 1'b0, 8'hxx, `Write_control_IN_buffer }, // Send an empty packet.
      { 1'b0, 1'b0, 16'h0000 },
      { 1'b1, 1'b0, 8'hxx, `Validate_control_IN_buffer },
      { 1'b1, 1'b0, 8'hxx, `Clear_control_OUT_buffer },
      { 1'b1, 1'b1, 16'hxxxx }  // End.
  };
`endif
