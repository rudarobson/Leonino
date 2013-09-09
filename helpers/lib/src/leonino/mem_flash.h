/* 
 * File:   mem_flash.h
 * Author: rudarobson
 *
 * Created on 1 de Setembro de 2013, 03:55
 */

#ifndef MEM_FLASH_H
#define	MEM_FLASH_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "leonino.h"
#define PROG_START 0x2000
    void SafeWriteBytesFlash(unsigned long startaddr, unsigned int num_bytes, unsigned char *flash_array);
    void SafeEraseFlash(unsigned long startaddr, unsigned long endaddr);



#ifdef	__cplusplus
}
#endif

#endif	/* MEM_FLASH_H */

