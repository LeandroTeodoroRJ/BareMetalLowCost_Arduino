/*
 * Description: ADXL345 I2C driver
 * Hostpage: https://github.com/LeandroTeodoroRJ/ESP8266
 * Stable: Yes
 * Version: 1.0.0
 * Last Uptate: 24.04.26
 * Dependences: No
 * Current: Yes
 * Maintainer: leandroteodoro.enganharia@gmail.com
 * Architecture: ModeMCU Ver3.0 - ESP8266
 * Compile/Interpreter: Arduino IDE Ver 2.3.2
 * Access: Public
 * Changelog: No
 * Readme and Documents: No
 * Links: No
 * Other Notes: The input is defined by GPIO number, not Dx number.
 *
 */
 

#include <Wire.h>

#define ADXL345_I2C_ADDR 0x53
#define ADXL345_POWER_CTL 0x2D
#define ADXL345_DATAX0   0x32

float xg_force = 0.0;
float yg_force = 0.0;
float zg_force = 0.0;

void adxl_update(){
  static bool initialized = false;
  if (!initialized) {
    Wire.begin();
    // Enable measurement
    Wire.beginTransmission(ADXL345_I2C_ADDR);
    Wire.write(ADXL345_POWER_CTL);
    Wire.write(0x08); // Measure bit
    Wire.endTransmission();
    initialized = true;
  }

  Wire.beginTransmission(ADXL345_I2C_ADDR);
  Wire.write(ADXL345_DATAX0);
  Wire.endTransmission(false); // restart
  Wire.requestFrom(ADXL345_I2C_ADDR, 6, true);

  if (Wire.available() >= 6) {
    int16_t x = Wire.read() | (Wire.read() << 8);
    int16_t y = Wire.read() | (Wire.read() << 8);
    int16_t z = Wire.read() | (Wire.read() << 8);

    // 4mg / LSB in full resolution
    xg_force = x * 0.0039;
    yg_force = y * 0.0039;
    zg_force = z * 0.0039;
  }
}