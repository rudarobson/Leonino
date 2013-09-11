int x(){
	
}

void loop(){
	PORTBbits.RB3 = 1;
	delay_ms(1000);
	PORTBbits.RB3 = 0;
	delay_ms(1000);
}

void setup(){
	TRISBbits.RB3 = 0;
}
