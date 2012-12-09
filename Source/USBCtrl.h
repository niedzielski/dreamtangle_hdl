/*******************************************************************************
DreamTangle_HDL
Stephen Niedzielski - sniedzie@digipen.edu
*******************************************************************************/


// LVR.
`define USB_ID_Vendor  16'h0925
`define USB_ID_Product 16'h1234

// Universal Serial Bus Specification, Revision 2.0, April 27, 2000, Standard
// Request Codes, table 9-4, page 251.
`define USB_SR_GET_STATUS         8'h00
`define USB_SR_CLEAR_FEATURE      8'h01
`define USB_SR_SET_FEATURE        8'h03
`define USB_SR_SET_ADDRESS        8'h05
`define USB_SR_GET_DESCRIPTOR     8'h06
`define USB_SR_SET_DESCRIPTOR     8'h07
`define USB_SR_GET_CONFIGURATION  8'h08
`define USB_SR_SET_CONFIGURATION  8'h09
`define USB_SR_GET_INTERFACE      8'h0A
`define USB_SR_SET_INTERFACE      8'h0B
`define USB_SR_SYNCH_FRAME        8'h0C

// Universal Serial Bus Specification, Revision 2.0, April 27, 2000, Descriptor
// Types, table 9-5, page 251.
`define USB_SD_DEVICE         8'h01
`define USB_SD_CONFIGURATION  8'h02
`define USB_SD_STRING         8'h03
`define USB_SD_INTERFACE      8'h04
`define USB_SD_ENDPOINT       8'h05

// Universal Serial Bus Specification, Revision 2.0, April 27, 2000, PID types,
// table 8-1, page 196.
`define USB_PID_TOKEN_OUT   8'h01
`define USB_PID_TOKEN_IN    8'h09
`define USB_PID_TOKEN_SOF   8'h05
`define USB_PID_TOKEN_SETUP 8'h0D

// Universal Serial Bus Specification, Revision 2.0, April 27, 2000, Standard
// Endpoint Descriptor, table 9-13, page 269.  Where n is endpoint 0 to 15.
`define EPnO_Address(n) 8'(8'h00 + n)
`define EPnI_Address(n) 8'(8'h80 + n)
