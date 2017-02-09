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
    digitalWrite(clockPin, LOW); // mi assicuro che il clock sia basso
    
    this->clockPin = 4;
    this->dataPin  = 5;
    
    this->break_time = 3000;
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

double opticalCaliper::toMillimeter(int32_t data)
{
    return (double)((const1 - data) * const2);
}

double opticalCaliper::read(void)
{
    this->reading = 0; //azzeramanto
    unsigned long tempMicros = 0;
    
    for (int i=0; i<=20; i++)
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
        
        digitalWrite(clockPin, LOW);
        _delay_us(1);
        do{ }    while (micros()-tempMicros < 13);  //attendo finchè non ho completato un ciclo di clock (freq ~77KHz -> 13us)
    }
    
    return this->toMillimeter(reading);
        
}
