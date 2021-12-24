#ifndef YETENEK12_H
#define YETENEK12_H

#include <Wire.h>
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

		enum colorCodes{
			green = 1,
			blue,
			orange,
			yellow,
			turquoise,
			purple
		};

		enum boards{
			io = 1,
			airmic,
			tofrgb,
			imu,
			temp,
			motor,
			gps
		};

		// byte checkComm(modbusMaster,TwoWire,byte addr);

		// Global
		void setDefaultAddresses();
		void setAddress(int board, int oldColorAddr, int newColorAddr);

		// IO Board
		uint16_t getDigitalIO(int colorAddr, int pin);
		void setDigitalIO(int colorAddr, int pin, int value);
		uint16_t getADC(int colorAddr, int port);
		float getADCVoltage(int colorAddr, int port);

		// Air Mic Sgp
		float getAirTemperature(int colorAddr);
		float getAirHumidity(int colorAddr);
		float getAirPressure(int colorAddr);
		float getAltitude(int colorAddr);
		float getMicrophoneFrequency(int colorAddr);
		float getMicrophoneAmplitude(int colorAddr);
		float getCO2(int colorAddr);
		float getTVOC(int colorAddr);
		float getH2(int colorAddr);
		float getEthanol(int colorAddr);

		// Tof Rgb Uv
		float getDistance(int colorAddr);
		// uint16_t getDistanceStatus(int addr); // TODO
		// void setDistanceMode(int); // TODO
		float getUVA(int colorAddr);
		float getUVB(int colorAddr);
		float getUVIndex(int colorAddr);
		uint16_t getColorRed(int colorAddr);
		uint16_t getColorGreen(int colorAddr);
		uint16_t getColorBlue(int colorAddr);
		uint16_t getColorClear(int colorAddr);
		uint16_t getColorTemp(int colorAddr);
		uint16_t getColorLux(int colorAddr);
		uint16_t getIRSensor(int colorAddr);
		
		// Internal

		void setBuzzer(int value);

	private:
		int getDeviceAddrFromColor(int board, int colorAddr);

		bool i2cRead(byte, byte, uint16_t*);
		bool i2cWrite(byte, byte, uint16_t);

		float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint);

};

extern Sensors yetenek;

#endif