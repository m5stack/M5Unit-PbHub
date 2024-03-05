#ifndef _M5_UNIT_PB_HUB_H_
#define _M5_UNIT_PB_HUB_H_

#include "Arduino.h"
#include "I2C_Class.h"

#define UNIT_PBHUB_I2C_ADDR 0x61

class M5UnitPbHub {
   private:
    TwoWire *_wire;
    uint8_t _addr;
    I2C_Class _i2c;

   public:
    bool begin(TwoWire *wire = &Wire, uint8_t addr = UNIT_PBHUB_I2C_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, long freq = 400000U);

    // IO
    bool digitalWrite(uint8_t ch, uint8_t index, bool value);
    bool digitalRead(uint8_t ch, uint8_t index);
    uint16_t analogRead(uint8_t ch);

    // PWM & SERVO
    bool setPWM(uint8_t ch, uint8_t index, uint8_t value);
    bool setServoAngle(uint8_t ch, uint8_t index, uint8_t value);
    bool setServoPulse(uint8_t ch, uint8_t index, uint16_t value);

    // RGB LED
    bool setLEDNum(uint8_t ch, uint16_t count);  // default 74
    bool setLEDColor(uint8_t ch, uint8_t index, uint32_t rgb888);
    bool setLEDBrightness(uint8_t ch, uint8_t value);
    bool fillLEDColor(uint8_t ch, uint8_t start, uint8_t count,
                      uint32_t rgb888);
};

#endif
