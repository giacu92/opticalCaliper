//
//  opticalCaliper.h
//  opticalCaliper
//
//  Created by Giacomo Mammarella on 23/01/17.
//  Copyright © 2017 Giacomo Mammarella. All rights reserved.
//

#ifndef opticalCaliper_h
#define opticalCaliper_h

#include "Arduino.h"

#define const1 494914
#define const2 99.22e-4

class opticalCaliper {

private:
    int clockPin = 0;   // default clockPin = 4
    int dataPin  = 0;   // default dataPin  = 5
    int32_t reading = 0x00;
    int32_t reading_temp = 0x00;    // to avoid reading value during conversion
    
    unsigned long prev_time  = 0;
    unsigned long break_time = 0;
    int counter = 0;
    
    void readInterrupt(void);
    
public:
    opticalCaliper();
    opticalCaliper(int ckPin, int DataPin);
    
    void setClockPin(int ckPin  );
    void setDataPin (int DataPin);
    int  getClockPin(void);
    int  getDataPin (void);
    
    int32_t read(void);    // returns the read bytes
    void readISR(void);       // uses ISR to read bytes
    
    double mmRead (void);    // returns the read value in millimeters
    double inRead (void);    // returns the read value in inches
    double mmReadInt(void);
};

#endif /* opticalCaliper_h */
