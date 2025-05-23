/**
 * @file rgb_led.ino
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

void setup()
{
    Serial.begin(115200);
    if (!pbhub.begin(&Wire, UNIT_PBHUB_I2C_ADDR, 21, 22, 100000U)) {
        Serial.println("Couldn't find Pbhub");
        while (1) delay(1);
    }
    uint8_t firmware_version = pbhub.getFirmwareVersion();
    Serial.printf("Firmware Version: %d\n", firmware_version);
    if (firmware_version < 2) {
        while (1) {
            delay(1000);
            Serial.println("Firmware Version is too old, please update the firmware");
            Serial.println("Please visit https://docs.m5stack.com/en/unit/pbhub_1.1");
        }
    }
    for (uint8_t ch = 0; ch < 6; ch++) {
        pbhub.setLEDNum(ch, 74);
        pbhub.setLEDBrightness(ch, 40);
    }
}

void loop()
{
    // ch: 0-5
    // index: 0-1
    // status: 0/1
    for (uint8_t ch = 0; ch < 6; ch++) {
        pbhub.fillLEDColor(ch, 0, 73, 0xff0000);
    }
    delay(1000);
    for (uint8_t ch = 0; ch < 6; ch++) {
        pbhub.fillLEDColor(ch, 0, 73, 0x00ff00);
    }
    delay(1000);
    for (uint8_t ch = 0; ch < 6; ch++) {
        pbhub.fillLEDColor(ch, 0, 73, 0x0000ff);
    }
    delay(1000);

    for (uint8_t ch = 0; ch < 6; ch++) {
        for (uint8_t index = 0; index < 73; index++) {
            pbhub.setLEDColor(ch, index, 0x00ff00);
            delay(20);
        }
    }
    delay(1000);
}
