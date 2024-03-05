/**
 * @file digital_write_read.ino
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
        for (uint8_t index = 0; index < 2; index++) {
            pbhub.digitalWrite(ch, index, 1);
            delay(300);
            Serial.printf("ch:%d index:%d\r\n", pbhub.digitalRead(ch, index),
                          index);
            delay(300);
            pbhub.digitalWrite(ch, index, 0);
            Serial.printf("ch:%d index:%d\r\n", pbhub.digitalRead(ch, index),
                          index);
            delay(300);
        }
    }
}
