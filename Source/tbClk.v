/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/

`include "Global.h"


// Testbench clock module.  Generates a clock signal for simulation.
// Created:   ~Friday, June 1, 2007 [Stephen Niedzielski]
// Modified:  Saturday, September 8, 2007 [Stephen Niedzielski]
module tbClk
#(
  // Defined in kilohertz to avoid constant overflow.
  parameter Timescale_kHz = 1_000_000_000, // `timescale used.
            Frequency_kHz = 0              // Desired output frequency.
)
(
  output reg _oClk
);

  initial
  begin
    _oClk = 0;
  end

  localparam Ticks = $unsigned( ( Timescale_kHz / (2 * Frequency_kHz)) );

  always
  begin
    #Ticks _oClk <= ~_oClk;
  end

endmodule
