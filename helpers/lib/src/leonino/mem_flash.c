#include "mem_flash.h"

void SafeWriteBytesFlash(unsigned long startaddr, unsigned int num_bytes, unsigned char *flash_array) {
    if (startaddr >= PROG_START)
        WriteBytesFlash(startaddr, num_bytes, flash_array);
}

void SafeEraseFlash(unsigned long startaddr, unsigned long endaddr){
    if (startaddr >= PROG_START && endaddr >= PROG_START)
        EraseFlash(startaddr,endaddr);
}