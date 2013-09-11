#include <leonino.h>

int x(){
	
}

void loop(){
	PORTBbits.RB3 = 1;
	delay_ms(100);
	PORTBbits.RB3 = 0;
	delay_ms(100);
}

void setup(){
	TRISBbits.RB3 = 0;
}
