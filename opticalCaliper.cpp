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
    this->clockPin = 4;
    this->dataPin  = 5;
    
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin,  OUTPUT);
    digitalWrite(clockPin, LOW); // mi assicuro che il clock sia basso
}

opticalCaliper::opticalCaliper(int ckPin, int DataPin)
{
    this->clockPin = ckPin;
    this->dataPin  = DataPin;
    
    pinMode(this->clockPin, OUTPUT);
    pinMode(this->dataPin,  OUTPUT);
    digitalWrite(this->clockPin, LOW); // mi assicuro che il clock sia basso
}

opticalCaliper::opticalCaliper(int ckPin, int DataPin1, int DataPin2)
{
    #define DUAL_CALIPER
    
    opticalCaliper(ckPin, DataPin1);
    this->dataPin2 = DataPin2;
    
    pinMode(this->dataPin2, OUTPUT);
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

double opticalCaliper::toMillimeter(int32_t data)
{
    return (double)((const1 - data) * const2);
}

double* opticalCaliper::read(void)
{
    this->reading = 0; //azzeramanto
    unsigned long tempMicros = 0;
    double values[2] = {0, 0};
    
    for (int i=0; i<32; i++)
    {
        tempMicros = micros();
        //alzo il fronte di clock sul pin di clock
        digitalWrite(clockPin, HIGH);
        _delay_us(1);   //attendo 1us per stabilizzare il clock
        
        //leggo il bit in ingresso e setto il risultato
        if (digitalRead(dataPin) == HIGH)
        {
            bitSet(reading, i);
        }
        
        #ifdef DUAL_CALIPER
            if (digitalRead(this->dataPin2) == HIGH)
            {
                bitSet(reading2, i);
            }
        #endif
        
        digitalWrite(clockPin, LOW);
        _delay_us(1);
        do{ }    while (micros()-tempMicros < 13);  //attendo finchè non ho completato un ciclo di clock (freq ~77KHz -> 13us)
    }
    
    values[0] = double(reading );
    values[1] = double(reading2);
    
    return values; // ritorno il puntatore all'array
        
}
