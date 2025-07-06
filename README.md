# BULLM_ExtendMotor

本库为配合牛明工作室的8通道电机驱动扩展板而设计的库。

# 使用

## 安装

### PlatformIO

在PlatformIO中使用本库，在`platformio.ini`中添加如下内容

```ini
[env:myenv]
...
lib_deps = 
  bullm/BULLM_ExtendMotor
...
```

### Arduino IDE
在Arduino IDE中，直接在库管理器中搜索`BULLM_ExtendMotor`并安装即可。

## 简单示例

```c++
#include <Wire.h>
#include "BULLM_ExtendMotor.h"

BULLM_ExtendMotor motor(127); // 实例化，地址为127

void setup() {
    Wire.begin(4, 5); // 初始化I2C
    motor.begin(); // 初始化
    motor.setPWMFreq(1000); // 将PWM频率设置为1000Hz
    motor.setSpeed(1, 255); // 设置第1通道电机的正转速度为255
}
```


## 方法
### begin()
初始化

### setPWMFreq(uint16_t freq)  
设置PWM频率

### setSpeed(uint8_t index, int speed)  
设置指定通道的速度
* index为通道号, 从1开始，1~8
* speed为速度值，范围为-255~255，正数表示正转，负数表示反转，0表示停止。

### setSpeedHigh(uint8_t index, int speed)
设置指定通道的速度，高精度
* index为通道号, 从1开始，1~8
* speed为速度值，范围为-4096~4096，正数表示正转，负数表示反转，0表示停止。

### stopAll()
停止所有通道的电机