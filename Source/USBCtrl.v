/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Created:   ~Friday, June 1, 2007 [Stephen Niedzielski]
// Modified:  Wednesday, October 31, 2007 [Stephen Niedzielski]
module USB
(
  input         iClk,
  input         iDly_,
  
  // FIFO lines.
  input         iGo,
  input [15:0]  iD,
  input [6:0]   iCnt,
  output        oPop,
  output        oDone,

  // ISP1362 lines.
  input         iClk200,
  input         iINT2,
  inout [15:0]  ioD,
  output        oRESET_,
  output [1:0]  oA,
  output        oRD_,
  output        oWR_,
  output        oCS_,
  output        oOTG_DP1,
  output        oOTG_DM1,
  
  output [15:0] oDbg
);
  `include "romUSB.h"
  `include "ISP1362Ctrl.h"
  `include "USBCtrl.h"


  reg [23:0] _ISR;
  initial
    _ISR = 24'h00_0000;
  reg
  _Stall,
  _Init,
  _GetDevice,
  _SetAdr,
  _GetCfg,
  _GetReport,
  _String0,
  _String1,
  _String2,
  _SetCfg,
  _User,
  _Go,
  _Done,
  _INT2;
  initial
  begin
    _Stall      = 1'b0;
    _Init       = 1'b1;
    _GetDevice  = 1'b0;
    _SetAdr     = 1'b0;
    _GetCfg     = 1'b0;
    _GetReport  = 1'b0;
    _String0    = 1'b0;
    _String1    = 1'b0;
    _String2    = 1'b0;
    _SetCfg     = 1'b0;
    _User       = 1'b0;
    _Go         = 1'b0;
    _INT2       = 1'b0;
    _Done       = 1'b0;
  end
  reg [7:0]
  _EP0OS,
  _EP0IS,
  _EP1IS;
  initial
  begin
    _EP0OS = 8'h00;
    _EP0IS = 8'h00;
    _EP1IS = 8'h00;
  end
  
  reg [15:0] _ISP_Q_Buf;
  initial
    _ISP_Q_Buf = 16'h0000;
  
  reg [15:0] _ISP_D;
  initial
    _ISP_D = 16'h0000;  
  reg
  _ISP_Rd,
  _ISP_Cmd,
  _ISP_Go;
  initial
  begin
    _ISP_Rd   = 1'b0;
    _ISP_Cmd  = 1'b0;
    _ISP_Go   = 1'b0;
  end
  wire ISP_Done;
  wire [15:0] ISP_Q;

  reg [6:0] _Cnt;
  initial _Cnt = 6'd0;
    
  reg [15:0] _Dbg;
  initial _Dbg = 16'h1234;

  assign oDbg = _Dbg;
  
  reg [7:0] _UserCnt;
  initial _UserCnt = 6'hxx;
    
  reg _Pop;
  initial _Pop = 1'b0;
  assign oPop = _Pop;
  
  assign oDone = _Done;
    
  ISP1362Ctrl
  ISP1362Ctrl0
  (
    // Intermodule lines.
    .iClk200( iClk200 ),
    .iRead( _ISP_Rd ),
    .iCmd( _ISP_Cmd ),
    .iD( _ISP_D ),
    .iGo( _ISP_Go ),
    .oDone( ISP_Done ),
    .oQ( ISP_Q ),

    // ISP1362 lines.
    .ioD( ioD ),
    .oRESET_( oRESET_ ),
    .oA( oA ),
    .oRD_( oRD_ ),
    .oWR_( oWR_ ),
    .oCS_( oCS_ ),
    .oOTG_DP1( oOTG_DP1 ),
    .oOTG_DM1( oOTG_DM1 )
  );

  always_ff @( posedge iClk )
  begin
    // Defaults.
    _ISP_Go   <= 1'b0;
    _Pop <= 1'b0;
    _Done <= 1'b1;

    if( iGo || _Go || _User )
      _Done <= 1'b0;
    
    if( iGo )
    begin
      _Go       <= 1'b1;
      _UserCnt  <= iCnt;
    end
    
    if( ISP_Done && iDly_ )
    begin
      priority case( 1'b1 )

        _Stall:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romStall[_Cnt][romCmd] && romStall[_Cnt][romRd] )
          begin
            _Stall    <= 1'b0;
            _Cnt      <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romStall[_Cnt][romD:0];
            _ISP_Rd   <= romStall[_Cnt][romRd];
            _ISP_Cmd  <= romStall[_Cnt][romCmd];
          end
        end
        
        _ISR[0], // Reset.
        _Init:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          // Initialize status registers.
          _ISR              <= 24'd0;
          _Init             <= 1'b1; // In case in this state because _ISR[0] reset.
          _EP0OS            <= 8'd0;
          _EP0IS            <= 8'd0;
          _EP1IS            <= 8'd0;
          
          if( romInit[_Cnt][romCmd] && romInit[_Cnt][romRd] )
          begin
            _Init <= 1'b0;
            _Cnt  <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romInit[_Cnt][romD:0];
            _ISP_Rd   <= romInit[_Cnt][romRd];
            _ISP_Cmd  <= romInit[_Cnt][romCmd];
          end
        end
        
        _GetDevice:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romGetDevice[_Cnt][romCmd] && romGetDevice[_Cnt][romRd] )
          begin
            _GetDevice <= 1'b0;
            _Cnt   <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romGetDevice[_Cnt][romD:0];
            _ISP_Rd   <= romGetDevice[_Cnt][romRd];
            _ISP_Cmd  <= romGetDevice[_Cnt][romCmd];
          end
        end
    
        _SetAdr:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romSetAdr[_Cnt][romCmd] && romSetAdr[_Cnt][romRd] )
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= { 8'h00, { 1'b1,       // DEVEN
                                    ISP_Q[6:0]  // DEVADR
                                  }
                         };
            _ISP_Rd   <= 1'b0;
            _ISP_Cmd  <= 1'b0;
  
            _SetAdr <= 1'b0;
            _Cnt  <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romSetAdr[_Cnt][romD:0];
            _ISP_Rd   <= romSetAdr[_Cnt][romRd];
            _ISP_Cmd  <= romSetAdr[_Cnt][romCmd];
          end
        end
  
        _GetCfg:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          case( _Cnt )
            0:
            begin
              // Skip 2 bytes.
              _ISP_Go   <= 1'b1;
              _ISP_Rd   <= 1'b1;
              _ISP_Cmd  <= 1'b0;
            end
            1:
            begin
              // Get the requested length.
              _ISP_Go   <= 1'b1;
            end
            2:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Acknowledge_set_up };
              _ISP_Rd   <= 1'b0;
              _ISP_Cmd  <= 1'b1;
            end
            3:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Clear_control_OUT_buffer };
            end
            4:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Write_control_IN_buffer };
            end
            5:
            begin
              // Write the length of the packet.
              _ISP_Go   <= 1'b1;
              _ISP_D    <= (ISP_Q[7:0] < 35)
                         ? {8'h00, ISP_Q[7:0]}
                         : 16'd34;
              _ISP_Cmd  <= 1'b0;
            end
            default:
            begin
              // Write the packet.
              if( romGetCfg[_Cnt - 3'd6][romCmd] && romGetCfg[_Cnt - 3'd6][romRd] )
              begin
                _GetCfg <= 1'b0;
                _Cnt   <= 6'd0;
              end
              else
              begin
                _ISP_Go   <= 1'b1;
                _ISP_D    <= romGetCfg[_Cnt - 3'd6][romD:0];
                _ISP_Rd   <= romGetCfg[_Cnt - 3'd6][romRd];
                _ISP_Cmd  <= romGetCfg[_Cnt - 3'd6][romCmd];
              end
            end
          endcase
        end
        
        _GetReport:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romGetReport[_Cnt][romCmd] && romGetReport[_Cnt][romRd] )
          begin
            _GetReport <= 1'b0;
            _Cnt   <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romGetReport[_Cnt][romD:0];
            _ISP_Rd   <= romGetReport[_Cnt][romRd];
            _ISP_Cmd  <= romGetReport[_Cnt][romCmd];
          end
        end
              
        _String0:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romString0[_Cnt][romCmd] && romString0[_Cnt][romRd] )
          begin
            _String0 <= 1'b0;
            _Cnt   <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romString0[_Cnt][romD:0];
            _ISP_Rd   <= romString0[_Cnt][romRd];
            _ISP_Cmd  <= romString0[_Cnt][romCmd];
          end
        end
  
        _String1:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romString1[_Cnt][romCmd] && romString1[_Cnt][romRd] )
          begin
            _String1 <= 1'b0;
            _Cnt <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romString1[_Cnt][romD:0];
            _ISP_Rd   <= romString1[_Cnt][romRd];
            _ISP_Cmd  <= romString1[_Cnt][romCmd];
          end
        end
  
        _String2:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romString2[_Cnt][romCmd] && romString2[_Cnt][romRd] )
          begin
            _String2 <= 1'b0;
            _Cnt   <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romString2[_Cnt][romD:0];
            _ISP_Rd   <= romString2[_Cnt][romRd];
            _ISP_Cmd  <= romString2[_Cnt][romCmd];
          end
        end
  
        _SetCfg:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          if( romSetCfg[_Cnt][romCmd] && romSetCfg[_Cnt][romRd] )
          begin
            _SetCfg <= 1'b0;
            _Cnt   <= 6'd0;
          end
          else
          begin
            _ISP_Go   <= 1'b1;
            _ISP_D    <= romSetCfg[_Cnt][romD:0];
            _ISP_Rd   <= romSetCfg[_Cnt][romRd];
            _ISP_Cmd  <= romSetCfg[_Cnt][romCmd];
          end
        end
  
        |_ISR[10:8]: // Update endpoint status register.
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          unique case( _Cnt )
            0:
            begin
              _ISP_Go   <= 1'b1;
              priority case( 1'b1 )
                _ISR[8]:  _ISP_D <= { 8'hxx, `Read_control_OUT_status };
                _ISR[9]:  _ISP_D <= { 8'hxx, `Read_control_IN_status };
                default:  _ISP_D <= { 8'hxx, `Read_endpoint_1_status };
              endcase
              _ISP_Rd   <= 1'b0;
              _ISP_Cmd  <= 1'b1;
            end
            1:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_Rd   <= 1'b1;
              _ISP_Cmd  <= 1'b0;
            end
            2:
            begin             
              // Store the status.
              priority case( 1'b1 )
                _ISR[8]:  _EP0OS <= ISP_Q[7:0];
                _ISR[9]:  _EP0IS <= ISP_Q[7:0];
                default:  _EP1IS <= ISP_Q[7:0];
              endcase
  
              // Drop out of this state.
              priority case( 1'b1 )
                _ISR[8]:  _ISR[8] <= 1'b0;
                _ISR[9]:  _ISR[9] <= 1'b0;
                default:  _ISR[10] <= 1'b0;
              endcase
              
              _Cnt <= 6'd0;
            end
          endcase
        end
        
        _EP0OS[3]: // OVERWRITE
        begin
          // Update _EP0OS and drop out.
          _ISR[8]   <= 1'b1;
        end

        // EP0O Setup packet.
        _EP0OS[6] ||  // EPFULL1
        _EP0OS[5] ||  // EPFULL0
        _EP0OS[2]:    // SETUPT
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          case( _Cnt )
            0:
            begin
              // Request to read EP0O buffer.
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Read_control_OUT_buffer };
              _ISP_Rd   <= 1'b0;
              _ISP_Cmd  <= 1'b1;
            end
            1,2:
            begin
              // Read four bytes, throw away first two.
              _ISP_Go   <= 1'b1;
              _ISP_Rd   <= 1'b1;
              _ISP_Cmd  <= 1'b0;
            end
            3:
            begin
              // Save last two bytes, get next two.
              _ISP_Q_Buf  <= ISP_Q;
              _ISP_Go     <= 1'b1;
              _ISP_Rd     <= 1'b1;
            end
            4:
            begin
              case( _ISP_Q_Buf )
                16'h0680: casez( ISP_Q )
                            16'h01??: _GetDevice  <= 1'b1;
                            16'h02??: _GetCfg     <= 1'b1;
                            16'h0300: _String0    <= 1'b1;
                            16'h0301: _String1    <= 1'b1;
                            16'h0302: _String2    <= 1'b1;
                            default:  _Stall      <= 1'b1; // Request not supported.
                          endcase
                16'h0681: _GetReport  <= 1'b1;
                16'h0900: _SetCfg     <= 1'b1;
                16'h0500: _SetAdr     <= 1'b1;
                default:  _Stall      <= 1'b1; // Request not supported.
              endcase

              // Update _EP0OS and drop out.
              _ISR[8] <= 1'b1;
              _Cnt    <= 6'd0;
            end
          endcase
        end
  
        _User:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          unique case( _Cnt )
            0:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Write_endpoint_1_buffer };
              _ISP_Rd   <= 1'b0;
              _ISP_Cmd  <= 1'b1;
            end
            1:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_D    <= _UserCnt << 1; // Multiply by two for sixteen bit wide FIFO.
              _ISP_Cmd  <= 1'b0;
            end
            2:
            begin
              if( _UserCnt != 0 )
              begin
                // Stay in this state.
                _Cnt      <= _Cnt;

                _UserCnt  <= _UserCnt - 1'd1;
                _Pop      <= 1'b1;
                _ISP_Go   <= 1'b1;
                _ISP_D    <= iD;
              end
            end
            3:
            begin
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Validate_endpoint_1_buffer };
              _ISP_Cmd  <= 1'b1;

              _ISR[8]   <= 1'b1;
              _INT2     <= 1'b1;
              
              _Cnt      <= 6'd0;
              _User     <= 1'b0;
            end
          endcase
        end
        
        iINT2,
        _INT2:
        begin
          // Defaults.
          _Cnt <= _Cnt + 1'd1;

          case( _Cnt )
            0:
            begin
              // Keep in this machine.
              _INT2 <= 1'b1;
      
              _ISP_Go   <= 1'b1;
              _ISP_D    <= { 8'hxx, `Read_DcInterrupt_register };
              _ISP_Rd   <= 1'b0;
              _ISP_Cmd  <= 1'b1;
            end
            1:
            begin
              // Read two bytes.
              _ISP_Go   <= 1'b1;
              _ISP_Rd   <= 1'b1;
              _ISP_Cmd  <= 1'b0;
            end
            2:
            begin
              // Store the low word.
              _ISR[15:0] <= ISP_Q;
  
              // Read two bytes.
              _ISP_Go   <= 1'b1;
              _ISP_Rd   <= 1'b1;
            end
            3:
            begin
              // Store the high byte.
              _ISR[23:16] <= ISP_Q[7:0];
  
              _INT2 <= 1'b0;
              _Cnt  <= 6'd0;
            end
          endcase
        end
        
        _Go: // Request to send user packet.
        begin
          // Note: This system prevents iINT2 from being interrupted by a user packet.
          // Send user packet.
          _User <= 1'b1;
          _Go   <= 1'b0;
        end

        default: // Poll EP0O status.
        begin
          // For some reason the interrupt is not triggering on its own for
          // packets.  As such, EP0O is polled whenever the module is idle.
          _ISR[8] <= 1'b1;
        end
        
      endcase
    end // if( ISP_Done && iDly_ )
  end // always_ff @( posedge iClk )

endmodule
