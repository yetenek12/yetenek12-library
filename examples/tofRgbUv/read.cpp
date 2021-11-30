#include <Arduino.h>
#include <YETENEK12.h>

void setup(){
	Serial.begin(115200);
	yetenek.init(0); // I2C
}

void loop(){
    float distance = yetenek.getDistance(1);
	Serial.print("==> Distance: ");
	Serial.println(distance);

	float uva =  yetenek.getUVA(1);
	Serial.print("==> UV A: ");
	Serial.println(uva);

	float uvb =  yetenek.getUVB(1);
	Serial.print("==> UV B: ");
	Serial.println(uvb);

	float uv_index =  yetenek.getUVIndex(1);
	Serial.print("==> UV Index: ");
	Serial.println(uv_index);

	uint16_t red =  yetenek.getColorRed(1);
	Serial.print("==> Red: ");
	Serial.println(red);

	uint16_t green =  yetenek.getColorGreen(1);
	Serial.print("==> Green: ");
	Serial.println(green);

	uint16_t blue =  yetenek.getColorBlue(1);
	Serial.print("==> Blue: ");
	Serial.println(blue);

	uint16_t clear =  yetenek.getColorClear(1);
	Serial.print("==> Clear: ");
	Serial.println(clear);

	uint16_t color_temp =  yetenek.getColorTemp(1);
	Serial.print("==> Color Temp: ");
	Serial.println(color_temp);

	uint16_t lux =  yetenek.getColorLux(1);
	Serial.print("==> Lux: ");
	Serial.println(Lux);

	uint16_t ir_sensor =  yetenek.getIRSensor(1);
	Serial.print("==> IR Sensor: ");
	Serial.println(ir_sensor);
}