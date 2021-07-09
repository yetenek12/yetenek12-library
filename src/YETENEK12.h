#ifndef YETENEK12_H
#define YETENEK12_H

#include <Wire.h>
#include <SoftwareSerial.h>
#include <SensorModbusMaster.h>
#include <WireSlaveRequest.h>

#define HOLDING_REGISTERS 0x03
#define INPUT_REGISTERS 0x04

#define MAX_SLAVE_RESPONSE_LENGTH 16        //default was 32
#define MODBUS_SPEED 38400

#define ADDR_LEDM	        10	//LED Mode(0 = Auto, 1 Dim Red, 2 Dim Green, 3 Dim Blue, 4 Dim White, 5 Red, 6 Green, 7 Blue, 8 White, 9 Fl. Red, 10 Fl. Green, 11 Fl. Blue, 12 Fl. White)  
#define ADDR_LEDR	        ADDR_LEDM+1
#define ADDR_LEDG           ADDR_LEDM+2
#define ADDR_LEDB           ADDR_LEDM+3
#define ADDR_LEDW           ADDR_LEDM+4
#define ADDR_VSUP           19	//Supply Voltage

// Air-Mic-UV Module
#define ADDR_AIR_MIC_UV     20
#define ADDR_SF1	        ADDR_AIR_MIC_UV+1	//Sound Frequency
#define ADDR_SA1	        ADDR_AIR_MIC_UV+2	//Amplitude
#define ADDR_SF2    	    ADDR_AIR_MIC_UV+3
#define ADDR_SA2	        ADDR_AIR_MIC_UV+4

// Temp
#define ADDR_TEMPERATURE    ADDR_AIR_MIC_UV+5
#define ADDR_HUMIDITY	    ADDR_AIR_MIC_UV+6
#define ADDR_PRESSURE	    ADDR_AIR_MIC_UV+7
#define ADDR_GAS	        ADDR_AIR_MIC_UV+8

// UV
#define ADDR_UVA            ADDR_AIR_MIC_UV+9
#define ADDR_UVB            ADDR_AIR_MIC_UV+10
#define ADDR_UVC            ADDR_AIR_MIC_UV+11
#define ADDR_UVV            ADDR_AIR_MIC_UV+12    //Vacuum UV
#define ADDR_UVIN           ADDR_AIR_MIC_UV+13    //UV Index



//TOF Module
#define ADDR_TOF            40
#define ADDR_DISTANCE	    ADDR_TOF+1
#define ADDR_DIS_STATUS	    ADDR_TOF+2
#define ADDR_DRM	        ADDR_TOF+3	//Distance Reading Mode

//RGB SENSOR TCS34725
#define ADDR_RGB            55
#define ADDR_R              ADDR_RGB
#define ADDR_G              ADDR_RGB+1
#define ADDR_B              ADDR_RGB+2

//OLED
#define ADDR_OLED           60 //60 or 61

//PT1000 MAX31865 TEMPERATURE SENSOR
#define ADDR_TEMP           65
//#define ADDR_TEMPERATURE    50

//CCS811 AIR QUALITY
#define ADDR_AQ             70
#define ADDR_CO2            ADDR_AQ
#define ADDR_TVOC           ADDR_AQ+1
#define ADDR_H2             ADDR_AQ+2
#define ADDR_ETH            ADDR_AQ+3

#define ADDR_ADC         80
#define ADDR_ADCS1       ADDR_ADC+1         //Settings
#define ADDR_ADCS2       ADDR_ADC+2         //Settings
#define ADDR_A0          ADDR_ADC+3
#define ADDR_A1          ADDR_ADC+4
#define ADDR_A2          ADDR_ADC+5
#define ADDR_A3          ADDR_ADC+6
#define ADDR_A4          ADDR_ADC+7
#define ADDR_A10         ADDR_ADC+13

//ICM-20948 9DoF Sensor
#define ADDR_DOF9        95
#define ADDR_ACCX        ADDR_DOF9
#define ADDR_ACCY        ADDR_DOF9+1
#define ADDR_ACCZ        ADDR_DOF9+2
#define ADDR_GYRX        ADDR_DOF9+3
#define ADDR_GYRY        ADDR_DOF9+4
#define ADDR_GYRZ        ADDR_DOF9+5
#define ADDR_MAGX        ADDR_DOF9+6
#define ADDR_MAGY        ADDR_DOF9+7
#define ADDR_MAGZ        ADDR_DOF9+8
#define ADDR_HDG         ADDR_DOF9+9
#define ADDR_TEMP9       ADDR_DOF9+10
#define ADDR_ACCMODE     ADDR_DOF9+11
#define ADDR_GYRMODE     ADDR_DOF9+12
#define ADDR_CMPMODE     ADDR_DOF9+13


#define ADDR_MOTOR       85
#define ADDR_MOTOR_MODE  ADDR_MOTOR
#define ADDR_SDIR        ADDR_MOTOR+1             //Set direction
#define ADDR_SSPD        ADDR_MOTOR+2           //Set speed
#define ADDR_CDIR        ADDR_MOTOR+3             //Current direction
#define ADDR_CSPD        ADDR_MOTOR+4             //Current speed
#define ADDR_ACONS       ADDR_MOTOR+5             //Current consumption
#define ADDR_ALIMIT      ADDR_MOTOR+6             //Current consumption


class Sensors
{
    public:
        HardwareSerial* modbusSerial;
        modbusMaster* modbus;
        WireSlaveRequest* slaveReq;

        int selectedComm = -1;

        Sensors();

        void init(int);

        enum commType{
            modBus,
            i2c
        };

        enum errorCodes{
            commTypeNotSelected = -2,
        };

        // byte checkComm(modbusMaster,TwoWire,byte addr);

        int16_t getTemperature();
        uint16_t getHumidity();
        int16_t getPressure();
        uint16_t getGas();

        int16_t getSoundFreq();
        int16_t getSoundAmplitude();

        int16_t getDistance();
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