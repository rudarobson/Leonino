#include "../internal/internal.h"
#include "delay.h"

void delay_ms(unsigned int t) {//t == 0 means 65536 ms
	do {
		_delay(INST_FREQ / 1000);//delay 1ms
	} while (t-- != 0);
}

