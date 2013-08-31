#include "../leonino.h"
#include "usb.h"
#include "ep1.h"
#include "ep2.h"

/* IN DESCRIPTOR */

#ifndef EP1_C
#define EP1_C

BDENTRY ep1_bd @ BD_ADDRESS_IN(1);
unsigned char ep1_buffer[EP1_MAX_PACKET_SIZE] @ EP1_BUFFER_ADDRESS;
unsigned char total_writen = 0;

/* IN DESCRIPTOR */
void ep1_configure() {
    total_writen = 0;
    ep1_bd.BDCNT = 0;
    ep1_bd.BDADDRL = LOW_BYTE(EP1_BUFFER_ADDRESS);
    ep1_bd.BDADDRH = HIGH_BYTE(EP1_BUFFER_ADDRESS);
    ep1_bd.BDSTAT.uc = BDSTAT_DTS; //nothing to send prepare to DATA PACKET 1 so put 0
    UEP1 = UEP_EPHSHK | UEP_EPINEN | UEP_EPCONDIS;
}

void ep1_unconfigure() {
    UEP1 = 0;
    ep1_bd.BDSTAT.uc = BDSTAT_DTS; //nothing to send prepare to DATA PACKET 1 so put 0
    total_writen = 0;
}

unsigned char ep1_write(unsigned char *buffer, unsigned char count) {
    if (BDSTAT_CPU_OWNER(ep1_bd) && ((total_writen + count) < EP1_MAX_PACKET_SIZE)) {
        unsigned char i;
        for (i = 0; i < count; i++)
            ep1_buffer[total_writen + i] = buffer[i];

        total_writen += count;

        return count; //number of bytes put into the buffer
    }

    return 0;
}

//prepare to send

unsigned char ep1_send() {
    if (BDSTAT_CPU_OWNER(ep1_bd)) {
        ep1_bd.BDCNT = total_writen;
        total_writen = 0;
        if (ep1_bd.BDSTAT.DTS == 0)
            ep1_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN | BDSTAT_DTS;
        else
            ep1_bd.BDSTAT.uc = BDSTAT_UOWN | BDSTAT_DTSEN;
        return 1;
    }

    return 0;
}

void ep1_entry_point(unsigned char ustat) {
}
#endif
