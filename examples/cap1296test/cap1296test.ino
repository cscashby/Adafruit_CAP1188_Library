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
 
#include <Wire.h>
#include <SPI.h>
#include "CAP1296_Library/cscashby_CAP1296.h"

// For I2C, connect SDA to your Arduino's SDA pin, SCL to SCL pin
// On UNO/Duemilanove/etc, SDA == Analog 4, SCL == Analog 5
// On Leonardo/Micro, SDA == Digital 2, SCL == Digital 3
// On Mega/ADK/Due, SDA == Digital 20, SCL == Digital 21

// Use I2C, no reset pin!
cscashby_CAP1296 cap = cscashby_CAP1296();

void setup() {
  Serial.begin(9600);
  Serial.println("CAP1296 test!");

  // Defaults to i2c address 0x28
  if (!cap.begin()) {
    Serial.println("CAP1296 not found");
    while (1);
  }
  Serial.println("CAP1296 found!");
}

void loop() {
  uint8_t touched = cap.touched();

  if (touched == 0) {
    // No touch detected
    return;
  }
  
  for (uint8_t i=0; i<6; i++) {
    if (touched & (1 << i)) {
      Serial.print("C"); Serial.print(i+1); Serial.print("\t");
    }
  }
  Serial.println();
  delay(200);
}

