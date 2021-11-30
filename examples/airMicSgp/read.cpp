#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(115200);
	yetenek.init(0); // I2C
}

void loop(){
	float temp = yetenek.getAirTemperature(1);
	Serial.print("==> Temp: ");
	Serial.println(temp);
    
	float hum = yetenek.getAirHumidity(1);
	Serial.print("==> Humidity: ");
	Serial.println(hum);

	float pressure = yetenek.getAirPressure(1);
	Serial.print("==> Pressure: ");
	Serial.println(pressure);

	float altitude = yetenek.getAltitude(1);
	Serial.print("==> Altitude: ");
	Serial.println(altitude);

	float mic_db = yetenek.getMicrophoneAmplitude(1);
	Serial.print("==> Mic dB: ");
	Serial.println(mic_db);

	float mic_hertz = yetenek.getMicrophoneFrequency(1);
	Serial.print("==> Mic Hertz: ");
	Serial.println(mic_hertz);
	

	float co2 = yetenek.getCO2(1);
	Serial.print("==> CO2: ");
	Serial.println(co2);

	float tvoc = yetenek.getTVOC(1);
	Serial.print("==> TVOC: ");
	Serial.println(tvoc);

	float h2 = yetenek.getH2(1);
	Serial.print("==> H2: ");
	Serial.println(h2);

	float ethanol = yetenek.getEthanol(1);
	Serial.print("==> Ethanol: ");
	Serial.println(ethanol);
}