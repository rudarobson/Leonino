#include <htc.h>
#include "usb.h"
#include "ep0.h"
#include "ep2.h"
#include "descriptor.h"


#ifndef EP2_C
#define EP2_C

BDENTRY ep2_bd @ BD_ADDRESS_OUT(2);
unsigned char ep2_buffer[EP2_MAX_PACKET_SIZE] @ EP2_BUFFER_ADDRESS;

/* OUT DESCRIPTOR */
unsigned char ep2_last_data_bit = 0;
unsigned char ep2_code = 0;
usb_read_handler ep2_receive_handler = 0;

void ep2_configure() {
    //TRISB = 0xC0; //all B ports for out except 7 and 6

    ep2_last_data_bit = 0;
    ep2_bd.BDCNT = EP2_MAX_PACKET_SIZE;
    ep2_bd.BDADDRL = LOW_BYTE(EP2_BUFFER_ADDRESS);
    ep2_bd.BDADDRH = HIGH_BYTE(EP2_BUFFER_ADDRESS);
    ep2_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for data 0
    UEP2 = UEP_EPHSHK | UEP_EPOUTEN | UEP_EPCONDIS;
}

void ep2_unconfigure() {
    ep2_last_data_bit = 0;
    ep2_bd.BDSTAT = 0;
    UEP2 = 0;
}

//prepare for read

void ep2_prepare_read() {
    ep2_bd.BDCNT = EP2_MAX_PACKET_SIZE;

    if (ep2_last_data_bit == 0)
        ep2_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
    else
        ep2_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN;

}

void ep2_configure_handler(usb_read_handler handler) {
    ep2_receive_handler = handler;
}

void ep2_entry_point(unsigned char ustat) {
    if (ep2_receive_handler != 0)
        ep2_receive_handler((char*)EP2_BUFFER_ADDRESS, ep2_bd.BDCNT);

    ep2_prepare_read();


    if (ep2_last_data_bit == 0)
        ep2_last_data_bit = 1;
    else
        ep2_last_data_bit = 0;
}
#endif

