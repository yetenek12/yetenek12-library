#include "YETENEK12.h"

Sensors::Sensors(){}
void Sensors::init(int type){
	if(type == 0){
		selectedComm = commType::i2c;
		Wire.begin(33, 32, (uint32_t) 400000);
	}else if(type == 1){
		selectedComm = commType::modBus;
		Serial2.begin(MODBUS_SPEED, SERIAL_8N1, 9, 10);
		// Switch pin girince calismiyor
		modbus.begin(ADDR_IO_1, Serial2); // Random address works
	}

	pinMode(25, OUTPUT); // Buzzer
	pinMode(13, INPUT); // Button 1
	pinMode(14, INPUT); // Button 2
	pinMode(12, OUTPUT); // LED
	ds18b20.begin(); // Temperature Sensor
	strip.begin(); // RGB Led
  	strip.show(); // RGB Led
  	strip.setBrightness(50); // RGB Led

	// OLED SCREEN
	Wire1.begin(21, 22, (uint32_t) 400000);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println(F("YETENEK 12"));
	display.setTextSize(1);
	display.println();
	display.print("Version: ");
	display.println("0.0.1");
	display.display();

	// SD Card
	// TODO
}

// GLOBAL
void Sensors::setDefaultAddresses(){
	// Broadcast all addresses
}
void Sensors::setAddress(int board, int currentColorAddr, int newColorAddr){
	int currentDeviceAddr = getDeviceAddrFromColor(board, currentColorAddr);
	int newDeviceAddr = getDeviceAddrFromColor(board, newColorAddr);
	
	if(selectedComm == commType::i2c){
		i2cWrite(currentDeviceAddr, ADDR_C_SET_I2C_ADDR, newDeviceAddr);

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(currentDeviceAddr);
		modbus.uint16ToRegister(ADDR_C_SET_MODBUS_ADDR, newDeviceAddr);
	}
}
uint16_t Sensors::getModuleType(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_TYPE, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_TYPE, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getSerialNumber(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_SERIAL_NUMBER, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_SERIAL_NUMBER, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getModelNumber(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_MODEL_NUMBER, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_MODEL_NUMBER, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getSoftwareVersion(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_SW_VER, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_SW_VER, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getHardwareVersion(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_HW_VER, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_HW_VER, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getDefaultI2CAddress(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_DEF_I2C_ADDR, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_DEF_I2C_ADDR, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getDefaultModBusAddress(int board, int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(board, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_C_DEF_MODBUS_ADDR, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_C_DEF_MODBUS_ADDR, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

// IO BOARD
uint16_t Sensors::getDigitalIO(int colorAddr, int pin){
	int deviceAddr = getDeviceAddrFromColor(boards::io, colorAddr);
	int requestRegister = 0;
	switch (pin){
		case 1:
			requestRegister = ADDR_IO_B1;
			break;
		case 2:
			requestRegister = ADDR_IO_B2;
			break;
		case 3:
			requestRegister = ADDR_IO_B3;
			break;
		case 4:
			requestRegister = ADDR_IO_B4;
			break;
		case 5:
			requestRegister = ADDR_IO_B5;
			break;
		case 6:
			requestRegister = ADDR_IO_B6;
			break;
		case 7:
			requestRegister = ADDR_IO_B7;
			break;
		case 8:
			requestRegister = ADDR_IO_B8;
			break;
		default:
			break;
	}
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, requestRegister, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, requestRegister, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
void Sensors::setDigitalIO(int colorAddr, int pin, int value){
	int deviceAddr = getDeviceAddrFromColor(boards::io, colorAddr);
	int requestRegister = 0;
	switch (pin){
		case 1:
			requestRegister = ADDR_IO_A1;
			break;
		case 2:
			requestRegister = ADDR_IO_A2;
			break;
		case 3:
			requestRegister = ADDR_IO_A3;
			break;
		case 4:
			requestRegister = ADDR_IO_A4;
			break;
		case 5:
			requestRegister = ADDR_IO_A5;
			break;
		case 6:
			requestRegister = ADDR_IO_A6;
			break;
		case 7:
			requestRegister = ADDR_IO_A7;
			break;
		case 8:
			requestRegister = ADDR_IO_A8;
			break;
		default:
			break;
	}
	if(selectedComm == commType::i2c){
		i2cWrite(deviceAddr, requestRegister, value);

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		modbus.uint16ToRegister(requestRegister, value);
	}
}
uint16_t Sensors::getADC(int colorAddr, int port){
	int deviceAddr = getDeviceAddrFromColor(boards::io, colorAddr);
	int requestRegister = 0;
	switch (port){
		case 1:
			requestRegister = ADDR_IO_ADC1;
			break;
		case 2:
			requestRegister = ADDR_IO_ADC2;
			break;
		case 3:
			requestRegister = ADDR_IO_ADC3;
			break;
		case 4:
			requestRegister = ADDR_IO_ADC4;
			break;
		default:
			break;
	}
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, requestRegister, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, requestRegister, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getADCVoltage(int colorAddr, int port){
	int deviceAddr = getDeviceAddrFromColor(boards::io, colorAddr);
	int requestRegister = 0, requestRegister2 = 0;
	switch (port){
		case 1:
			requestRegister = ADDR_IO_ADC1_V_MSB;
			requestRegister2 = ADDR_IO_ADC1_V_LSB;
			break;
		case 2:
			requestRegister = ADDR_IO_ADC2_V_MSB;
			requestRegister2 = ADDR_IO_ADC2_V_LSB;
			break;
		case 3:
			requestRegister = ADDR_IO_ADC3_V_MSB;
			requestRegister2 = ADDR_IO_ADC3_V_LSB;
			break;
		case 4:
			requestRegister = ADDR_IO_ADC4_V_MSB;
			requestRegister2 = ADDR_IO_ADC4_V_LSB;
			break;
		default:
			break;
	}

	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, requestRegister, &val1);
		bool t2 = i2cRead(deviceAddr, requestRegister2, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, requestRegister, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, requestRegister2, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

// AIR
float Sensors::getAirTemperature(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_TMP_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_TMP_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_TMP_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_TMP_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getAirHumidity(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_HUM_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_HUM_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_HUM_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_HUM_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getAirPressure(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_PRE_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_PRE_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_PRE_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_PRE_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getAltitude(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_ALT_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_ALT_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_ALT_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_ALT_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
void Sensors::setSeaLevel(int colorAddr, float value){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		i2cWrite(deviceAddr, ADDR_AIR_BME_SEA_MSB, MSB_16bit_of_float32(value));
		i2cWrite(deviceAddr, ADDR_AIR_BME_SEA_LSB, LSB_16bit_of_float32(value));

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		modbus.uint16ToRegister(ADDR_AIR_BME_SEA_MSB, MSB_16bit_of_float32(value));
		modbus.uint16ToRegister(ADDR_AIR_BME_SEA_LSB, LSB_16bit_of_float32(value));
	}
}
float Sensors::getMicrophoneFrequency(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_SF_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_SF_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_SF_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_SF_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getMicrophoneAmplitude(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_SA_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_SA_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_SA_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_SA_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getCO2(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_CO2_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_CO2_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_CO2_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_CO2_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getTVOC(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_TVOC_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_TVOC_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_TVOC_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_TVOC_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getH2(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_H2_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_H2_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_H2_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_H2_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getEthanol(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::air, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_AIR_ETH_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_AIR_ETH_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_ETH_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AIR_ETH_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

// OPTICS
float Sensors::getDistance(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_OPT_DIS_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_OPT_DIS_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_DIS_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_DIS_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getDistanceStatus(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_DIS_STA, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_DIS_STA, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
void Sensors::setDistanceMode(int colorAddr, int value){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		i2cWrite(deviceAddr, ADDR_OPT_DIS_M, value);

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		modbus.uint16ToRegister(ADDR_OPT_DIS_M, value);
	}
}
float Sensors::getUVA(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_OPT_A_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_OPT_A_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_A_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_A_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getUVB(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_OPT_B_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_OPT_B_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_B_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_B_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getUVIndex(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_OPT_I_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_OPT_I_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_I_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_I_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorRed(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_C_R, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_C_R, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorGreen(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_C_G, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_C_G, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorBlue(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_C_B, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_C_B, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorClear(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_C_C, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_C_C, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorTemp(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_C_T, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_C_T, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorLux(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_C_L, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_C_L, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getIRSensor(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::optics, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_OPT_IR, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_OPT_IR, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
// TODO SET LED
// TODO SET RGB

// TEMP PROBE
float Sensors::getTempProbe(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::temp, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_TEMP_T_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_TEMP_T_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_DIS_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_OPT_DIS_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

// IMU
float Sensors::getAccelX(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_ACCX_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_ACCX_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_ACCX_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_ACCX_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getAccelY(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_ACCY_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_ACCY_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_ACCY_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_ACCY_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getAccelZ(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_ACCZ_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_ACCZ_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_ACCZ_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_ACCZ_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getGyroX(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_GYRX_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_GYRX_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_GYRX_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_GYRX_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getGyroY(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_GYRY_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_GYRY_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_GYRY_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_GYRY_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getGyroZ(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_GYRZ_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_GYRZ_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_GYRZ_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_GYRZ_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getMagX(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_MAGX_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_MAGX_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_MAGX_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_MAGX_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getMagY(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_MAGY_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_MAGY_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_MAGY_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_MAGY_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getMagZ(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_MAGZ_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_MAGZ_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_MAGZ_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_MAGZ_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getHeading(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(deviceAddr, ADDR_IMU_HDG, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_IMU_HDG, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getImuTemp(int colorAddr){
	int deviceAddr = getDeviceAddrFromColor(boards::imu, colorAddr);
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(deviceAddr, ADDR_IMU_TEMP9_MSB, &val1);
		bool t2 = i2cRead(deviceAddr, ADDR_IMU_TEMP9_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val1, val2); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(deviceAddr);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_TEMP9_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_IMU_TEMP9_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

// MAIN BOARD
void Sensors::setBuzzer(int value){
	digitalWrite(25, value);
}
float Sensors::readTemperature(){
	ds18b20.requestTemperatures();
	float tempC = ds18b20.getTempCByIndex(0);
	if(tempC != DEVICE_DISCONNECTED_C) { return tempC; } 
	else{ return -1; }
}
int Sensors::readButton(int value){
	if(value == 1){ return !digitalRead(13); }
	else if(value == 2){ return !digitalRead(14); }
	else{ return -1; }
}
void Sensors::setLed(int value){
	digitalWrite(12, value);
}
void Sensors::setRGBBrightness(int value){
	value = constrain(value, 0, 255);
	strip.setBrightness(value);
}
void Sensors::setRGBWColor(int r, int g, int b, int w){
	strip.setPixelColor(0, strip.Color(r, g, b, w));
	strip.show();
}
void Sensors::clearScreen(){
	display.clearDisplay();
	// display.display();
}
void Sensors::showScreen(){
	display.display();
}
void Sensors::setScreenText(String value, int size, int color, int x, int y){
	if(x != -1 && y != -1){ display.setCursor(x, y); }
	if(color == 1){ display.setTextColor(WHITE); }
	else if(color == 2){ display.setTextColor(BLACK, WHITE); }

	display.setTextSize(size);
	display.print(value);
}

// HELPERS
bool Sensors::i2cRead(byte addr, byte reg, uint16_t *val){

	// BUG: arduino-esp32 Ilk okumada bir onceki sorgunun degeri geri donuyor, onun icin ayni sorgudan iki kere yapmak ve okumak gerekiyor
	
	Wire.beginTransmission(addr);
	Wire.write((uint8_t)reg);
	if(Wire.endTransmission(true)){
		log_e("Wire.endTransmission() error");
	}
	uint8_t Terror = Wire.requestFrom((uint8_t) addr, (uint8_t) 2);
	if(Terror){
		byte highByte = (byte) Wire.read();
		delay(2);
		byte lowByte = (byte) Wire.read();
	}else{
		log_e("Wire.requestFrom() error");
	}

	Wire.beginTransmission(addr);
	Wire.write((uint8_t)reg);
	if(Wire.endTransmission(true)){
		log_e("Wire.endTransmission() error");
		return false;
	}
	uint8_t error = Wire.requestFrom((uint8_t) addr, (uint8_t) 2);
	if(error){
		byte highByte = (byte) Wire.read();
		delay(2);
		byte lowByte = (byte) Wire.read();
		*val = (highByte << 8) | lowByte;
		return true;
	}else{
		log_e("Wire.requestFrom() error");
		return false;
	}
}
bool Sensors::i2cWrite(byte addr, byte reg, uint16_t val){
	Wire.beginTransmission(addr);
	Wire.write(reg);
	Wire.write(val);
	if(Wire.endTransmission(true)){
		log_e("Wire.endTransmission() error");
		return false;
	}
	return true;
}
float Sensors::float32_from_two_uint16(uint16_t MSB_uint, uint16_t LSB_uint){
	union{
		float f_number;
		uint16_t uint16_arr[2];
	} union_for_conv;  
	union_for_conv.uint16_arr[0] = LSB_uint;
	union_for_conv.uint16_arr[1] = MSB_uint;
	return union_for_conv.f_number;
}
uint16_t Sensors::MSB_16bit_of_float32(float float_number){
	union{
		float f_number;
		uint16_t uint16_arr[2];
	} union_for_conv;  
	union_for_conv.f_number = float_number;
	uint16_t MSB_uint16 = union_for_conv.uint16_arr[1];
	return MSB_uint16;
}
uint16_t Sensors::LSB_16bit_of_float32(float float_number){
	union{
		float f_number;
		uint16_t uint16_arr[2];
	} union_for_conv;  
	union_for_conv.f_number = float_number;
	uint16_t LSB_uint16 = union_for_conv.uint16_arr[0];
	return LSB_uint16;
}
int Sensors::getDeviceAddrFromColor(int board, int colorAddr){
	int deviceAddr = -1;
	switch (board){
		case boards::io:
			switch (colorAddr){
				case colorCodes::green:
					deviceAddr = ADDR_IO_1;
					break;
				case colorCodes::blue:
					deviceAddr = ADDR_IO_2;
					break;
				case colorCodes::orange:
					deviceAddr = ADDR_IO_3;
					break;
				case colorCodes::yellow:
					deviceAddr = ADDR_IO_4;
					break;
				case colorCodes::turquoise:
					deviceAddr = ADDR_IO_5;
					break;
				case colorCodes::purple:
					deviceAddr = ADDR_IO_6;
					break;
				default:
					deviceAddr = ADDR_IO_1;
					break;
			}
			break;

		case boards::air:
			switch (colorAddr){
				case colorCodes::green:
					deviceAddr = ADDR_AIR_1;
					break;
				case colorCodes::blue:
					deviceAddr = ADDR_AIR_2;
					break;
				case colorCodes::orange:
					deviceAddr = ADDR_AIR_3;
					break;
				case colorCodes::yellow:
					deviceAddr = ADDR_AIR_4;
					break;
				case colorCodes::turquoise:
					deviceAddr = ADDR_AIR_5;
					break;
				case colorCodes::purple:
					deviceAddr = ADDR_AIR_6;
					break;
				default:
					deviceAddr = ADDR_AIR_1;
					break;
			}
			break;

		case boards::optics:
			switch (colorAddr){
				case colorCodes::green:
					deviceAddr = ADDR_OPT_1;
					break;
				case colorCodes::blue:
					deviceAddr = ADDR_OPT_2;
					break;
				case colorCodes::orange:
					deviceAddr = ADDR_OPT_3;
					break;
				case colorCodes::yellow:
					deviceAddr = ADDR_OPT_4;
					break;
				case colorCodes::turquoise:
					deviceAddr = ADDR_OPT_5;
					break;
				case colorCodes::purple:
					deviceAddr = ADDR_OPT_6;
					break;
				default:
					deviceAddr = ADDR_OPT_1;
					break;
			}
			break;

		case boards::imu:
			switch (colorAddr){
				case colorCodes::green:
					deviceAddr = ADDR_IMU_1;
					break;
				case colorCodes::blue:
					deviceAddr = ADDR_IMU_2;
					break;
				case colorCodes::orange:
					deviceAddr = ADDR_IMU_3;
					break;
				case colorCodes::yellow:
					deviceAddr = ADDR_IMU_4;
					break;
				case colorCodes::turquoise:
					deviceAddr = ADDR_IMU_5;
					break;
				case colorCodes::purple:
					deviceAddr = ADDR_IMU_6;
					break;
				default:
					deviceAddr = ADDR_IMU_1;
					break;
			}
			break;

		case boards::temp:
			switch (colorAddr){
				case colorCodes::green:
					deviceAddr = ADDR_TEMP_1;
					break;
				case colorCodes::blue:
					deviceAddr = ADDR_TEMP_2;
					break;
				case colorCodes::orange:
					deviceAddr = ADDR_TEMP_3;
					break;
				case colorCodes::yellow:
					deviceAddr = ADDR_TEMP_4;
					break;
				case colorCodes::turquoise:
					deviceAddr = ADDR_TEMP_5;
					break;
				case colorCodes::purple:
					deviceAddr = ADDR_TEMP_6;
					break;
				default:
					deviceAddr = ADDR_TEMP_1;
					break;
			}
			break;

		default:
			break;
	}
	return deviceAddr;
}

Sensors yetenek = Sensors();