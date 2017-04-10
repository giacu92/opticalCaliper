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
}

void opticalCaliper::begin(int ckPin, int DataPin)
{
    this->clockPin = ckPin;
    this->dataPin  = DataPin;
    
    pinMode(this->clockPin, OUTPUT);
    pinMode(this->dataPin , INPUT_PULLUP );
    digitalWrite(this->clockPin, LOW); // mi assicuro che il clock sia basso
}

void opticalCaliper::setClockPin(int ckPin)
{
    this->clockPin = ckPin;
}

void opticalCaliper::setDataPin(int DataPin)
{
    this->dataPin = DataPin;
}

void opticalCaliper::setCalibration(float cal_factor)
{
    this->calibration_factor = cal_factor;
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
    unsigned long tempMicros = 0;
    this->reading = 0x00;
    
    for (int i=0; i<32; i++)
    {
        tempMicros = micros();
        int lettura_positiva = 0;
        //alzo il fronte di clock sul pin di clock
        digitalWrite(this->clockPin, HIGH);
        //delayMicroseconds(10);
        
        //leggo il bit in ingresso e setto il risultato
        
        for (int j = 0; j<5; j++)
        {
            if (digitalRead(this->dataPin) == HIGH)
            {
                lettura_positiva += 1;
            }
        }
        if (lettura_positiva >= 3)
        {
            bitSet(this->reading, i);
        }
        
        delayMicroseconds(10);
        digitalWrite(clockPin, LOW);
        //delayMicroseconds(100);
        while (micros()-tempMicros < 100)
        {
            delayMicroseconds(10);
            //attendo finchè non ho completato un ciclo di clock (freq ~77KHz -> 13us)
        }
    }
    #ifdef DEBUG_MODE
        Serial.println("");
    #endif
    
    return  (this->reading-this->calibration_offset) * this->calibration_factor; // ritorno il puntatore all'array
}

void opticalCaliper::setZero()
{
    unsigned long tempMicros = 0;
    this->reading = 0x00;
    
    for (int i=0; i<32; i++)
    {
        tempMicros = micros();
        //alzo il fronte di clock sul pin di clock
        digitalWrite(this->clockPin, HIGH);
        delayMicroseconds(10);
        
        //leggo il bit in ingresso e setto il risultato
        if (digitalRead(this->dataPin) == HIGH)
        {
            bitSet(this->reading, i);
        }
        
        delayMicroseconds(10);
        digitalWrite(clockPin, LOW);
        //delayMicroseconds(100);
        while (micros()-tempMicros < 100)
        {
            delayMicroseconds(10);
            //attendo finchè non ho completato un ciclo di clock (freq ~77KHz -> 13us)
        }
    }

    this->calibration_offset = reading;
}
