#include "4dotLineFollower.h"

#include "config.h"

rgblinefollower::rgblinefollower(int port_num, uint8_t address)
    : port(port_num - 1) {
    pinMode(port::pin.s1, OUTPUT);
    pinMode(port::pin.s2, OUTPUT);
    if (address == ADDRESS1) {
        digitalWrite(port::pin.s1, HIGH);
        digitalWrite(port::pin.s2, HIGH);
    } else if (address == ADDRESS2) {
        digitalWrite(port::pin.s1, LOW);
        digitalWrite(port::pin.s2, HIGH);
    } else if (address == ADDRESS3) {
        digitalWrite(port::pin.s1, HIGH);
        digitalWrite(port::pin.s2, LOW);
    } else if (address == ADDRESS4) {
        digitalWrite(port::pin.s1, LOW);
        digitalWrite(port::pin.s2, LOW);
    } else {
        digitalWrite(port::pin.s1, HIGH);
        digitalWrite(port::pin.s2, HIGH);
        address = ADDRESS1;
    }

    Device_Address = RGBLINEFOLLOWER_DEFAULT_ADDRESS + address;

    Kp = 0.3;
    study_types = STUDY_IDLE;
    iic_error_count = 0;

    Wire.begin();
    delay(10);
#ifdef DEBUG
    debug->log(F("rgb line follower has benn initialized"));
#endif
}

int8_t rgblinefollower::setRGBColour(uint8_t colour) {
    int8_t return_value = 0;
    uint8_t data = colour;
    return_value = writeReg(RGBLINEFOLLOWER_SET_RGB_ADDR, data);
    return (return_value);
}
int8_t rgblinefollower::writeData(uint8_t start, const uint8_t *pData,
                                  uint8_t size) {
    int8_t return_value = 0;
    Wire.beginTransmission(Device_Address);
    return_value = Wire.write(start);
    if (return_value != 1) {
        return (I2C_ERROR);
    }
    Wire.write(pData, size);
    return_value = Wire.endTransmission(true);
    return (return_value);
}

int8_t rgblinefollower::writeReg(uint8_t reg, uint8_t data) {
    int8_t return_value = 0;
    return_value = writeData(reg, &data, 1);
    delay(5);
    return (return_value);
}
int8_t rgblinefollower::readData(uint8_t start, uint8_t *buffer, uint8_t size) {
    int16_t i = 0;
    int8_t return_value = 0;

    Wire.beginTransmission(Device_Address);
    return_value = Wire.write(start);
    if (return_value != 1) {
        return (I2C_ERROR);
    }
    return_value = Wire.endTransmission(false);
    if (return_value != 0) {
        return (return_value);
    }
    delayMicroseconds(1);
    Wire.requestFrom(Device_Address, size, (uint8_t) true);
    while (Wire.available() && i < size) {
        buffer[i++] = Wire.read();
    }
    delayMicroseconds(1);
    if (i != size) {
        return (I2C_ERROR);
    }
    return (0);
}
void rgblinefollower::updataAllSensorValue(void) {
    int8_t return_value;
    int16_t temp_positionOffset;
    return_value = readData(RGBLINEFOLLOWER_DEVICE_ID_ADDR, &i2cData[0], 8);
    if (return_value == I2C_OK) {
        if (i2cData[RGBLINEFOLLOWER_DEVICE_ID_ADDR] ==
            RGBLINEFOLLOWER_DEVICE_ID) {
            adcOutput[RGB1_INDEX] = i2cData[RGBLINEFOLLOWER_RGB1_ADDR];
            adcOutput[RGB2_INDEX] = i2cData[RGBLINEFOLLOWER_RGB2_ADDR];
            adcOutput[RGB3_INDEX] = i2cData[RGBLINEFOLLOWER_RGB3_ADDR];
            adcOutput[RGB4_INDEX] = i2cData[RGBLINEFOLLOWER_RGB4_ADDR];
            temp_positionOffset = (int16_t)(
                i2cData[RGBLINEFOLLOWER_TURNOFFSET_L_ADDR] |
                ((uint16_t)i2cData[RGBLINEFOLLOWER_TURNOFFSET_H_ADDR] << 8));
            temp_positionOffset = (int16_t)(Kp * temp_positionOffset);
            positionOffset = constrain(temp_positionOffset, -512, 512);
            positionState = i2cData[RGBLINEFOLLOWER_STATE_ADDR] & 0x0F;
            study_types = (i2cData[RGBLINEFOLLOWER_STATE_ADDR] >> 4) & 0x03;
        } else {
            iic_error_count++;
        }
    }
}
uint8_t rgblinefollower::getPositionState(void) { return positionState; }
