#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include <Wire.h>
#include <SPI.h>

// The default I2C address
#define CAP1296_I2CADDR 0x29

// Some registers we use
#define CAP1296_MAIN 0x00
#define CAP1296_SENINPUTSTATUS 0x3
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
  void LEDpolarity(uint8_t x);

 private:
  boolean _i2c;
  int8_t _i2caddr;
};

