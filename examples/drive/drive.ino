#include <Arduino.h>
#include <Wire.h>
#include <BULLM_ExtendMotor.h>

BULLM_ExtendMotor motor(0x7F);

void setup() {
    Wire.begin(); // 初始化I2C
    motor.begin(); // 初始化扩展版
    motor.setPWMFreq(1000); // 将PWM频率设置为1000Hz
}

void speed_all(int speed){
    for (int i = 0; i < 8; ++i) {
        motor.setSpeed(i, speed);
    }
}

void loop() {
    speed_all(127);
    delay(1000);
    speed_all(255);
    delay(1000);
    motor.stopAll();
    delay(1000);
    speed_all(-127);
    delay(1000);
    speed_all(-255);
    delay(1000);
    motor.stopAll();
    delay(1000);
}