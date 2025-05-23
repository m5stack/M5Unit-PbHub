#include "M5UnitPbHub.h"

bool M5UnitPbHub::begin(TwoWire* wire, uint8_t addr, uint8_t sda, uint8_t scl, long freq)
{
    _i2c.begin(wire, sda, scl, freq);
    _addr = addr;
    return _i2c.exist(_addr);
}

bool M5UnitPbHub::digitalWrite(uint8_t ch, uint8_t index, bool value)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x00 + index);
    return _i2c.writeByte(_addr, reg, value);
}

bool M5UnitPbHub::setPWM(uint8_t ch, uint8_t index, uint8_t value)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x02 + index);
    return _i2c.writeByte(_addr, reg, value);
}

bool M5UnitPbHub::digitalRead(uint8_t ch, uint8_t index)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x04 + index);
    return _i2c.readByte(_addr, reg);
}

uint16_t M5UnitPbHub::analogRead(uint8_t ch)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x06);
    uint8_t data[2];
    if (_i2c.readBytes(_addr, reg, data, 2)) {
        return (data[1] << 8) | data[0];
    }
    return 0;
}

bool M5UnitPbHub::setLEDNum(uint8_t ch, uint16_t count)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x08);
    uint8_t data[2];
    data[0] = count & 0xff;
    data[1] = count >> 8;
    return _i2c.writeBytes(_addr, reg, data, 2);
}

bool M5UnitPbHub::setLEDColor(uint8_t ch, uint8_t index, uint32_t rgb888)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x09);
    uint8_t data[5];
    data[0] = index & 0xff;
    data[1] = index >> 8;
    data[2] = (rgb888 >> 16) & 0xff;
    data[3] = (rgb888 >> 8) & 0xff;
    data[4] = rgb888 & 0xff;
    return _i2c.writeBytes(_addr, reg, data, 5);
}

bool M5UnitPbHub::fillLEDColor(uint8_t ch, uint8_t start, uint8_t count, uint32_t rgb888)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x0A);
    uint8_t data[7];
    data[0] = start & 0xff;
    data[1] = start >> 8;
    data[2] = count & 0xff;
    data[3] = count >> 8;
    data[4] = (rgb888 >> 16) & 0xff;
    data[5] = (rgb888 >> 8) & 0xff;
    data[6] = rgb888 & 0xff;
    return _i2c.writeBytes(_addr, reg, data, 7);
}

bool M5UnitPbHub::setLEDBrightness(uint8_t ch, uint8_t value)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x0B);
    return _i2c.writeByte(_addr, reg, value);
}

bool M5UnitPbHub::setServoAngle(uint8_t ch, uint8_t index, uint8_t value)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x0C + index);
    return _i2c.writeByte(_addr, reg, value);
}

bool M5UnitPbHub::setServoPulse(uint8_t ch, uint8_t index, uint16_t value)
{
    if (ch == 5) ch++;
    uint8_t reg = ((ch + 4) << 4) | (0x0E + index);

    uint8_t data[2];
    data[0] = value & 0xff;
    data[1] = value >> 8;
    return _i2c.writeBytes(_addr, reg, data, 2);
}

bool M5UnitPbHub::setLEDShowMode(uint8_t mode)
{
    return _i2c.writeByte(_addr, 0xFA, mode);
}

uint8_t M5UnitPbHub::getLEDShowMode(void)
{
    return _i2c.readByte(_addr, 0xFA);
}

uint8_t M5UnitPbHub::getFirmwareVersion(void)
{
    return _i2c.readByte(_addr, 0xFE);
}
