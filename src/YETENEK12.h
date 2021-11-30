#ifndef YETENEK12_H
#define YETENEK12_H

#include <Wire.h>
#include <SoftwareSerial.h>
#include <SensorModbusMaster.h>
#include <addr/defines.h>

class Sensors
{
	public:
		HardwareSerial* modbusSerial;
		modbusMaster modbus;

		int selectedComm = -1;

		Sensors();

		void init(int type); // 0 => i2c Mode , 1 => ModBus

		int swPin = 0;

		enum commType{
			modBus,
			i2c
		};

		enum errorCodes{
			commTypeNotSelected = -2,
		};

		// byte checkComm(modbusMaster,TwoWire,byte addr);

		// IO Board
		uint16_t getDigitalIO(int addr, int pin);
		void setDigitalIO(int addr, int pin, int value);
		uint16_t getADC(int addr, int port);
		float getADCVoltage(int addr, int port);

		// Air Mic Sgp
		float getAirTemperature(int addr);
		float getAirHumidity(int addr);
		float getAirPressure(int addr);
		float getAltitude(int addr);
		float getMicrophoneFrequency(int addr);
		float getMicrophoneAmplitude(int addr);
		float getCO2(int addr);
		float getTVOC(int addr);
		float getH2(int addr);
		float getEthanol(int addr);

		// Tof Rgb Uv
		float getDistance(int addr);
		// uint16_t getDistanceStatus(int addr); // TODO
		// void setDistanceMode(int); // TODO
		float getUVA(int addr);
		float getUVB(int addr);
		float getUVIndex(int addr);
		uint16_t getColorRed(int addr);
		uint16_t getColorGreen(int addr);
		uint16_t getColorBlue(int addr);
		uint16_t getColorClear(int addr);
		uint16_t getColorTemp(int addr);
		uint16_t getColorLux(int addr);
		uint16_t getIRSensor(int addr);

	private:
		bool i2cRead(byte, byte, uint16_t*);
		bool i2cWrite(byte, byte, uint16_t);

		float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint);

};

extern Sensors yetenek;

#endif