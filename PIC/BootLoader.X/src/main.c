/* 
 * File:   main.c
 * Author: rudarobson
 *
 * Created on 25 de Outubro de 2012, 01:26
 */
#include <leonino/leonino.h>

#define PROG_START      0x2000
asm("PROG_START EQU 0x2000");
#define WRITE_FLASH     0x01
#define ERASE_FLASH     0x02
#define BOOT_END        0x03

//
////#pragma config CONFIG1L = 0x24
//__CONFIG(1, PLLDIV_5 & CPUDIV_OSC1_PLL2 & USBDIV_2);
//
////#pragma config CONFIG1H = 0xF
//__CONFIG(2, FOSC_HSPLL_HS & FCMEN_OFF & IESO_OFF);
//
////#pragma config CONFIG2L = 0x3F
//__CONFIG(3, PWRT_OFF & BOR_ON & BORV_3 & VREGEN_ON);
//
////#pragma config CONFIG2H = 0x1E
//__CONFIG(4, WDT_OFF & WDTPS_32768);
//
////#pragma config CONFIG3H = 0x83
//__CONFIG(5, CCP2MX_ON & PBADEN_ON & LPT1OSC_OFF & MCLRE_ON);
//
//__CONFIG(5, CCP2MX_ON & PBADEN_ON & LPT1OSC_OFF & MCLRE_ON);
////#pragma config CONFIG4L = 0x85
//__CONFIG(6, STVREN_ON & LVP_ON & ICPRT_OFF & XINST_OFF);
////#pragma config CONFIG5L = 0xF
//__CONFIG(7, CP0_OFF & CP1_OFF & CP2_OFF & CP3_OFF);
////#pragma config CONFIG5H = 0xC0
//__CONFIG(8, CPB_OFF & CPD_OFF);
////#pragma config CONFIG6L = 0xF
//__CONFIG(9, WRT0_OFF & WRT1_OFF & WRT2_OFF & WRT3_OFF);
////#pragma config CONFIG6H = 0xE0
//__CONFIG(10, WRTC_OFF & WRTB_OFF & WRTD_OFF);
////#pragma config CONFIG7L = 0xF
//__CONFIG(11, EBTR0_OFF & EBTR1_OFF & EBTR2_OFF & EBTR3_OFF);
////#pragma config CONFIG7H = 0x40
//__CONFIG(12, EBTRB_OFF);

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

    asm("GOTO _user_app");
}

