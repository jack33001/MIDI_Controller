#ifndef SENSOR_H
#define SENSOR_H

#include "stm32f4xx_hal.h"
#include <vector>

class I2CSensor {
public:
  I2CSensor(I2C_HandleTypeDef* i2cHandle, uint8_t address);
  std::vector<uint8_t> readData(uint8_t regAddress, uint8_t size);

private:
  I2C_HandleTypeDef* i2cHandle;
  uint8_t address;
};

#endif /* SENSOR_H */
