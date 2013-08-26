/* 
 * File:   main.c
 * Author: rudarobson
 *
 * Created on 25 de Outubro de 2012, 01:26
 */
#include <xc.h>
#include <leonino/leonino.h>

#define PROG_START      0x2000
#define WRITE_FLASH     0x01
#define ERASE_FLASH     0x02
#define BOOT_END        0x03


char boot_started;
char wait_boot;

void handler(char *data, int total) {
    unsigned char type = data[0];

    switch (type) {
        case WRITE_FLASH:

            boot_started = 1;
            unsigned int address = 0;
            unsigned int data_len;
            unsigned int aux;
            unsigned int i = 0;

            for (i = 0; i < 2; i++) {
                aux = (data[1 + i]) & 0xFF;
                address |= (aux << (8 * (1 - i)));
            }

            data_len = data[3];

            if (address >= PROG_START) {
                WriteBytesFlash(address, data_len, (data + 4));
                data[1] = (address >> 8) & 0xff;
                data[2] = (address & 0xff);
                usb_write(data, 4); //write { 0x01, ADDRHIGH,ADDRLOW,LENGTH }
                ReadFlash(address, data_len, data);
                usb_write(data, data_len); //write data read from flash
                usb_send();
            }
            break;
        case ERASE_FLASH:

            boot_started = 1;
            unsigned int address = 0;
            unsigned int aux;
            for (i = 0; i < 2; i++) {
                aux = (data[1 + i]) & 0xFF;
                address |= (aux << (8 * (1 - i)));
            }

            if (address >= PROG_START) {
                EraseFlash(address, address + 0x20); //erase 64 bytes
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

