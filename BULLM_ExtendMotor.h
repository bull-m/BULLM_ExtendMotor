/*!
 *  @file Adafruit_PWMServoDriver.h
 *
 *  This is a library for our Adafruit 16-channel PWM & Servo driver.
 *
 *  Designed specifically to work with the Adafruit 16-channel PWM & Servo
 * driver.
 *
 *  Pick one up today in the adafruit shop!
 *  ------> https://www.adafruit.com/product/815
 *
 *  These driver use I2C to communicate, 2 pins are required to interface.
 *  For Arduino UNOs, thats SCL -> Analog 5, SDA -> Analog 4.
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  BSD license, all text above must be included in any redistribution
 */

/*!
 * 本库基于Adafruit PWM Servo Driver Library二次封装开发，该库使用了BSD许可，上方保留了源库的作者信息，感谢Adafruit的开源工作。
 *
 * 本库专为配合牛明工作室的8通道电机驱动扩展板而设计的库
 *
 * 这个驱动器使用I2C进行通信，需要2个引脚进行接口。
 * 对于Arduino UNO，这是SCL->5，SDA->4。
 */
#ifndef _BULLM_ExtendMotor_H
#define _BULLM_ExtendMotor_H
#include "Adafruit_PWMServoDriver.h"
#include <Arduino.h>

class BULLM_ExtendMotor{
public:
    BULLM_ExtendMotor();
    BULLM_ExtendMotor(const uint8_t addr);
    BULLM_ExtendMotor(const uint8_t addr, TwoWire &i2c);
    bool begin();
    void reset();
    void sleep();
    void wakeup();
    void setPWMFreq(float freq);

    void setPin(uint8_t num, uint16_t val);
    void setSpeed(uint8_t index, int value);
    void setSpeedHigh(uint8_t index, int value);
    void stopAll();
private:
    Adafruit_PWMServoDriver *pwmDriver;
    uint8_t _i2caddr;
    TwoWire *_i2c;
};

#endif