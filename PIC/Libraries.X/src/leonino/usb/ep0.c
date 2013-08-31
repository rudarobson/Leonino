#include "../leonino.h"
#include "usb.h"
#include "ep0.h"
#include "ep1.h"
#include "ep2.h"
#include "descriptor.h"

#ifndef EP0_C
#define EP0_C

#if defined(__COMPILER_HITECH) || defined(__COMPILER_XC8)
BDENTRY ep0_out_bd @ BD_ADDRESS_OUT(0);
unsigned char ep0_out_buffer[EP0_MAX_PACKET_SIZE] @ EP0_OUT_BUFFER_ADDRESS;
SetupPacket setup_pkt @ EP0_OUT_BUFFER_ADDRESS;
#elif defined(__COMPILER_SDCC)
__at(BD_ADDRESS_OUT(0)) BDENTRY ep0_out_bd;
__at(EP0_OUT_BUFFER_ADDRESS) unsigned char ep0_out_buffer[EP0_MAX_PACKET_SIZE];
#endif

usb_handler_t ep0_out_handler;

#if defined(__COMPILER_HITECH) || defined(__COMPILER_XC8)
BDENTRY ep0_in_bd @ BD_ADDRESS_IN(0);
unsigned char ep0_in_buffer[EP0_MAX_PACKET_SIZE]@ EP0_IN_BUFFER_ADDRESS;
#elif defined(__COMPILER_SDCC)
__at(BD_ADDRESS_IN(0)) BDENTRY ep0_in_bd;
__at(EP0_IN_BUFFER_ADDRESS) unsigned char ep0_in_buffer[EP0_MAX_PACKET_SIZE];
#endif

usb_handler_t ep0_in_handler;

unsigned char *ep0_in_decsriptor;
unsigned int ep0_in_total_bytes_to_send;

unsigned char ep0_dir;
unsigned char ep0_temp_uaddr;

void ep0_configure() {
    ep0_in_total_bytes_to_send = 0;
    UEP0 = UEP_EPHSHK | UEP_EPINEN | UEP_EPOUTEN;
    ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
    ep0_out_bd.BDADDRL = LOW_BYTE(EP0_OUT_BUFFER_ADDRESS);
    ep0_out_bd.BDADDRH = HIGH_BYTE(EP0_OUT_BUFFER_ADDRESS);
    ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for data 0

    ep0_in_bd.BDCNT = 0;
    ep0_in_bd.BDADDRL = LOW_BYTE(EP0_IN_BUFFER_ADDRESS);
    ep0_in_bd.BDADDRH = HIGH_BYTE(EP0_IN_BUFFER_ADDRESS);
    ep0_in_bd.BDSTAT.uc = 0;
    
}

void ep0_handle_setup_transaction() {
    unsigned int desc_len;

    switch (setup_pkt.bRequest) {
        case GET_STATUS://return two bytes
            switch (bmRequestType_Recipient(setup_pkt.bRequest)) {
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
                    break;
            }
            ep0_in_handler = ep0_in_handler_ack;
            ep0_out_handler = ep0_out_handler_ack;

            ep0_in_bd.BDCNT = 2;
            ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
            break;
        case GET_DESCRIPTOR://return the descriptor
            switch (setup_pkt.wValueHigh) {// wValue_High(ep0_out_buffer)) {
                case DESCRIPTOR_DEVICE_TYPE:
                    ep0_in_decsriptor = dev_desc;
                    desc_len = DESCRIPTOR_DEVICE_LENGTH;
                    break;
                case DESCRIPTOR_CONFIGURATION_TYPE:
                    ep0_in_decsriptor = conf_desc_0;
                    desc_len = DESCRIPTOR_CONFIGURATION_TOTAL_LENGTH;
                    break;
                case DESCRIPTOR_STRING_TYPE:
                    switch (setup_pkt.wValueLow) {
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
                    }
                    break;
            }
            ep0_in_total_bytes_to_send = MIN(setup_pkt.wLength, desc_len); //MIN(wLength(ep0_out_buffer), desc_len);

            ep0_in_bd.BDSTAT.DTS = 0; //prepare to wait a DATA1

            ep0_out_handler = ep0_out_handler_ack;
            ep0_in_handler = ep0_in_handler_send_descriptor;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS; //wait for out at status stage with data1

            ep0_in_handler_send_descriptor();
            break;
        case SET_ADDRESS:
            ep0_temp_uaddr = setup_pkt.wValueLow; // wValue_Low(ep0_out_buffer);

            ep0_in_handler = ep0_in_handler_set_address; //remove possibly

            //no data stage
            ep0_in_bd.BDCNT = 0;
            ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            //wait for setup
            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for setup
            break;
        case GET_CONFIGURATION:
            if (usb_device_state == DEVICE_CONFIGURED) {
                ep0_in_buffer[0] = 1; //only 1 configuration
                ep0_in_bd.BDCNT = 1; //wLength(ep0_out_buffer);
                ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
            }

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN; //wait for out data1 status stage
            break;
        case SET_CONFIGURATION:
            if (setup_pkt.wValueLow == 1) {
                ep0_in_handler = ep0_in_handler_configure;
                ep1_configure();
                ep2_configure();
                ep0_in_bd.BDCNT = 0;
                ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

                ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
                ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for setup
            }
            break;
        case GET_INTERFACE:
            ep0_in_buffer[0] = 0; //only 1 interface

            ep0_in_bd.BDCNT = 1;
            ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS; //wait for out status
            break;
        case SET_INTERFACE:
            ep0_in_bd.BDCNT = 0; //only 1 interface
            ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTS | BDSTAT_DTSEN;

            ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
            ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for setup
            break;
    }

    UCONbits.PKTDIS = 0; //reenable setup
}

void ep0_handle_standard_device() {
    unsigned char pid;

    if (ep0_dir == TRANS_DIR_IN)
        pid = BDSTAT_PID(ep0_in_bd.BDSTAT.uc);
    else
        pid = BDSTAT_PID(ep0_out_bd.BDSTAT.uc);

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
    }
}

void ep0_entry_point(unsigned char ustat) {
    unsigned char bmRequestType;

    if (USTAT_DIRECTION(ustat) == TRANS_DIR_IN) {
        ep0_dir = TRANS_DIR_IN;
        bmRequestType = bmRequestType_Type(setup_pkt.bRequest);
    } else {
        ep0_dir = TRANS_DIR_OUT;
        bmRequestType = bmRequestType_Type(setup_pkt.bRequest);
    }

    switch (bmRequestType) {
        case bmRequestType_Standard:
            ep0_handle_standard_device();
            break;
    }

}

void ep0_in_handler_send_descriptor() {
    unsigned int num = MIN(ep0_in_total_bytes_to_send, EP0_MAX_PACKET_SIZE);

    if (num > 0)
        ReadFlash(ep0_in_decsriptor, num, ep0_in_buffer);

    ep0_in_decsriptor += num;
    ep0_in_bd.BDCNT = num;

    if (ep0_in_bd.BDSTAT.DTS == 1)
        ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN;
    else
        ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;

}

void ep0_out_handler_ack() {
    //wait for setup token
    ep0_out_bd.BDCNT = EP0_MAX_PACKET_SIZE;
    ep0_out_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN;
}

void ep0_in_handler_ack() {
    //wait for setup token
    ep0_in_bd.BDCNT = 0;
    ep0_in_bd.BDSTAT.uc = BDSTAT_UOWN;
}

void ep0_in_handler_set_address() {
    UADDR = ep0_temp_uaddr;
}

void ep0_in_handler_configure() {
    usb_device_state = DEVICE_CONFIGURED;
}
#endif