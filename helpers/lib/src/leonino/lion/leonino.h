/* 
 * File:   internal.h
 * Author: rudarobson
 *
 * Created on 13 de Agosto de 2013, 15:11
 */

#ifndef LEONINO_H
#define	LEONINO_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

#include "delay.h"
#include "usb/usb.h"

#ifndef CPU_FREQ
#define CPU_FREQ        48000000 /* 48 MHZ */
#endif

#define INST_FREQ       CPU_FREQ/4 /* 48/4 MHZ */
#define INST_FREQ_us    INST_FREQ/1000000
#define INST_FREQ_ms    INST_FREQ/1000
#define HIGH            1
#define LOW		0

#define std_int32 long
#define std_byte char
#define std_int8 std_byte

    void delay_ms(unsigned int t);

#ifdef	__cplusplus
}
#endif

#endif	/* LEONINO_H */

