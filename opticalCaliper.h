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
#define const2 99.22e-4 //calibration constant

class opticalCaliper {

private:
    int clockPin = 0;   // default clockPin = 4
    int dataPin  = 0;   // default dataPin  = 5
    int dataPin2 = 0;
    int32_t reading  = 0x00;
    int32_t reading2 = 0x00;
    
    double toMillimeter(int32_t data);
    
public:
    opticalCaliper();
    opticalCaliper(int ckPin, int DataPin);
    opticalCaliper(int ckPin, int DataPin1, int DataPin2);
    
    void setClockPin(int ckPin  );
    void setDataPin (int DataPin);
    int  getClockPin(void);
    int  getDataPin (void);
    
    double* read(void);    // returns the read value in millimeters
};

//static void readInterrupt(void);

#endif /* opticalCaliper_h */
