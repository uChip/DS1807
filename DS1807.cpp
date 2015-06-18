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
 * Sets wiper position to 1 above mute and zero crossing activated.
 */
void DS1807::begin() {
  activateZC(); //turn on zero crossing
  setBothWipers((uint8_t)DS1807_WIPER_MIN);	// 1 above mute
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
 * valid range is 0x00 = H to 0x40 = L
 */
bool DS1807::setBothWipers(uint16_t value) {
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t)DS1807_CMD_WRBOTH);
  uint8_t temp = (value & 0xFF);
  Wire.write(temp);
  return (Wire.endTransmission() == 0);
}
 
/** Set Wiper value
 * valid range is 0x00 = H to 0x40 = L
 */
bool DS1807::setBothWipers(uint8_t value) {
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t)DS1807_CMD_WRBOTH);
  Wire.write(value);
  return (Wire.endTransmission() == 0);
}
  
/** Set Wiper0 value
 * valid range is 0x00 = H to 0x40 = L
 */
bool DS1807::setWiper0(uint8_t value) {
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t)DS1807_CMD_WRPOT0);
  Wire.write(value);
  return (Wire.endTransmission() == 0);
}
  
/** Set Wiper1 value
 * valid range is 0x00 = H to 0x40 = L
 */
bool DS1807::setWiper1(uint8_t value) {
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t)DS1807_CMD_WRPOT1);
  Wire.write(value);
  return (Wire.endTransmission() == 0);
}
  
/** Turn on zero crossing detection
 */
bool DS1807::activateZC(void){
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t)DS1807_CMD_ACT_ZC);
  return (Wire.endTransmission() == 0);  // returns true if no errors
}

/** Read Both Wiper values
 */
uint8_t DS1807::getWipers() {
  Wire.beginTransmission(devAddr);
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

