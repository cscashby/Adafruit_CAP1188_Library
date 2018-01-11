#include "cscashby_CAP1296.h"

uint8_t mySPCR, SPCRback;

cscashby_CAP1296::cscashby_CAP1296() {
  _i2c = true;
}

boolean cscashby_CAP1296::begin(uint8_t i2caddr) {
  Wire.begin()
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
       (readRegister(CAP1296_MANUID) != 0x5D) {
    return false;
  }
  // allow multiple touches
  writeRegister(CAP1296_MTBLK, 0); 
  // speed up a bit
  writeRegister(CAP1296_STANDBYCFG, 0x30);
  return true;
}

uint8_t  cscashby_CAP1296::touched(void) {
  uint8_t t = readRegister(CAP1296_SENINPUTSTATUS);
  if (t) {
    writeRegister(CAP1296_MAIN, readRegister(CAP1296_MAIN) & ~CAP1296_MAIN_INT);
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

uint8_t cscashby_CAP1296::readRegister(uint8_t reg) {
  Wire.beginTransmission(_i2caddr);
  i2cwrite(reg);
  Wire.endTransmission();
  Wire.requestFrom(_i2caddr, 1);
  return (i2cread());
  return reply;
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
}

