/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/


// ISP1362 Product Data Sheet, Rev. 05, May 8, 2007, Initialization Commands,
// table 108, pages 106 - 107.
//      Command                           Code          Data Bytes  Read / Write
`define Write_control_OUT_configuration   8'h20         // 1        W
`define Write_control_IN_configuration    8'h21         // 1        W
`define Write_endpoint_1_configuration    8'h22         // 1        W
`define Write_endpoint_2_configuration    8'h23         // 1        W
`define Write_endpoint_3_configuration    8'h24         // 1        W
`define Write_endpoint_4_configuration    8'h25         // 1        W
`define Write_endpoint_5_configuration    8'h26         // 1        W
`define Write_endpoint_6_configuration    8'h27         // 1        W
`define Write_endpoint_7_configuration    8'h28         // 1        W
`define Write_endpoint_8_configuration    8'h29         // 1        W
`define Write_endpoint_9_configuration    8'h2A         // 1        W
`define Write_endpoint_10_configuration   8'h2B         // 1        W
`define Write_endpoint_11_configuration   8'h2C         // 1        W
`define Write_endpoint_12_configuration   8'h2D         // 1        W
`define Write_endpoint_13_configuration   8'h2E         // 1        W
`define Write_endpoint_14_configuration   8'h2F         // 1        W
`define Read_control_OUT_configuration    8'h30         // 1        R
`define Read_control_IN_configuration     8'h31         // 1        R
`define Read_endpoint_1_configuration     8'h32         // 1        R
`define Read_endpoint_2_configuration     8'h33         // 1        R
`define Read_endpoint_3_configuration     8'h34         // 1        R
`define Read_endpoint_4_configuration     8'h35         // 1        R
`define Read_endpoint_5_configuration     8'h36         // 1        R
`define Read_endpoint_6_configuration     8'h37         // 1        R
`define Read_endpoint_7_configuration     8'h38         // 1        R
`define Read_endpoint_8_configuration     8'h39         // 1        R
`define Read_endpoint_9_configuration     8'h3A         // 1        R
`define Read_endpoint_10_configuration    8'h3B         // 1        R
`define Read_endpoint_11_configuration    8'h3C         // 1        R
`define Read_endpoint_12_configuration    8'h3D         // 1        R
`define Read_endpoint_13_configuration    8'h3E         // 1        R
`define Read_endpoint_14_configuration    8'h3F         // 1        R
`define Write_device_address              8'hB6         // 1        W
`define Read_device_address               8'hB7         // 1        R
`define Write_Mode_register               8'hB8         // 1        W
`define Read_Mode_register                8'hB9         // 1        R
`define Write_hardware_configuration      8'hBA         // 1        W
`define Read_hardware_configuration       8'hBB         // 1        R
`define Write_DcInterruptEnable_register  8'hC2         // 4        W
`define Read_DcInterruptEnable_register   8'hC3         // 4        R
`define Write_DMA_configuration           8'hF0         // 2        W
`define Read_DMA_configuration            8'hF1         // 2        R
`define Write_DMA_counter                 8'hF2         // 2        W
`define Read_DMA_counter                  8'hF3         // 2        R
`define Reset_device                      8'hF6         // 0

// ISP1362 Product Data Sheet, Rev. 05, May 8, 2007, Data Flow Commands, table
// 108, page 107.
//      Command                           Code          Data Bytes  Read / Write
`define Write_control_IN_buffer           8'h01         // <= 64    W
`define Write_endpoint_1_buffer           8'h02         // <= 1023  W
`define Write_endpoint_2_buffer           8'h03         // <= 1023  W
`define Write_endpoint_3_buffer           8'h04         // <= 1023  W
`define Write_endpoint_4_buffer           8'h05         // <= 1023  W
`define Write_endpoint_5_buffer           8'h06         // <= 1023  W
`define Write_endpoint_6_buffer           8'h07         // <= 1023  W
`define Write_endpoint_7_buffer           8'h08         // <= 1023  W
`define Write_endpoint_8_buffer           8'h09         // <= 1023  W
`define Write_endpoint_9_buffer           8'h0A         // <= 1023  W
`define Write_endpoint_10_buffer          8'h0B         // <= 1023  W
`define Write_endpoint_11_buffer          8'h0C         // <= 1023  W
`define Write_endpoint_12_buffer          8'h0D         // <= 1023  W
`define Write_endpoint_13_buffer          8'h0E         // <= 1023  W
`define Write_endpoint_14_buffer          8'h0F         // <= 1023  W
`define Read_control_OUT_buffer           8'h10         // <= 64    R
`define Read_endpoint_1_buffer            8'h12         // <= 1023  R
`define Read_endpoint_2_buffer            8'h13         // <= 1023  R
`define Read_endpoint_3_buffer            8'h14         // <= 1023  R
`define Read_endpoint_4_buffer            8'h15         // <= 1023  R
`define Read_endpoint_5_buffer            8'h16         // <= 1023  R
`define Read_endpoint_6_buffer            8'h17         // <= 1023  R
`define Read_endpoint_7_buffer            8'h18         // <= 1023  R
`define Read_endpoint_8_buffer            8'h19         // <= 1023  R
`define Read_endpoint_9_buffer            8'h1A         // <= 1023  R
`define Read_endpoint_10_buffer           8'h1B         // <= 1023  R
`define Read_endpoint_11_buffer           8'h1C         // <= 1023  R
`define Read_endpoint_12_buffer           8'h1D         // <= 1023  R
`define Read_endpoint_13_buffer           8'h1E         // <= 1023  R
`define Read_endpoint_14_buffer           8'h1F         // <= 1023  R
`define Stall_control_OUT_endpoint        8'h40         // 0
`define Stall_control_IN_endpoint         8'h41         // 0
`define Stall_endpoint_1                  8'h42         // 0
`define Stall_endpoint_2                  8'h43         // 0
`define Stall_endpoint_3                  8'h44         // 0
`define Stall_endpoint_4                  8'h45         // 0
`define Stall_endpoint_5                  8'h46         // 0
`define Stall_endpoint_6                  8'h47         // 0
`define Stall_endpoint_7                  8'h48         // 0
`define Stall_endpoint_8                  8'h49         // 0
`define Stall_endpoint_9                  8'h4A         // 0
`define Stall_endpoint_10                 8'h4B         // 0
`define Stall_endpoint_11                 8'h4C         // 0
`define Stall_endpoint_12                 8'h4D         // 0
`define Stall_endpoint_13                 8'h4E         // 0
`define Stall_endpoint_14                 8'h4F         // 0
`define Read_control_OUT_status           8'h50         // 1        R
`define Read_control_IN_status            8'h51         // 1        R
`define Read_endpoint_1_status            8'h52         // 1        R
`define Read_endpoint_2_status            8'h53         // 1        R
`define Read_endpoint_3_status            8'h54         // 1        R
`define Read_endpoint_4_status            8'h55         // 1        R
`define Read_endpoint_5_status            8'h56         // 1        R
`define Read_endpoint_6_status            8'h57         // 1        R
`define Read_endpoint_7_status            8'h58         // 1        R
`define Read_endpoint_8_status            8'h59         // 1        R
`define Read_endpoint_9_status            8'h5A         // 1        R
`define Read_endpoint_10_status           8'h5B         // 1        R
`define Read_endpoint_11_status           8'h5C         // 1        R
`define Read_endpoint_12_status           8'h5D         // 1        R
`define Read_endpoint_13_status           8'h5E         // 1        R
`define Read_endpoint_14_status           8'h5F         // 1        R
`define Validate_control_IN_buffer        8'h61         // 0
`define Validate_endpoint_1_buffer        8'h62         // 0
`define Validate_endpoint_2_buffer        8'h63         // 0
`define Validate_endpoint_3_buffer        8'h64         // 0
`define Validate_endpoint_4_buffer        8'h65         // 0
`define Validate_endpoint_5_buffer        8'h66         // 0
`define Validate_endpoint_6_buffer        8'h67         // 0
`define Validate_endpoint_7_buffer        8'h68         // 0
`define Validate_endpoint_8_buffer        8'h69         // 0
`define Validate_endpoint_9_buffer        8'h6A         // 0
`define Validate_endpoint_10_buffer       8'h6B         // 0
`define Validate_endpoint_11_buffer       8'h6C         // 0
`define Validate_endpoint_12_buffer       8'h6D         // 0
`define Validate_endpoint_13_buffer       8'h6E         // 0
`define Validate_endpoint_14_buffer       8'h6F         // 0
`define Clear_control_OUT_buffer          8'h70         // 0
`define Clear_endpoint_1_buffer           8'h72         // 0
`define Clear_endpoint_2_buffer           8'h73         // 0
`define Clear_endpoint_3_buffer           8'h74         // 0
`define Clear_endpoint_4_buffer           8'h75         // 0
`define Clear_endpoint_5_buffer           8'h76         // 0
`define Clear_endpoint_6_buffer           8'h77         // 0
`define Clear_endpoint_7_buffer           8'h78         // 0
`define Clear_endpoint_8_buffer           8'h79         // 0
`define Clear_endpoint_9_buffer           8'h7A         // 0
`define Clear_endpoint_10_buffer          8'h7B         // 0
`define Clear_endpoint_11_buffer          8'h7C         // 0
`define Clear_endpoint_12_buffer          8'h7D         // 0
`define Clear_endpoint_13_buffer          8'h7E         // 0
`define Clear_endpoint_14_buffer          8'h7F         // 0
`define Unstall_control_OUT_endpoint      8'h80         // 0
`define Unstall_control_IN_endpoint       8'h81         // 0
`define Unstall_endpoint_1                8'h82         // 0
`define Unstall_endpoint_2                8'h83         // 0
`define Unstall_endpoint_3                8'h84         // 0
`define Unstall_endpoint_4                8'h85         // 0
`define Unstall_endpoint_5                8'h86         // 0
`define Unstall_endpoint_6                8'h87         // 0
`define Unstall_endpoint_7                8'h88         // 0
`define Unstall_endpoint_8                8'h89         // 0
`define Unstall_endpoint_9                8'h8A         // 0
`define Unstall_endpoint_10               8'h8B         // 0
`define Unstall_endpoint_11               8'h8C         // 0
`define Unstall_endpoint_12               8'h8D         // 0
`define Unstall_endpoint_13               8'h8E         // 0
`define Unstall_endpoint_14               8'h8F         // 0
`define Check_control_OUT_status          8'hD0         // 1        R
`define Check_control_IN_status           8'hD1         // 1        R
`define Check_endpoint_1_status           8'hD2         // 1        R
`define Check_endpoint_2_status           8'hD3         // 1        R
`define Check_endpoint_3_status           8'hD4         // 1        R
`define Check_endpoint_4_status           8'hD5         // 1        R
`define Check_endpoint_5_status           8'hD6         // 1        R
`define Check_endpoint_6_status           8'hD7         // 1        R
`define Check_endpoint_7_status           8'hD8         // 1        R
`define Check_endpoint_8_status           8'hD9         // 1        R
`define Check_endpoint_9_status           8'hDA         // 1        R
`define Check_endpoint_10_status          8'hDB         // 1        R
`define Check_endpoint_11_status          8'hDC         // 1        R
`define Check_endpoint_12_status          8'hDD         // 1        R
`define Check_endpoint_13_status          8'hDE         // 1        R
`define Check_endpoint_14_status          8'hDF         // 1        R
`define Acknowledge_set_up                8'hF4         // 0

// ISP1362 Product Data Sheet, Rev. 05, May 8, 2007, General Commands, table
// 108, page 108.  Where n is endpoint 1 to 15.
//      Command                           Code          Data Bytes  Read / Write
`define Read_control_OUT_error_code       8'hA0         // 1        R
`define Read_control_IN_error_code        8'hA1         // 1        R
`define Read_endpoint_1_error_code        8'hA2         // 1        R
`define Read_endpoint_2_error_code        8'hA3         // 1        R
`define Read_endpoint_3_error_code        8'hA4         // 1        R
`define Read_endpoint_4_error_code        8'hA5         // 1        R
`define Read_endpoint_5_error_code        8'hA6         // 1        R
`define Read_endpoint_6_error_code        8'hA7         // 1        R
`define Read_endpoint_7_error_code        8'hA8         // 1        R
`define Read_endpoint_8_error_code        8'hA9         // 1        R
`define Read_endpoint_9_error_code        8'hAA         // 1        R
`define Read_endpoint_10_error_code       8'hAB         // 1        R
`define Read_endpoint_11_error_code       8'hAC         // 1        R
`define Read_endpoint_12_error_code       8'hAD         // 1        R
`define Read_endpoint_13_error_code       8'hAE         // 1        R
`define Read_endpoint_14_error_code       8'hAF         // 1        R
`define Unlock_device                     8'hB0         // 2        W
`define Write_DcScratch_register          8'hB2         // 2        W
`define Read_DcScratch_register           8'hB3         // 2        R
`define Read_frame_number                 8'hB4         // 1 or 2?  R
`define Read_chip_ID                      8'hB5         // 2        R
`define Read_DcInterrupt_register         8'hC0         // 4        R