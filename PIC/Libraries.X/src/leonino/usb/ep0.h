#include "usb.h"

#ifndef EP0_H
#define EP0_H
#define EP0_MAX_PACKET_SIZE			0x40
#define EP0_OUT_BUFFER_ADDRESS		0x0500
#define EP0_IN_BUFFER_ADDRESS		(EP0_OUT_BUFFER_ADDRESS + EP0_MAX_PACKET_SIZE)

#define GET_STATUS			0x00
#define GET_DESCRIPTOR                  0x06
#define SET_ADDRESS			0x05
#define SET_CONFIGURATION               0x09
#define GET_INTERFACE                   0x0A
#define SET_INTERFACE                   0x0B

void ep0_handle_setup_transaction();
void ep0_handle_standard_device();
void ep0_entry_point(unsigned char ustat);
void ep0_configure();

void ep0_in_handler_prepare_to_send_descriptor();
void ep0_in_handler_send_descriptor();
void ep0_out_handler_ack();
void ep0_in_handler_ack();
void ep0_in_handler_set_address();
void ep0_in_handler_configure();
#endif