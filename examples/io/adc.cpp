#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(115200);
	yetenek.init(0); // I2C
}

int adc1, adc2, adc3, adc4;
float adc1_voltage, adc2_voltage, adc3_voltage, adc4_voltage;

void loop(){

	Serial.print("GET ADC 1 -> ");
	adc1 = yetenek.getADC(1, 1); // Addr: 1, Pin: 1
	Serial.println(adc1);
	Serial.print("\n\nGET ADC 2 -> ");
	adc2 = yetenek.getADC(1, 2); // Addr: 1, Pin: 2
	Serial.println(adc2);
	Serial.print("\n\nGET ADC 3 -> ");
	adc3 = yetenek.getADC(1, 3); // Addr: 1, Pin: 3
	Serial.println(adc3);
	Serial.print("\n\nGET ADC 4 -> ");
	adc4 = yetenek.getADC(1, 4); // Addr: 1, Pin: 2
	Serial.println(adc4);

	Serial.print("GET ADC V 1 -> ");
	adc1_voltage = yetenek.getADCVoltage(1, 1); // Addr: 1, Pin: 1
	Serial.println(adc1_voltage);
	Serial.print("GET ADC V 2 -> ");
	adc2_voltage = yetenek.getADCVoltage(1, 2); // Addr: 1, Pin: 1
	Serial.println(adc2_voltage);
	Serial.print("GET ADC V 3 -> ");
	adc3_voltage = yetenek.getADCVoltage(1, 3); // Addr: 1, Pin: 1
	Serial.println(adc3_voltage);
	Serial.print("GET ADC V 4 -> ");
	adc4_voltage = yetenek.getADCVoltage(1, 4); // Addr: 1, Pin: 1
	Serial.println(adc4_voltage);

}