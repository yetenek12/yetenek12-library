#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(9600);
	yetenek.init(0); // I2C
}

void loop(){
	int okunan_deger = yetenek.getDigitalIO(1, 1); // Addr: 1, Pin: 1
	yetenek.setDigitalIO(1, 1, okunan_deger);
	Serial.print("Okunan Deger: ");
    Serial.println(okunan_deger);
	delay(50);
}
