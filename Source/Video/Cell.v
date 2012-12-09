module Cell
(
  input        iClk27,
  input        iEn,
  input [8:0]  iRGB,
  output [8:0] oA,
  output [8:0] oB,
  output [8:0] oC,
  output [8:0] oD,
  output [8:0] oE,
  output [8:0] oF,
  output [8:0] oG,
  output [8:0] oH,
  output [8:0] oI
);

  reg [35:0] _Line0D;
  initial _Line0D = 36'hx_xxxx_xxxx;
  reg [3:0] _Line0ClkEn;
  initial _Line0ClkEn = 4'b1000;

  wire [35:0]
  Line0Q,
  Line1Q;

  assign
  oA = _Line0D[9 * 3 +: 9],
  oB = _Line0D[9 * 2 +: 9],
  oC = _Line0D[9 * 1 +: 9],
  oD = Line0Q[9 * 3 +: 9],
  oE = Line0Q[9 * 2 +: 9],
  oF = Line0Q[9 * 1 +: 9],
  oG = Line1Q[9 * 3 +: 9],
  oH = Line1Q[9 * 2 +: 9],
  oI = Line1Q[9 * 1 +: 9];

  always_ff @( posedge iClk27 )
    if( iEn )
    begin
      _Line0ClkEn <= { _Line0ClkEn[0], _Line0ClkEn[3:1] };
      _Line0D <= { iRGB, _Line0D[35:9] };
    end

  Line
  Line0
  (
    .clken( _Line0ClkEn[0] ),
    .clock( iClk27 ),
    .shiftin( _Line0D ),
    .shiftout( Line0Q ),
    .taps(  )
  );
  Line
  Line1
  (
    .clken( _Line0ClkEn[0] ),
    .clock( iClk27 ),
    .shiftin( Line0Q ),
    .shiftout( Line1Q ),
    .taps(  )
  );

endmodule
