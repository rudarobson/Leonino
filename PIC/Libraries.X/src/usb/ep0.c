#include <htc.h>
#include "usb.h"
#include "ep0.h"
#include "ep1.h"
#include "ep2.h"
#include "descriptor.h"

#ifndef EP0_C
#define EP0_C

BDENTRY ep0_out_bd @ BD_ADDRESS_OUT(0);
usb_handler_t ep0_out_handler;
unsigned char ep0_out_buffer[EP0_MAX_PACKET_SIZE] @ EP0_OUT_BUFFER_ADDRESS;

BDENTRY ep0_in_bd @ BD_ADDRESS_IN(0);
unsigned char ep0_in_buffer[EP0_MAX_PACKET_SIZE]@ EP0_IN_BUFFER_ADDRESS;
usb_handler_t ep0_in_handler;

unsigned char *ep0_in_decsriptor;
unsigned int ep0_in_total_bytes_sent;
unsigned int ep0_in_total_bytes_to_send;
unsigned int ep0_in_total_bytes_sent_on_last_transfer;

unsigned char ep0_last_data_bit;
unsigned char ep0_bdstat;
unsigned char ep0_dir;
unsigned char ep0_temp_uaddr;

void ep0_configure() {
    UEP0 = UEP_EPHSHK | UEP_EPINEN | UEP_EPOUTEN;
    ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
    ep0_out_bd.BDADDRL = LOW_BYTE(EP0_OUT_BUFFER_ADDRESS);
    ep0_out_bd.BDADDRH = HIGH_BYTE(EP0_OUT_BUFFER_ADDRESS);
    ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for data 0

    ep0_in_bd.BDCNT = 0;
    ep0_in_bd.BDADDRL = LOW_BYTE(EP0_IN_BUFFER_ADDRESS);
    ep0_in_bd.BDADDRH = HIGH_BYTE(EP0_IN_BUFFER_ADDRESS);
    ep0_in_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
}

void ep0_handle_setup_transaction() {
    unsigned int desc_len;

    switch (bRequest(ep0_out_buffer)) {
        case GET_STATUS://return two bytes


            //log_id(DEBUG_CONST_GETSTATUS, bmRequestType_Recipient(ep0_out_buffer));
            switch (bmRequestType_Recipient(ep0_out_buffer)) {
                case bmRequestType_Recipient_Device:
                    ep0_in_buffer[0] = 0;
                    ep0_in_buffer[1] = 0;
                    break;
                case bmRequestType_Recipient_Interface:
                    ep0_in_buffer[0] = 0;
                    ep0_in_buffer[1] = 0;
                    break;
                case bmRequestType_Recipient_Endpoint:
                    ep0_in_buffer[0] = 0;
                    ep0_in_buffer[1] = 0;
                    break;
                default:
                    //log_id(DEBUG_CONST_NONE, DEBUG_CONST_NONE_bmrequestType_Recipient);
                    break;
            }
            ep0_in_handler = ep0_in_handler_ack;
            ep0_out_handler = ep0_out_handler_ack;

            ep0_in_bd.BDCNT = 2;
            ep0_in_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for out at status stage with data0
            break;
        case GET_DESCRIPTOR://return the descriptor
            //log_id(DEBUG_CONST_DESCRIPTOR, wValue_High(ep0_out_buffer));
            switch (wValue_High(ep0_out_buffer)) {
                case DESCRIPTOR_DEVICE_TYPE:
                    ep0_in_decsriptor = dev_desc;
                    desc_len = DESCRIPTOR_DEVICE_LENGTH;
                    break;
                case DESCRIPTOR_CONFIGURATION_TYPE:
                    ep0_in_decsriptor = conf_desc_0;
                    desc_len = DESCRIPTOR_CONFIGURATION_TOTAL_LENGTH;
                    break;
                case DESCRIPTOR_STRING_TYPE:
                    switch (wValue_Low(ep0_out_buffer)) {
                        case 0:
                            ep0_in_decsriptor = string_desc_0;
                            desc_len = DESCRIPTOR_STRING0_LENGTH;
                            break;
                        case 1:
                            ep0_in_decsriptor = string_desc_1;
                            desc_len = DESCRIPTOR_STRING1_LENGTH;
                            break;
                        case 2:
                            ep0_in_decsriptor = string_desc_2;
                            desc_len = DESCRIPTOR_STRING2_LENGTH;
                            break;
                        default:
                            //log_id(DEBUG_CONST_NONE, DEBUG_CONST_wValueLow);
                            //log_id(DEBUG_CONST_NONE, wValue_Low(ep0_out_buffer));
                            break;
                    }
                    break;
                default:
                    //log_id(DEBUG_CONST_NONE, DEBUG_CONST_NONE_wValue_High);
                    break;
            }
            ep0_in_total_bytes_sent = 0;
            ep0_in_total_bytes_sent_on_last_transfer = 0;
            ep0_in_total_bytes_to_send = MIN(wLength(ep0_out_buffer), desc_len);
            ep0_last_data_bit = 0; //prepare to wait a DATA1

            ep0_in_handler_prepare_to_send_descriptor();


            ep0_in_handler = ep0_in_handler_send_descriptor;
            ep0_out_handler = ep0_out_handler_ack;

            ep0_in_bd.BDSTAT = ep0_bdstat;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS; //wait for out at status stage with data1
            break;
        case SET_ADDRESS:
            //log_id(DEBUG_CONST_SETADDRESS, wValue_Low(ep0_out_buffer));
            ep0_temp_uaddr = wValue_Low(ep0_out_buffer);

            ep0_in_handler = ep0_in_handler_set_address; //remove possibly

            //no data stage
            ep0_in_bd.BDCNT = 0;
            ep0_in_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            //wait for setup
            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for setup
            break;
        case SET_CONFIGURATION:
            //log_id(DEBUG_CONST_SET_CONFIGURATION_DESCRIPTOR_INDEX, wValue_Low(ep0_out_buffer)); //log descriptor index
            if (wValue_Low(ep0_out_buffer) == 1) {
                ep0_in_handler = ep0_in_handler_configure;
                ep1_configure();
                ep2_configure();
                ep0_in_bd.BDCNT = 0;
                ep0_in_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

                ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
                ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for setup
            }
            break;
        case GET_INTERFACE:
            ep0_in_buffer[0] = 0; //only 1 interface

            ep0_in_bd.BDCNT = 1;
            ep0_in_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS; //wait for out status
            break;
        case SET_INTERFACE:
            ep0_in_bd.BDCNT = 0; //only 1 interface
            ep0_in_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for setup
            break;
        default:
            //log_id(DEBUG_CONST_NONE, DEBUG_CONST_NONE_bRequest);
            //log_id(DEBUG_CONST_NONE, bRequest(ep0_out_buffer));
            break;
    }

    UCONbits.PKTDIS = 0; //reenable setup
}

void ep0_handle_standard_device() {
    unsigned char pid;

    if (ep0_dir == TRANS_DIR_IN)
        pid = BDSTAT_PID(ep0_in_bd.BDSTAT);
    else
        pid = BDSTAT_PID(ep0_out_bd.BDSTAT);

    //log_id(DEBUG_CONST_PID, pid);

    switch (pid) {
        case PID_OUT:
            ep0_out_handler();
            break;
        case PID_IN:
            ep0_in_handler();
            break;
        case PID_SETUP:
            ep0_handle_setup_transaction();
            break;
        default:
            //log_id(DEBUG_CONST_NONE, DEBUG_CONST_NONE_PID);
            break;
    }
}

void ep0_entry_point(unsigned char ustat) {
    unsigned char bmRequestType;

    if (USTAT_DIRECTION(ustat) == TRANS_DIR_IN) {
        ep0_dir = TRANS_DIR_IN;
        bmRequestType = bmRequestType_Type(ep0_in_buffer);
    } else {
        ep0_dir = TRANS_DIR_OUT;
        bmRequestType = bmRequestType_Type(ep0_out_buffer);
    }

    switch (bmRequestType) {
        case bmRequestType_Standard:
            ep0_handle_standard_device();
            break;
        default:
            //log_id(DEBUG_CONST_NONE, DEBUG_CONST_NONE_bmRequestType);
            break;
    }

}

void ep0_in_handler_prepare_to_send_descriptor() {
    unsigned int num = MIN(ep0_in_total_bytes_to_send - ep0_in_total_bytes_sent, EP0_MAX_PACKET_SIZE);

    //if (num >= 0) {
    if (num > 0)
        ReadFlash(ep0_in_decsriptor + ep0_in_total_bytes_sent, num, ep0_in_buffer);

    ep0_in_bd.BDCNT = num;
    ep0_in_total_bytes_sent_on_last_transfer = num;
    if (ep0_last_data_bit == 1) {
        ep0_bdstat = BDSTAT_UOWN | BDSTAT_DTSEN;
        ep0_last_data_bit = 0;
    } else {
        ep0_bdstat = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
        ep0_last_data_bit = 1;
    }
    //    } else
    //        ep0_bdstat = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
}

void ep0_in_handler_send_descriptor() {
    ep0_in_total_bytes_sent += ep0_in_total_bytes_sent_on_last_transfer;
    ep0_in_handler_prepare_to_send_descriptor();
    ep0_in_bd.BDSTAT = ep0_bdstat;
}

void ep0_out_handler_ack() {
    //wait for setup token
    ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
    ep0_out_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN;
}

void ep0_in_handler_ack() {
    //wait for setup token
    ep0_in_bd.BDCNT = 0;
    ep0_in_bd.BDSTAT = BDSTAT_UOWN;
}

void ep0_in_handler_set_address() {
    UADDR = ep0_temp_uaddr;
}

void ep0_in_handler_configure() {
    usb_device_state = DEVICE_CONFIGURED;
}
#endif