#ifndef YETENEK12_H
#define YETENEK12_H

#include <Wire.h>
#include <SoftwareSerial.h>
#include <SensorModbusMaster.h>
#include <WireSlaveRequest.h>
#include <addr/defines.h>

class Sensors
{
	public:
		HardwareSerial* modbusSerial;
		modbusMaster modbus;
		WireSlaveRequest* slaveReq;

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

		uint16_t getAirTemperature();
		uint16_t getAirHumidity();
		uint16_t getAirPressure();
		uint16_t getAltitude();
		uint16_t getMicrophoneDB();
		uint16_t getMicrophoneFrequency();


		uint16_t getDistance();
		void setDistanceMode(int);

		uint16_t getUva();
		uint16_t getUvb();
		uint16_t getUvindex();

		int16_t getADC(byte channel, bool = false);
		int16_t getAGMT(byte, bool = false);             //Accelerometer,Gyro, Magnetometer, Temperature
		//bool setAccMode(byte, bool = false);
		//TODO: implement all mode setters

		int16_t getTempProbe();


	private:
		bool i2cRead(byte, byte, uint16_t*);
		bool i2cWrite(byte, byte, uint16_t);

		float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint);

};

extern Sensors yetenek;

#endif