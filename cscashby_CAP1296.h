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

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>

// The default I2C address
#define CAP1296_I2CADDR 0x28

// Some registers we use
#define CAP1296_MAIN 0x00
#define CAP1296_SENINPUTSTATUS 0x3
#define CAP1296_INTEN 0x27
#define CAP1296_MTBLK 0x2A
#define CAP1296_STANDBYCFG 0x41
#define CAP1296_LEDPOL 0x73

#define CAP1296_PRODID 0xFD
#define CAP1296_MANUID 0xFE
#define CAP1296_REV 0xFF

// And some masks
#define CAP1296_MAIN_INT 0x01

class cscashby_CAP1296 {
 public:
  // Hardware I2C
  cscashby_CAP1296();

  boolean begin(uint8_t i2caddr = CAP1296_I2CADDR);
  uint8_t readRegister(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t value);
  uint8_t touched(void);

 private:
  boolean _i2c;
  int8_t _i2caddr;
};

void receive(int byteCount);
