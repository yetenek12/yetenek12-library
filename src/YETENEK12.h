#ifndef YETENEK12_H
#define YETENEK12_H

#include <Wire.h>
#include <SensorModbusMaster.h>
#include <addr/defines.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

// Model Numbers
#define MK3    1
#define MK4    2
#define IO_V1  3
#define MB_V1  4 // Main Board V1
#define MB_V2  5 // Main Board V1.1

class Sensors
{
	public:
		HardwareSerial* modbusSerial;
		modbusMaster modbus;

		OneWire oneWire{26};
		DallasTemperature ds18b20{&oneWire};
		Adafruit_SSD1306 display{128, 32, &Wire1, -1};
		Adafruit_NeoPixel strip{1, 27, NEO_GRBW + NEO_KHZ800};

		int selectedComm = -1;

		Sensors();

		/**
		 * @brief Start communucation
		 * 
		 * @param type  0 for I2C Mode, 1 for ModBus Mode
		 */
		void init(int type); // 0 => i2c Mode , 1 => ModBus

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
			air,
			optics,
			imu,
			temp,
			motor,
			gps
		};

		// Global
		// TODO GET Connected Boards
		void setDefaultAddresses();
		void setAddress(int board, int currentColorAddr, int newColorAddr);
		uint16_t getModuleType(int board, int colorAddr);
		uint16_t getSerialNumber(int board, int colorAddr);
		uint16_t getModelNumber(int board, int colorAddr);
		uint16_t getSoftwareVersion(int board, int colorAddr);
		uint16_t getHardwareVersion(int board, int colorAddr);
		uint16_t getDefaultI2CAddress(int board, int colorAddr);
		uint16_t getDefaultModBusAddress(int board, int colorAddr);

		// IO
		uint16_t getDigitalIO(int colorAddr, int pin);
		void setDigitalIO(int colorAddr, int pin, int value);
		uint16_t getADC(int colorAddr, int port);
		float getADCVoltage(int colorAddr, int port);

		// Air
		float getAirTemperature(int colorAddr);
		float getAirHumidity(int colorAddr);
		float getAirPressure(int colorAddr);
		float getAltitude(int colorAddr);
		void setSeaLevel(int colorAddr, float value);
		float getMicrophoneFrequency(int colorAddr);
		float getMicrophoneAmplitude(int colorAddr);
		float getCO2(int colorAddr);
		float getTVOC(int colorAddr);
		float getH2(int colorAddr);
		float getEthanol(int colorAddr);

		// Optics
		float getDistance(int colorAddr);
		uint16_t getDistanceStatus(int colorAddr);
		void setDistanceMode(int colorAddr, int value);
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

		// Temp Probe
		float getTempProbe(int colorAddr);
		
		// IMU
		float getAccelX(int colorAddr);
		float getAccelY(int colorAddr);
		float getAccelZ(int colorAddr);
		float getGyroX(int colorAddr);
		float getGyroY(int colorAddr);
		float getGyroZ(int colorAddr);
		float getMagX(int colorAddr);
		float getMagY(int colorAddr);
		float getMagZ(int colorAddr);
		uint16_t getHeading(int colorAddr);
		float getImuTemp(int colorAddr);

		// Internal
		void setBuzzer(int value);
		float readTemperature();
		int readButton(int value);
		void setLed(int value);
		void setRGBWColor(int r, int g, int b, int w, int brightness);
		void clearScreen();
		void showScreen();
		void screenNewLine();
		void setScreenText(String value, int size = 1, int color = 1, int x = -1, int y = -1);
		void setScreenText(int value, int size = 1, int color = 1, int x = -1, int y = -1);
		void setScreenText(float value, int size = 1, int color = 1, int x = -1, int y = -1);

	private:
		int getDeviceAddrFromColor(int board, int colorAddr);

		bool i2cRead(byte, byte, uint16_t*);
		bool i2cWrite(byte, byte, uint16_t);

		uint16_t MSB_16bit_of_float32(float float_number);
		uint16_t LSB_16bit_of_float32(float float_number);
		float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint);

};

extern Sensors yetenek;

#endif