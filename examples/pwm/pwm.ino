/**
 * @file pwm.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 *
 * @Hardwares: M5Core + PbHub v1.1
 * @Platform Version: Arduino M5Stack Board Manager v2.1.0
 * @Dependent Library:
 * M5UnitPbHub: https://github.com/m5stack/M5Unit-PbHub
 */

#include "M5UnitPbHub.h"

M5UnitPbHub pbhub;

void setup() {
    Serial.begin(115200);
    if (!pbhub.begin(&Wire, UNIT_PBHUB_I2C_ADDR, 21, 22, 400000U)) {
        Serial.println("Couldn't find Pbhub");
        while (1) delay(1);
    }
}

void loop() {
    // ch: 0-5
    // index: 0-1
    // status: 0/1
    for (uint8_t ch = 0; ch < 6; ch++) {
        for (uint8_t index = 0; index < 2; index++) {
            for (uint8_t h = 0; h < 255; h++) {
                pbhub.setPWM(ch, index, h);
                Serial.printf("ch:%d index:%d PWM: %.1f%%\r\n", ch, index,
                              h / 255.0 * 100.0);
                delay(10);
            }
        }
    }
    delay(1000);
}
