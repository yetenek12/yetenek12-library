#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(115200);
	yetenek.init(Sensors::commType::i2c);
}


void loop(){
	int dis = yetenek.getDistance();
	int freq = yetenek.getSoundFreq();
	int amp = yetenek.getSoundAmplitude();
	Serial.printf("Distance: %d\tSound Frequency: %ld\tSound Amplitude: %d", dis, freq, amp);
	delay(1000);
}