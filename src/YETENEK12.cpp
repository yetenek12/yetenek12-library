#include "YETENEK12.h"

Sensors::Sensors(){}

// For I2C use
void Sensors::init(){
	selectedComm = commType::i2c;
	Wire.begin(33, 32, 400000);
}

// For ModBus use
void Sensors::init(int rx, int tx, int sw){
	selectedComm = commType::modBus;
	Serial1.begin(MODBUS_SPEED, SWSERIAL_8N1, rx, tx);
	swPin = sw;
	pinMode(swPin, OUTPUT);
}

uint16_t Sensors::getDigitalIO(int pin){
	int addr = 0;
	switch (pin){
	case 1:
		addr = ADDR_IO_B1;
		break;
	case 2:
		addr = ADDR_IO_B2;
		break;
	case 3:
		addr = ADDR_IO_B3;
		break;
	case 4:
		addr = ADDR_IO_B4;
		break;
	case 5:
		addr = ADDR_IO_B5;
		break;
	case 6:
		addr = ADDR_IO_B6;
		break;
	case 7:
		addr = ADDR_IO_B7;
		break;
	case 8:
		addr = ADDR_IO_B8;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_IO, addr, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		// modbus.setSlaveID(ADDR_IO);
		modbus.begin(ADDR_IO, Serial1);
		return modbus.int16FromRegister(HOLDING_REGISTERS, addr, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

void Sensors::setDigitalIO(int pin, int value){
	int addr = 0;
	switch (pin){
	case 1:
		addr = ADDR_IO_A1;
		break;
	case 2:
		addr = ADDR_IO_A2;
		break;
	case 3:
		addr = ADDR_IO_A3;
		break;
	case 4:
		addr = ADDR_IO_A4;
		break;
	case 5:
		addr = ADDR_IO_A5;
		break;
	case 6:
		addr = ADDR_IO_A6;
		break;
	case 7:
		addr = ADDR_IO_A7;
		break;
	case 8:
		addr = ADDR_IO_A8;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		i2cWrite(ADDR_IO, addr, value);

	}else if(selectedComm == commType::modBus){
		// modbus.setSlaveID(ADDR_IO);
		modbus.uint16ToRegister(addr, value);

	}
}


uint16_t Sensors::getADC(int port){
	int addr = 0;
	switch (port){
	case 1:
		addr = ADDR_IO_ADC1;
		break;
	case 2:
		addr = ADDR_IO_ADC2;
		break;
	case 3:
		addr = ADDR_IO_ADC3;
		break;
	case 4:
		addr = ADDR_IO_ADC4;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_IO, addr, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_IO);
		return modbus.int16FromRegister(HOLDING_REGISTERS, addr, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getADCVoltage(int port){
	int addr = 0;
	switch (port){
	case 1:
		addr = ADDR_IO_ADC1_V;
		break;
	case 2:
		addr = ADDR_IO_ADC2_V;
		break;
	case 3:
		addr = ADDR_IO_ADC3_V;
		break;
	case 4:
		addr = ADDR_IO_ADC4_V;
		break;
	default:
		break;
	}
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_IO, addr, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_IO);
		return modbus.int16FromRegister(HOLDING_REGISTERS, addr, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}



uint16_t Sensors::getAirTemperature(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_AMS, ADDR_AMS_TMP, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.begin(ADDR_IO, modbusSerial, 4);
		modbus.setSlaveID(ADDR_AMS);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_AMS_TMP, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getAirHumidity(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_AMS, ADDR_AMS_HUM, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_AMS_HUM, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getAirPressure(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_AMS, ADDR_AMS_PRE, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_AMS_PRE, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getAltitude(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_AMS, ADDR_AMS_ALT, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_AMS_ALT, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getMicrophoneDB(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_AMS, ADDR_AMS_SA, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_AMS_SA, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getMicrophoneFrequency(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_AMS, ADDR_AMS_SF, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_AMS);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_AMS_SF, bigEndian);
	
	}else{
		return errorCodes::commTypeNotSelected;
	}
}

uint16_t Sensors::getDistance(){
	if(selectedComm == commType::i2c){
		int16_t res = 0;
		if(i2cRead(ADDR_TRU, ADDR_TRU_DIS, res)){ return res; }
		else{ return -1; }

	}else if(selectedComm == commType::modBus){
		modbus.setSlaveID(ADDR_TRU);
		return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TRU_DIS, bigEndian);
	
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
// 		int16_t res = 0;
// 		if(i2cRead(ADDR_AIR_MIC_UV, ADDR_SF1, res)){ return res; }
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
// 		int16_t res = 0;
// 		if(i2cRead(ADDR_AIR_MIC_UV, ADDR_SA1, res)){ return res; }
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
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
//     int16_t res = 0;
//     if(iic)
//     {
//        if(i2cRead(ADDR_TEMP,ADDR_TEMPERATURE,res))
//             return res;
//     }
//     modbus.setSlaveID(ADDR_TEMP);
//     return modbus.int16FromRegister(HOLDING_REGISTERS, ADDR_TEMPERATURE, bigEndian);
// }

bool Sensors::i2cRead(byte addr, byte reg, int16_t &val){
	try{
		WirePacker packer;
		packer.write(reg);
		packer.end();
		
		Wire.beginTransmission(addr);
		while (packer.available())
			Wire.write(packer.read());
		if(Wire.endTransmission()){
			log_e("Wire.endTransmission() error");
			// TODO restart or something
			return false;
		}

		delay(20); // TODO Fine Tunning
		slaveReq = new WireSlaveRequest(Wire, addr, MAX_SLAVE_RESPONSE_LENGTH);
		slaveReq->setRetryDelay(5);
		if(slaveReq->request(addr)){
			while (slaveReq->available()) {
				byte highByte = (byte) slaveReq->read();
				byte lowByte = (byte) slaveReq->read();
				val = (highByte << 8) | lowByte;
				// log_w("Brain I2C Event %hhu %hhu %ld", highByte, lowByte, val);
			}
			delete slaveReq;
			return true;
		}
		else{
			delete slaveReq;
			log_e("request error");
			return false;
		}
	}catch(const std::exception& e){
		log_e("err: %s", e.what());
		return false;
	}
}

bool Sensors::i2cWrite(byte addr, byte reg, int16_t val){
	try{
		WirePacker packer;
		packer.write(reg);
		packer.write(val);
		packer.end();
		
		Wire.beginTransmission(addr);
		while (packer.available())
			Wire.write(packer.read());
		if(Wire.endTransmission())
			return false;

		return true;
	}
	catch(const std::exception& e)
	{
		log_e("%s", e.what());
		return false;
	}
	
}


Sensors yetenek = Sensors();