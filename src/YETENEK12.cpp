#include "YETENEK12.h"

Sensors::Sensors(){}

void Sensors::init(int type){
	if(type == 0){
		selectedComm = commType::i2c;
		Wire.begin(33, 32, (uint32_t) 400000);
	}else if(type == 1){
		selectedComm = commType::modBus;
		Serial2.begin(MODBUS_SPEED, SERIAL_8N1, 9, 10);
		pinMode(swPin, OUTPUT);
		// Switch pin girince calismiyor
		modbus.begin(ADDR_IO_1, Serial2); // Random address works
	}
}


// IO BOARD

uint16_t Sensors::getDigitalIO(int addr, int pin){
	int r_addr = 0;
	switch (pin){
	case 1:
		r_addr = ADDR_IO_B1;
		break;
	case 2:
		r_addr = ADDR_IO_B2;
		break;
	case 3:
		r_addr = ADDR_IO_B3;
		break;
	case 4:
		r_addr = ADDR_IO_B4;
		break;
	case 5:
		r_addr = ADDR_IO_B5;
		break;
	case 6:
		r_addr = ADDR_IO_B6;
		break;
	case 7:
		r_addr = ADDR_IO_B7;
		break;
	case 8:
		r_addr = ADDR_IO_B8;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_IO_1, r_addr, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_IO_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, r_addr, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

void Sensors::setDigitalIO(int addr, int pin, int value){
	int r_addr = 0;
	switch (pin){
	case 1:
		r_addr = ADDR_IO_A1;
		break;
	case 2:
		r_addr = ADDR_IO_A2;
		break;
	case 3:
		r_addr = ADDR_IO_A3;
		break;
	case 4:
		r_addr = ADDR_IO_A4;
		break;
	case 5:
		r_addr = ADDR_IO_A5;
		break;
	case 6:
		r_addr = ADDR_IO_A6;
		break;
	case 7:
		r_addr = ADDR_IO_A7;
		break;
	case 8:
		r_addr = ADDR_IO_A8;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		i2cWrite(ADDR_IO_1, r_addr, value);

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_IO_1);
		modbus.uint16ToRegister(r_addr, value);
		long after = millis();
	}
}

uint16_t Sensors::getADC(int addr, int port){
	int r_addr = 0;
	switch (port){
	case 1:
		r_addr = ADDR_IO_ADC1;
		break;
	case 2:
		r_addr = ADDR_IO_ADC2;
		break;
	case 3:
		r_addr = ADDR_IO_ADC3;
		break;
	case 4:
		r_addr = ADDR_IO_ADC4;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_IO_1, r_addr, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_IO_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, r_addr, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getADCVoltage(int addr, int port){
	int r_addr = 0, r_addr2 = 0;
	switch (port){
	case 1:
		r_addr = ADDR_IO_ADC1_V_MSB;
		r_addr2 = ADDR_IO_ADC1_V_LSB;
		break;
	case 2:
		r_addr = ADDR_IO_ADC2_V_MSB;
		r_addr2 = ADDR_IO_ADC2_V_LSB;
		break;
	case 3:
		r_addr = ADDR_IO_ADC3_V_MSB;
		r_addr2 = ADDR_IO_ADC3_V_LSB;
		break;
	case 4:
		r_addr = ADDR_IO_ADC4_V_MSB;
		r_addr2 = ADDR_IO_ADC4_V_LSB;
		break;
	default:
		break;
	}

	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_IO_1, r_addr, &val1);
		bool t2 = i2cRead(ADDR_IO_1, r_addr2, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_IO_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, r_addr, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, r_addr2, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}



// AIR MIC SGP

float Sensors::getAirTemperature(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_TMP_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_TMP_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_TMP_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_TMP_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getAirHumidity(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_HUM_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_HUM_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_HUM_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_HUM_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getAirPressure(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_PRE_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_PRE_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_PRE_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_PRE_LSB, bigEndian);
		return float32_from_two_uint16(val2, val1);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getAltitude(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_ALT_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_ALT_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_ALT_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_ALT_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getMicrophoneFrequency(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_SF_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_SF_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_SF_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_SF_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getMicrophoneAmplitude(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_SA_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_SA_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_SA_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_SA_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getCO2(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_CO2_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_CO2_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_CO2_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_CO2_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getTVOC(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_TVOC_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_TVOC_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_TVOC_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_TVOC_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getH2(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_H2_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_H2_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_H2_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_H2_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

float Sensors::getEthanol(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_AMS_1, ADDR_AMS_ETH_MSB, &val1);
		bool t2 = i2cRead(ADDR_AMS_1, ADDR_AMS_ETH_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_ETH_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_AMS_ETH_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}




// TOF RGB UV

float Sensors::getDistance(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_TRU_1, ADDR_TRU_DIS_MSB, &val1);
		bool t2 = i2cRead(ADDR_TRU_1, ADDR_TRU_DIS_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_DIS_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_DIS_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getUVA(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_TRU_1, ADDR_TRU_A_MSB, &val1);
		bool t2 = i2cRead(ADDR_TRU_1, ADDR_TRU_A_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_A_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_A_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getUVB(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_TRU_1, ADDR_TRU_B_MSB, &val1);
		bool t2 = i2cRead(ADDR_TRU_1, ADDR_TRU_B_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_B_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_B_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
float Sensors::getUVIndex(int addr){
	if(selectedComm == commType::i2c){
		uint16_t val1 = 0, val2 = 0;
		bool t1 = i2cRead(ADDR_TRU_1, ADDR_TRU_I_MSB, &val1);
		bool t2 = i2cRead(ADDR_TRU_1, ADDR_TRU_I_LSB, &val2);
		if(t1 && t2){ return float32_from_two_uint16(val2, val1); }
		else{ return -1; };

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		uint16_t val1 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_I_MSB, bigEndian);
		uint16_t val2 = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_TRU_I_LSB, bigEndian);
		return float32_from_two_uint16(val1, val2);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getColorRed(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_C_R, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_C_R, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorGreen(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_C_G, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_C_G, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorBlue(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_C_B, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_C_B, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorClear(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_C_C, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_C_C, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorTemp(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_C_T, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_C_T, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getColorLux(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_C_L, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_C_L, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}
uint16_t Sensors::getIRSensor(int addr){
	if(selectedComm == commType::i2c){
		uint16_t res = 0;
		if(i2cRead(ADDR_TRU_1, ADDR_TRU_IR, &res)){ return res; }
		else{ return 0; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU_1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_IR, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

// void Sensors::setDistanceMode(int mode){
// 	if(selectedComm == commType::i2c){
// 		i2cWrite(ADDR_IO, ADDR_IO_1, mode);

// 	}else if(selectedComm == commType::modBus){
// 		modbus.setSlaveID(ADDR_TOF);
// 		modbus.uint16ToRegister(ADDR_DRM, mode);
// 	}
// }


// int16_t Sensors::getSoundFreq(){
// 	if(selectedComm == commType::i2c){
// 		uint16_t res = 0;
// 		if(i2cRead(ADDR_AIR_MIC_UV, ADDR_SF1, &res)){ return res; }
// 		else{ return -1; }

// 	}else if(selectedComm == commType::modBus){
// 		modbus.setSlaveID(ADDR_AIR_MIC_UV);
// 		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_SF1, bigEndian);
	
// 	}else{
// 		return errorCodes::commTypeNotSelected;
// 	}
// }

// int16_t Sensors::getSoundAmplitude(){
// 	if(selectedComm == commType::i2c){
// 		uint16_t res = 0;
// 		if(i2cRead(ADDR_AIR_MIC_UV, ADDR_SA1, &res)){ return res; }
// 		else{ return -1; }

// 	}else if(selectedComm == commType::modBus){
// 		modbus.setSlaveID(ADDR_AIR_MIC_UV);
// 		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_SA1, bigEndian);
	
// 	}else{
// 		return errorCodes::commTypeNotSelected;
// 	}
// }

// byte Sensors::checkComm(modbusMaster modbus,TwoWire Wire, byte addr){
//     byte con = 0;
//    if(modbus != nullptr)
//     {
//         modbus.setSlaveID(addr);
//         if (modbus.getRegisters(HOLDING_REGISTERS, 0x01, 1))
//             con |= 0x01;
//     }
//    if(Wire != NULL)
//     {
//         Wire.beginTransmission(addr);
//         if(!Wire.endTransmission())
//             con |= 0x02;
//     }
//     return con;
	// return 0;
// }

// int16_t Sensors::getTemperature()
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_AIR,ADDR_TEMP,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_AIR);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TEMP, bigEndian);
// }
// uint16_t Sensors::getHumidity()
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_AIR,ADDR_HUMIDITY,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_AIR);
//     return modbus.int16FromRegister( HOLDING_REGISTERS, ADDR_HUMIDITY, bigEndian);
// }
// int16_t Sensors::getPressure()
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_AIR,ADDR_PRESSURE,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_AIR);
//     return modbus.int16FromRegister( HOLDING_REGISTERS, ADDR_PRESSURE, bigEndian);
// }
// uint16_t Sensors::getGas(modbusMaster modbus,TwoWire Wire,bool iic)
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_AIR,ADDR_GAS,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_AIR);
//     return modbus.int16FromRegister( HOLDING_REGISTERS, ADDR_GAS, bigEndian);
// }




// bool Sensors::setDistanceMode(modbusMaster modbus,TwoWire Wire,short mode, bool iic)
// {
//     if(iic)
//       if (i2cWrite(ADDR_TOF,ADDR_DRM,mode))    
//         return true;
		
//     modbus.setSlaveID(ADDR_TOF);    
//     modbus.uint16ToRegister(ADDR_DRM,mode);
//     delay(2);
//     uint16_t response = modbus.uint16FromRegister(HOLDING_REGISTERS, ADDR_DRM, bigEndian);
//     return response == mode;
// }

// uint16_t Sensors::getUva(modbusMaster modbus,TwoWire Wire,bool iic)
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_UV,ADDR_UVA,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_UV);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_UVA, bigEndian);
// }
// uint16_t Sensors::getUvb(modbusMaster modbus,TwoWire Wire,bool iic)
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_UV,ADDR_UVB,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_UV);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_UVB, bigEndian);
// }
// uint16_t Sensors::getUvindex(modbusMaster modbus,TwoWire Wire,bool iic)
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_UV,ADDR_UVIN,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_UV);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_UVIN, bigEndian);
// }

// int16_t Sensors::getADC(modbusMaster modbus,TwoWire Wire,byte channel, bool iic)
// {
//     uint16_t res = 0;
//     //channel %=4;

//     if(iic)
//     {
//        if(i2cRead(ADDR_ADC,ADDR_A0+channel,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_ADC);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_A0+channel, bigEndian);
// }


// int16_t Sensors::getAGMT(modbusMaster modbus,TwoWire Wire,byte mode, bool iic)
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_DOF9,ADDR_DOF9+mode,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_DOF9);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_DOF9+mode, bigEndian);
// }


// int16_t Sensors::getTempProbe(modbusMaster modbus,TwoWire Wire,bool iic)
// {
//     uint16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_TEMP,ADDR_TEMPERATURE,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_TEMP);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TEMPERATURE, bigEndian);
// }

bool Sensors::i2cRead(byte addr, byte reg, uint16_t *val){

	// BUG: arduino-esp32 Ilk okumada bir onceki sorgunun degeri geri donuyor, onun icin ayni sorgudan iki kere yapmak ve okumak gerekiyor
	
	Wire.beginTransmission(addr);
	Wire.write((uint8_t)reg);
	if(Wire.endTransmission(true)){
		log_e("Wire.endTransmission() error");
	}
	uint8_t error = Wire.requestFrom((uint8_t) addr, (uint8_t) 2);
	if(error){
		byte highByte = (byte) Wire.read();
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
	error = Wire.requestFrom((uint8_t) addr, (uint8_t) 2);
	if(error){
		byte highByte = (byte) Wire.read();
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
	if(Wire.endTransmission(true))
		log_e("Wire.endTransmission() error");
		return false;
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

void Sensors::setBuzzer(int value){
	digitalWrite(25, value);
}

Sensors yetenek = Sensors();