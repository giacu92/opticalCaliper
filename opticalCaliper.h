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
//#define DEBUG_MODE

class opticalCaliper {

private:
    float calibration_factor = 0.992;
    //int32_t offset_factor    = 0;
    
    int clockPin = 4;   // default clockPin = 4
    int dataPin  = 5;   // default dataPin  = 5
    int reading  = 0;
    
public:
    opticalCaliper();
    
    void begin(int ckPin, int DataPin);
    void setClockPin(int ckPin  );
    void setDataPin (int DataPin);
    void setCalibration(float cal_factor);
    int  getClockPin(void);
    int  getDataPin (void);
    
    int read(void);    // returns the read value in millimeters
};

//static void readInterrupt(void);

#endif /* opticalCaliper_h */
