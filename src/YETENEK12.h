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
        SoftwareSerial* modbusSerial;
        modbusMaster modbus;
        WireSlaveRequest* slaveReq;

        int selectedComm = -1;

        Sensors();

        void init(); // i2c Mode
        void init(int, int, int); // ModBus Mode

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
        uint16_t getDigitalIO(int pin);
        void setDigitalIO(int pin, int value);
        uint16_t getADC(int port);
        uint16_t getADCVoltage(int port);

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
        bool i2cRead(byte,byte,int16_t&);
        bool i2cWrite(byte,byte,int16_t);

};

extern Sensors yetenek;

#endif