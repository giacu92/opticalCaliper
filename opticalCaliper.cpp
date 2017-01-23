//
//  opticalCaliper.cpp
//  opticalCaliper
//
//  Created by Giacomo Mammarella on 23/01/17.
//  Copyright © 2017 Giacomo Mammarella. All rights reserved.
//

#include "opticalCaliper.h"

opticalCaliper::opticalCaliper()
{
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin,  OUTPUT);
    
    this->clockPin = 4;
    this->dataPin  = 5;
    
}

opticalCaliper::opticalCaliper(int ckPin, int DataPin)
{
    opticalCaliper();
    
    this->clockPin = ckPin;
    this->dataPin  = DataPin;
}

void opticalCaliper::setClockPin(int ckPin)
{
    this->clockPin = ckPin;
}

void opticalCaliper::setDataPin(int DataPin)
{
    this->dataPin = DataPin;
}

int opticalCaliper::getClockPin(void)
{
    return this->clockPin;
}

int opticalCaliper::getDataPin(void)
{
    return this->dataPin;
}

int32_t opticalCaliper::read(void)
{
    this->reading = 0; // azzeramanto
    unsigned long tempMicros = micros();
    
    do{}    while(digitalRead(clockPin) == LOW);
    
    if(micros() - tempMicros > 3000) // se mi trovo al primo impulso del treno avvio la lettura altrimenti salto
    {
        for (int i=0;i<=20;i++)
        {
            do{}while(digitalRead(clockPin) == HIGH);      // alla fine dell'impulso di clock leggo quello di data
            if(digitalRead(dataPin) == 1)
            {
                bitSet(reading, i);
            }
            do{}    while(digitalRead(clockPin) == LOW);       // attendo il prossimo impulso di clock
        }
        //value2 = (494914 - reading) / 100.00 * 0.9922;
        return this->reading;
    }  
    else
    {
        read();
    }
}

double opticalCaliper::mmRead()
{
    return (double)((const1 - this->read()) * const2);
}

double opticalCaliper::inRead()
{
    return (double)(this->mmRead()/25.4);
}
