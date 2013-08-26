/* 
 * File:   internal.h
 * Author: rudarobson
 *
 * Created on 13 de Agosto de 2013, 15:11
 */

#ifndef INTERNAL_H
#define	INTERNAL_H

#include <htc.h>


#ifdef	__cplusplus
extern "C" {
#endif
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

#ifndef CPU_FREQ
#define CPU_FREQ        48000000 /* 48 MHZ */
#endif

#define INST_FREQ       CPU_FREQ/4 /* 48/4 MHZ */
#define INST_FREQ_us    INST_FREQ/1000000
#define INST_FREQ_ms    INST_FREQ/1000
#define HIGH            1
#define LOW		0

    void delay_ms(unsigned int t);

#ifdef	__cplusplus
}
#endif

#endif	/* INTERNAL_H */

