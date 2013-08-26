#include <htc.h>
#include "usb.h"
#include "ep1.h"
#include "ep2.h"

/* IN DESCRIPTOR */

#ifndef EP1_C
#define EP1_C

BDENTRY ep1_bd @ BD_ADDRESS_IN(1);
unsigned char ep1_buffer[EP1_MAX_PACKET_SIZE] @ EP1_BUFFER_ADDRESS;
unsigned char ep1_last_data_bit = 1;
unsigned char ep1_sent = 1;
unsigned char total_writen = 0;

/* IN DESCRIPTOR */
void ep1_configure() {
    ep1_last_data_bit = 1;
    ep1_sent = 1;

    ep1_bd.BDCNT = 0;
    ep1_bd.BDADDRL = LOW_BYTE(EP1_BUFFER_ADDRESS);
    ep1_bd.BDADDRH = HIGH_BYTE(EP1_BUFFER_ADDRESS);
    ep1_bd.BDSTAT = 0; //nothing to send
    UEP1 = UEP_EPHSHK | UEP_EPINEN | UEP_EPCONDIS;
}

void ep1_unconfigure() {
    ep1_last_data_bit = 1;
    ep1_sent = 1;
    ep1_bd.BDSTAT = 0;
    UEP1 = 0;
}

unsigned char ep1_write(unsigned char *buffer, unsigned char count) {
    if (ep1_sent && ((total_writen + count) < EP1_MAX_PACKET_SIZE)) {
        unsigned char i = 0;
        ep1_bd.BDSTAT = 0; //retrieve control

        for (i = 0; i < count && (i + total_writen) < EP1_MAX_PACKET_SIZE; i++)
            ep1_buffer[total_writen + i] = buffer[i];

        total_writen += i;

        return i; //number of bytes put into the buffer
    }

    return 0;
}

//prepare to send

unsigned char ep1_send() {
    if (ep1_sent) {
        ep1_sent = 0; //not sent yet

        ep1_bd.BDCNT = total_writen;
        if (ep1_last_data_bit == 0)
            ep1_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
        else
            ep1_bd.BDSTAT = BDSTAT_UOWN | BDSTAT_DTSEN;

        return 1;
    }

    return 0;
}

void ep1_entry_point(unsigned char ustat) {
    total_writen = 0;
    ep1_sent = 1;

    if (ep1_last_data_bit == 0)
        ep1_last_data_bit = 1;
    else
        ep1_last_data_bit = 0;
}
#endif
