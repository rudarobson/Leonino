/* 
 * File:   main.c
 * Author: rudarobson
 *
 * Created on 25 de Outubro de 2012, 01:26
 */
#include <leonino/leonino.h>

#include "usb/ep2.h"

#define PROG_START      0x2000
#define WRITE_FLASH     0x01
#define ERASE_FLASH     0x02
#define BOOT_END        0x03

typedef struct pck {
    unsigned char cmd;
    unsigned int address;
    unsigned char len;
} Pckt;

char boot_started;
char wait_boot;

void handler() {
    char data[USB_MAX_READ_SIZE];
    usb_read(data, USB_MAX_READ_SIZE, USB_MAX_READ_SIZE);
    Pckt *pckt = data;

    switch (pckt->cmd) {
        case WRITE_FLASH:
            boot_started = 1;

            if (pckt->address >= PROG_START) {
                usb_write(data, 4); //write { 0x01, ADDRHIGH,ADDRLOW,LENGTH }
                WriteBytesFlash(pckt->address, pckt->len, (data + 4));
                ReadFlash(pckt->address, pckt->len, data);
                usb_write(data, pckt->len); //write data read from flash
                usb_send();
            }
            break;
        case ERASE_FLASH:

            if (pckt->address >= PROG_START) {
                EraseFlash(pckt->address, pckt->address + 0x20); //erase 64 bytes
                usb_write_byte('O');
                usb_write_byte('K');
                usb_send();
            }
            break;
        case BOOT_END:
            usb_write_byte('O');
            usb_write_byte('K');
            usb_send();
            wait_boot = 0;
            break;
    }

    return;
}

void user_app() @ PROG_START {
    for (;;) {
    }
}

int main() @ 0x20 {
    unsigned long counter = 0;

    usb_disable();
    for (counter = 1000; counter > 1; counter--);

    usb_device_configure();
    usb_configure_handler(handler);

    counter = 0;
    boot_started = 0;
    wait_boot = 1;


    while (wait_boot == 1) {
        usb_handle();

        if (counter++ == 2500000 && !boot_started)
            wait_boot = 0;

    }

    user_app();
}

