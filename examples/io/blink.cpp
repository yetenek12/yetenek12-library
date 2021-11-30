#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(9600);
	yetenek.init(0); // I2C
}

void loop(){
	// Get Digital IO
	yetenek.setDigitalIO(1, 1, 1); // Addr: 1, Pin: 1, Value: 1
	delay(500);
	yetenek.setDigitalIO(1, 1, 0); // Addr: 1, Pin: 1, Value: 0
	delay(500);
}
