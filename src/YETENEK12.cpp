#include "YETENEK12.h"

Sensors::Sensors(){}

void Sensors::init(int type){
    selectedComm = type;
    
    if(selectedComm == commType::i2c){
        Wire.begin();
    
    }else if(selectedComm == commType::modBus){
        modbusSerial = new HardwareSerial(1);
        modbusSerial->begin(MODBUS_SPEED, SERIAL_8N1, 26, 25);
        modbus = new modbusMaster();
        modbus->begin(ADDR_TOF, modbusSerial, 19);
    }
}

int16_t Sensors::getDistance(){
    int16_t res = 0;
    if(selectedComm == commType::i2c){
        if(i2cRead(ADDR_TOF, ADDR_DISTANCE, res)){ return res; }
        else{ return -1; }

    }else if(selectedComm == commType::modBus){
        modbus->setSlaveID(ADDR_TOF);
        return modbus->int16FromRegister(HOLDING_REGISTERS, ADDR_DISTANCE, bigEndian);
    
    }else{
        return errorCodes::commTypeNotSelected;
    }
}

void Sensors::setDistanceMode(int mode){
    if(selectedComm == commType::i2c){
        i2cWrite(ADDR_TOF, ADDR_DRM, mode);

    }else if(selectedComm == commType::modBus){
        modbus->setSlaveID(ADDR_TOF);
        modbus->uint16ToRegister(ADDR_DRM, mode);
    }
}


int16_t Sensors::getSoundFreq(){
    int16_t res = 0;
    if(selectedComm == commType::i2c){
        if(i2cRead(ADDR_AIR_MIC_UV, ADDR_SF1, res)){ return res; }
        else{ return -1; }

    }else if(selectedComm == commType::modBus){
        modbus->setSlaveID(ADDR_AIR_MIC_UV);
        return modbus->int16FromRegister(HOLDING_REGISTERS, ADDR_SF1, bigEndian);
    
    }else{
        return errorCodes::commTypeNotSelected;
    }
}

int16_t Sensors::getSoundAmplitude(){
    int16_t res = 0;
    if(selectedComm == commType::i2c){
        if(i2cRead(ADDR_AIR_MIC_UV, ADDR_SA1, res)){ return res; }
        else{ return -1; }

    }else if(selectedComm == commType::modBus){
        modbus->setSlaveID(ADDR_AIR_MIC_UV);
        return modbus->int16FromRegister(HOLDING_REGISTERS, ADDR_SA1, bigEndian);
    
    }else{
        return errorCodes::commTypeNotSelected;
    }
}

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

        delay(5); // TODO Fine Tunning
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