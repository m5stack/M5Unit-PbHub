/**
 * @file analog_read.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief
 * @version 0.1
 * @date 2024-03-05
 *
 *
 * @Hardwares: M5Core + PbHub / PbHub v1.1
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
        // only one pin supports analog reading each channel
        Serial.printf("ch:%d adc:%d\r\n", ch, pbhub.analogRead(ch));
        delay(500);
    }
}