#ifndef _4DOTLINEFOLLOWER_H_
#define _4DOTLINEFOLLOWER_H_

#define I2C_ERROR (-1)
#define I2C_OK (0)
#define RGBLINEFOLLOWER_DEFAULT_ADDRESS (0x20)
#define RGBLINEFOLLOWER_DEVICE_ID (0xFA)
#define RGBLINEFOLLOWER_DEVICE_ID_ADDR (0x00)
#define RGBLINEFOLLOWER_RGB1_ADDR (0x01)
#define RGBLINEFOLLOWER_RGB2_ADDR (0x02)
#define RGBLINEFOLLOWER_RGB3_ADDR (0x03)
#define RGBLINEFOLLOWER_RGB4_ADDR (0x04)
#define RGBLINEFOLLOWER_TURNOFFSET_L_ADDR (0x05)
#define RGBLINEFOLLOWER_TURNOFFSET_H_ADDR (0x06)
#define RGBLINEFOLLOWER_STATE_ADDR (0x07)
#define RGBLINEFOLLOWER_RGB1_BACKGROUND_THRESHOLD_ADDR (0x08)
#define RGBLINEFOLLOWER_RGB2_BACKGROUND_THRESHOLD_ADDR (0x09)
#define RGBLINEFOLLOWER_RGB3_BACKGROUND_THRESHOLD_ADDR (0x0A)
#define RGBLINEFOLLOWER_RGB4_BACKGROUND_THRESHOLD_ADDR (0x0B)
#define RGBLINEFOLLOWER_RGB1_TRACK_THRESHOLD_ADDR (0x0C)
#define RGBLINEFOLLOWER_RGB2_TRACK_THRESHOLD_ADDR (0x0D)
#define RGBLINEFOLLOWER_RGB3_TRACK_THRESHOLD_ADDR (0x0E)
#define RGBLINEFOLLOWER_RGB4_TRACK_THRESHOLD_ADDR (0x0F)
#define RGBLINEFOLLOWER_GET_VERSION_ADDR (0x10)
#define RGBLINEFOLLOWER_STUDY_ADDR (0x31)
#define RGBLINEFOLLOWER_SET_RGB_ADDR (0x32)
#define RGB1_INDEX 0
#define RGB2_INDEX 1
#define RGB3_INDEX 2
#define RGB4_INDEX 3
#define RGBLINEFOLLOWER_NUM (0x04)
#define ADDRESS1 0
#define ADDRESS2 1
#define ADDRESS3 2
#define ADDRESS4 3
#define STUDY_IDLE 0
#define STUDY_BACKGROUND 1
#define STUDY_TRACK 2
#define RGB_COLOUR_RED 1
#define RGB_COLOUR_GREEN 2
#define RGB_COLOUR_BLUE 3

#include <Wire.h>

#include "port.h"

class rgblinefollower : private port {
   public:
    rgblinefollower(int port_num, uint8_t address);
    int8_t setRGBColour(uint8_t colour);
    uint8_t getPositionState(void);
    void updataAllSensorValue(void);

   private:
    
    int8_t writeData(uint8_t start, const uint8_t *pData, uint8_t size);
    int8_t readData(uint8_t start, uint8_t *buffer, uint8_t size);
    int8_t writeReg(uint8_t reg, uint8_t data);
    uint8_t i2cData[25];
    uint8_t adcOutput[RGBLINEFOLLOWER_NUM];
    uint8_t Device_Address;
    float Kp;
    int16_t positionOffset;
    uint8_t positionState;
    uint8_t study_types;
    uint32_t iic_error_count;
    unsigned long updata_time;
};

#endif