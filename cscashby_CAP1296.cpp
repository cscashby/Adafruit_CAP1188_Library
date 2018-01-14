/*************************************************** 
  This is a library for the CAP1296 I2C/SPI 6-chan Capacitive Sensor
  The original code was taken from the Adafruit library for the CAP1188 - license below applies
  Modified and maintained by Christian Ashby.
  BSD license, all text in this comment must be included in any redistribution
  
  This is a library for the CAP1188 I2C/SPI 8-chan Capacitive Sensor
  Designed specifically to work with the CAP1188 sensor from Adafruit
  ----> https://www.adafruit.com/products/1602
  These sensors use I2C/SPI to communicate, 2+ pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "cscashby_CAP1296.h"

cscashby_CAP1296::cscashby_CAP1296() {
  _i2c = true;
}

boolean cscashby_CAP1296::begin(uint8_t i2caddr) {
  Wire.begin();
  _i2caddr = i2caddr;

  readRegister(CAP1296_PRODID);
  
  // Useful debugging info
  Serial.print("Product ID: 0x");
  Serial.println(readRegister(CAP1296_PRODID), HEX);
  Serial.print("Manuf. ID: 0x");
  Serial.println(readRegister(CAP1296_MANUID), HEX);
  Serial.print("Revision: 0x");
  Serial.println(readRegister(CAP1296_REV), HEX);
  
  if ( (readRegister(CAP1296_PRODID) != 0x69) ||
       (readRegister(CAP1296_MANUID) != 0x5D) ) {
    return false;
  }
  // allow multiple touches
  writeRegister(CAP1296_MTBLK, 0); 
  // speed up a bit
  writeRegister(CAP1296_STANDBYCFG, 0x30);
  // disable interrupts
  writeRegister(CAP1296_INTEN, 0);
  return true;
}

uint8_t  cscashby_CAP1296::touched(void) {
  uint8_t t = readRegister(CAP1296_SENINPUTSTATUS);
  if (t) {
    writeRegister(CAP1296_MAIN, readRegister(CAP1296_MAIN) & ~CAP1296_MAIN_INT);
    Serial.print("MAIN: ");
    Serial.print(readRegister(0x10), HEX);
    Serial.print("-");
    Serial.println(readRegister(CAP1296_MAIN), HEX);
  }
  return t;
}

/*********************************************************************/

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static uint8_t i2cread(void) {
  #if ARDUINO >= 100
  return Wire.read();
  #else
  return Wire.receive();
  #endif
}

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(uint8_t x) {
  #if ARDUINO >= 100
  Wire.write((uint8_t)x);
  #else
  Wire.send(x);
  #endif
}

/**************************************************************************/
/*!
    @brief  Reads 8-bits from the specified register
*/
/**************************************************************************/
uint8_t cscashby_CAP1296::readRegister(uint8_t reg) {
  Wire.beginTransmission(_i2caddr);
  i2cwrite(reg);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, 1);
  return (i2cread());
}


/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void cscashby_CAP1296::writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_i2caddr);
  i2cwrite((uint8_t)reg);
  i2cwrite((uint8_t)(value));
  Wire.endTransmission();
}

