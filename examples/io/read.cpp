#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(9600);
	yetenek.init(0); // I2C
}

void loop(){
	// Get Digital IO
	int okunan_deger = yetenek.getDigitalIO(1, 1); // Addr: 1, Pin: 1
	Serial.print("Okunan Deger: ");
    Serial.println(okunan_deger);
	delay(500);
}
