#ifndef YETENEK12_H
#define YETENEK12_H

#include <Wire.h>
#include <SensorModbusMaster.h>
#include <addr/defines.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>

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
		void setAddress(int board, int currentColorAddr, int newColorAddr);

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

		float getTempProbe(int colorAddr);
		
		// Internal
		void setBuzzer(int value);
		float readTemperature();
		int readButton(int value);
		void setLed(int value);
		void setRGBBrightness(int value);
		void setRGBWColor(int r, int g, int b, int w);
		void clearScreen();
		void showScreen();
		void setScreenText(String value, int size = 1, int color = 1, int x = -1, int y = -1);

	private:
		int getDeviceAddrFromColor(int board, int colorAddr);

		bool i2cRead(byte, byte, uint16_t*);
		bool i2cWrite(byte, byte, uint16_t);

		float float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint);

};

extern Sensors yetenek;

#endif