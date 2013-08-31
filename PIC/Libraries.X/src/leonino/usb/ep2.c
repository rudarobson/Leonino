#include "../leonino.h"
#include "usb.h"
#include "ep0.h"
#include "ep2.h"
#include "descriptor.h"


#ifndef EP2_C
#define EP2_C

BDENTRY ep2_bd @ BD_ADDRESS_OUT(2);
unsigned char ep2_buffer[EP2_MAX_PACKET_SIZE] @ EP2_BUFFER_ADDRESS;

/* OUT DESCRIPTOR */
usb_read_handler ep2_receive_handler = 0;

void ep2_configure() {
    ep2_bd.BDCNT = EP2_MAX_PACKET_SIZE;
    ep2_bd.BDADDRL = LOW_BYTE(EP2_BUFFER_ADDRESS);
    ep2_bd.BDADDRH = HIGH_BYTE(EP2_BUFFER_ADDRESS);
    ep2_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN; //wait for data 0
    UEP2 = UEP_EPHSHK | UEP_EPOUTEN | UEP_EPCONDIS;
}

void ep2_unconfigure() {
    UEP2 = 0;
    ep2_bd.BDSTAT.uc = 0;
    ep2_unconfigure_handler();
}

//prepare for read

void ep2_prepare_read() {
    ep2_bd.BDCNT = EP2_MAX_PACKET_SIZE;

    if (ep2_bd.BDSTAT.DTS == 0)
        ep2_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
    else
        ep2_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN;

}

void ep2_configure_handler(usb_read_handler handler) {
    ep2_receive_handler = handler;
}

void ep2_unconfigure_handler() {
    ep2_receive_handler = 0;
}

void ep2_entry_point(unsigned char ustat) {
    if (ep2_receive_handler != 0)
        ep2_receive_handler();

#warning this should remain here until XC8 support function pointer with parameters
    //ep2_receive_handler((char*) EP2_BUFFER_ADDRESS, ep2_bd.BDCNT); this code don't execute on XC8

    ep2_prepare_read();
}

unsigned char ep2_read(char *buffer, unsigned char count, unsigned char maxcount) {
    unsigned char numread;
    numread = ((count >= maxcount) ? maxcount : count);
    numread = ((numread > EP2_MAX_PACKET_SIZE) ? EP2_MAX_PACKET_SIZE : numread);

    for (unsigned char i = 0; i < numread; i++)
        buffer[i] = ep2_buffer[i];

    return numread;
}
#endif

