#include "../leonino.h"
#include "usb.h"
#include "ep0.h"
#include "ep1.h"
#include "ep2.h"

void usb_device_configure() {
    usb_start();
    while (usb_device_state != DEVICE_CONFIGURED) {
        usb_handle();
    }
}

void usb_start() {
    UCON = 0;
    UIR = 0;
    UIE = 0;

    usb_reset();

    UCFG = UCFG_FSEN | UCFG_UPUEN | UCFG_UOEMON;

    UIE = UIR = (UIER_STALLI | UIER_TRNI | UIER_URSTI);

    //configure endpoints
    ep0_configure();

    UCON = UCON_USBEN;
    //wait for device to initialize
    while (UCONbits.SE0);
}

void usb_disable() {
    UCON = 0; //disable
    usb_reset();
}

void usb_reset() {
    //	UADDR = 0; Automatically Set
    ep1_unconfigure();
    ep2_unconfigure();
    usb_device_state = DEVICE_ATTACHED;
    //clear fifo
    UIRbits.TRNIF = 0;
    UIRbits.TRNIF = 0;
    UIRbits.TRNIF = 0;
    UIRbits.TRNIF = 0;

}

unsigned char toggle = 0;

void usb_handle() {
    if (UIRbits.URSTIF) {
        usb_reset();
        UIRbits.URSTIF = 0;
    } else if (UIRbits.STALLIF) {
        unsigned char ustat = USTAT;
        UIRbits.STALLIF = 0;
    } else if (UIRbits.TRNIF) {
        unsigned char ustat;
        unsigned char endpnum;

        ustat = USTAT;
        UIRbits.TRNIF = 0;
        endpnum = USTAT_ENDPNUM(ustat);
        switch (endpnum) {
            case 0:
                ep0_entry_point(ustat);
                break;
            case 1:
                ep1_entry_point(ustat);
                break;
            case 2:
                ep2_entry_point(ustat);
                break;
        }
    }
}

void usb_configure_handler(usb_read_handler handler) {
    ep2_configure_handler(handler);
}

unsigned char usb_write(unsigned char *buffer, unsigned char count) {
    return ep1_write(buffer, count);
}

unsigned char usb_write_byte(unsigned char byte) {
    unsigned char buf[1];
    buf[0] = byte;
    return ep1_write(buf, 1);
}

unsigned char usb_read(char *buffer, unsigned char count, unsigned char maxcount) {
    return ep2_read(buffer, count, maxcount);
}

unsigned char usb_send() {
    return ep1_send();
}

