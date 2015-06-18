/**************************************************************************/
/*! 
    @file     DS1807.cpp
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
	This is a library for the Microchip Digital Potentiometer series.

	@section  HISTORY

    2015-Jun-18  - First release, C. Schnarel
*/
/**************************************************************************/

#include "DS1807.h"

/** Default constructor, uses default I2C address.
 * @see DS1807_DEFAULT_ADDRESS
 */
DS1807::DS1807() {
    devAddr = DS1807_DEFAULT_ADDRESS;
}

/** Specific address constructor.
 * @param address I2C address
 * @see DS1807_DEFAULT_ADDRESS
 */
DS1807::DS1807(uint8_t address) {
    devAddr = address;
}

/** Power on and prepare for general usage.
 * This device is ready to use automatically upon power-up. It defaults to
 * TCON all functions enabled, WIPER at MID scale. The begin() function sets
 * these same values since a microcontroller reset did not necessarily restart the device.
 */
void DS1807::begin() {
  //setTCON(DS1807_TCON_ALL_EN);	// enable all functions
  setWiper(DS1807_WIPER_MID);	// set to mid scale
}

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, false otherwise
 */
bool DS1807::testConnection() {
    Wire.beginTransmission(devAddr);
    return (Wire.endTransmission() == 0);
}

/** Set Wiper value
 * valid range is 0x000 = B to 0x100 = A
 * setting wiper in the range 0x101 to 0x3FF will lock wiper at A w/ inc & dec disabled
 */
bool DS1807::setWiper(uint16_t value) {
  Wire.beginTransmission(devAddr);
  uint8_t temp = ((value >> 8 & 0x01) | DS1807_CMD_WRITE);
  Wire.write(temp);
  temp = (value & 0xFF);
  Wire.write(temp);
  return (Wire.endTransmission() == 0);
}
 
/** Increment Wiper value (one step closer to A)
 * will not increment past 0x100
 */
bool DS1807::incWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(DS1807_CMD_INC);
  return (Wire.endTransmission() == 0);
}
 
/** Decrement Wiper value (one step closer to B)
 * will not decrement past 0x000
 */
bool DS1807::decWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(DS1807_CMD_DEC);
  return (Wire.endTransmission() == 0);
}
 
/** Read Wiper value
 */
int16_t DS1807::getWiper() {
  Wire.beginTransmission(devAddr);
  Wire.write(DS1807_CMD_READ);
  if(Wire.endTransmission() == 0) {
    if(Wire.requestFrom(devAddr, (uint8_t) 2) == 2) {
      buffer = Wire.read();
      buffer <<= 8;
      buffer |= Wire.read();
      return buffer;
    }
    else return -1;
  }
  else return -1;
}

