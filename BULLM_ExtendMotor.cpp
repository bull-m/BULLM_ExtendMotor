#include "BULLM_ExtendMotor.h"

BULLM_ExtendMotor::BULLM_ExtendMotor(){
    pwmDriver = new Adafruit_PWMServoDriver();
}
BULLM_ExtendMotor::BULLM_ExtendMotor(const uint8_t addr){
    pwmDriver = new Adafruit_PWMServoDriver(addr);
}
BULLM_ExtendMotor::BULLM_ExtendMotor(const uint8_t addr, TwoWire &i2c){
    pwmDriver = new Adafruit_PWMServoDriver(addr, i2c);
}

/*!
 *  @brief  设置I2C接口和硬件
 *  @return 如果成功则为true，否则为false
 */
bool BULLM_ExtendMotor::begin() {
    return pwmDriver->begin();
}

/*!
 *  @brief  通过I2C发送复位命令
 */
void BULLM_ExtendMotor::reset() {
    pwmDriver->reset();
}

/*!
 *  @brief  将板置于睡眠模式
 */
void BULLM_ExtendMotor::sleep() {
    pwmDriver->sleep();
}

/*!
 *  @brief 将板从睡眠中唤醒
 */
void BULLM_ExtendMotor::wakeup() {
    pwmDriver->wakeup();
}

/*!
 *  @brief  为整个芯片设置PWM频率，最高可达1.6 KHz
 *  @param  freq 尝试匹配的浮点频率
 */
void BULLM_ExtendMotor::setPWMFreq(float freq) {
    pwmDriver->setPWMFreq(freq);
}

/*!
 *  @brief  设置引脚PWM输出
 *  @param  num PWM输出引脚，从0到15
 *  @param  val 从0到4096（含）。
 */
void BULLM_ExtendMotor::setPin(uint8_t num, uint16_t val) {
    pwmDriver->setPin(num, val);
    if (val == 4096) {
        // 信号完全开启的特殊值。
        pwmDriver->setPWM(num, 4096, 0);
    } else if (val == 0) {
        // 信号完全关闭的特殊值。
        pwmDriver->setPWM(num, 0, 4096);
    } else {
        pwmDriver->setPWM(num, 0, val);
    }
}
/*!
 *  @brief  停止所有电机
 */
void BULLM_ExtendMotor::stopAll(){
    for(uint8_t i = 0; i < 8; i++){
        setSpeedHigh(i, 0);
    }
}

/*!
 *  @brief  驱动指定电机
 *  @param  index 操作的电机,从0到7
 *  @param  value -255 ~ 255 负数反转，正数正转，0停止
 */
void BULLM_ExtendMotor::setSpeed(uint8_t index, int value){
    if(value < -255) value = -255;
    if(value > 255) value = 255;
    setSpeedHigh(index, (value + 255) * 8192 / 510 -4096);
}

/*!
 *  @brief  驱动指定电机,高精度
 *  @param  index 操作的电机,从0到7
 *  @param  value -4096 ~ 4096 负数反转，正数正转，0停止
 */
void BULLM_ExtendMotor::setSpeedHigh(uint8_t index, int value){
    if(index < 0 || index > 7){
        return;
    }
    if(value < -4096) value = -4096;
    if(value > 4096) value = 4096;
    /*
     * 前进引脚和后退引脚
     * 电机0：0脚和1脚
     * 电机1：2脚和3脚
     * 电机2：4脚和5脚
     * 电机3：6脚和7脚
     * 电机4：8脚和9脚
     * 电机5：10脚和11脚
     * 电机6：12脚和13脚
     * 电机7：14脚和15脚
     */
    uint8_t forward_i = index * 2;
    uint8_t reverse_i = index * 2 + 1;
    if(value >= 0){
        setPin(forward_i, value);
        setPin(reverse_i, 0);
    } else{
        setPin(forward_i, 0);
        setPin(reverse_i, -value);
    }
}