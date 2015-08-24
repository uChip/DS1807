/**************************************************************************/
/*! 
    @file     DS1807.h
    @author   C. Schnarel
	@license  BSD (see license.txt)
	
	This is a library for the Dallas Semiconductor Digital Potentiometer
	with zero crossing detection.

	@section  HISTORY

    2015-Jun-18  - First release, C. Schnarel
*/
/**************************************************************************/

#ifndef _DS1807_H_
#define _DS1807_H_

#ifdef ARDUINO
    #if ARDUINO < 100
        #include "WProgram.h"
    #else
        #include "Arduino.h"
    #endif
#else
    #include "ArduinoWrapper.h"
#endif

#include <Wire.h>

// I2C Address of device
#define DS1807_DEFAULT_ADDRESS	0x50	// A0,A1 & A2 are connected to GND

// Command definitions
#define DS1807_CMD_WRPOT0	0xA9
#define DS1807_CMD_WRPOT1	0xAA
#define DS1807_CMD_WRBOTH	0xAF
#define DS1807_CMD_ACT_ZC	0xBD
#define DS1807_CMD_DEACT_ZC	0xBD

// Common WIPER values
#define DS1807_WIPER_MAX	0x00
#define DS1807_WIPER_MID	0x20
#define DS1807_WIPER_MIN	0x3F
#define DS1807_WIPER_MUTE	0x40

class DS1807 {
    public:
        DS1807(void);
        DS1807(uint8_t address);
        
        void begin(void);
        bool testConnection(void);

	// Write the Wiper register
	bool setBothWipers(uint16_t value);  // returns true if no errors
        
	// Write the Wiper register
	bool setBothWipers(uint8_t value);  // returns true if no errors
        
	// Write the Wiper register
	bool setWiper0(uint8_t value);  // returns true if no errors
        
	// Write the Wiper register
	bool setWiper1(uint8_t value);  // returns true if no errors
        
	// Write the Wiper register
	bool activateZC(void);  // returns true if no errors
        
     // Read the Wiper register
     uint8_t getWipers(void);  // returns -1 if errors

    private:
        uint8_t devAddr;
        uint16_t buffer;
};

#endif /* _DS1807_H_ */
