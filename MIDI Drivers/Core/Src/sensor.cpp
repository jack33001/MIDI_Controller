#include "sensor.h"

I2CSensor::I2CSensor(I2C_HandleTypeDef* i2cHandle, uint8_t address) {
  i2cHandle_ = i2cHandle;
  address_ = address;
}

std::vector<uint8_t> I2CSensor::readData(uint8_t regAddress, uint8_t size) {
  std::vector<uint8_t> data(size);
  HAL_I2C_Mem_Read(i2cHandle_, address_, regAddress, I2C_MEMADD_SIZE_8BIT, data.data(), size, HAL_MAX_DELAY);
  return data;
}

void I2CSensor::writeData(uint8_t regAddress, std::vector<uint8_t> data) {
  HAL_I2C_Mem_Write(i2cHandle_, address_, regAddress, I2C_MEMADD_SIZE_8BIT, data.data(), data.size(), HAL_MAX_DELAY);
}
