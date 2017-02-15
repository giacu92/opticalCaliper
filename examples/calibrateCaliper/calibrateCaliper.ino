#include <opticalCaliper.h>

#define clkPin  2
#define dataPin 3

#define max_scale 450.00 //max scale in mm

opticalCaliper caliper;

void setup()
{
  Serial.begin(9600);
  caliper.begin(clkPin, dataPin);

  delay(100);
  Serial.println("Move caliper to minimum and send ""'0'"" via serial monitor to set zero.");
}

void loop()
{
  if(Serial.available() > 0)
  {
    byte input = Serial.read();
    //Serial.println("caliper reading: " + (String)(caliper.read()/100.00) + " mm");
    
    if(input != 48 && input != 49);
    
    else if (input == 48)
    {
      caliper.setZero();  //sets the offset
      Serial.println("\nMove caliper to max aperture and send ""'1'"" via serial monitor to get calibration value.");
    }
    else if (input == 49)
    {
      float val = caliper.read()/100.00 / max_scale;
      Serial.println("reading = " + (String)(caliper.read()/100.00) + " mm");
      Serial.println("Calibration factor = " + (String)val);
    }
    else if (input == 50)
    {
      Serial.println("reading = " + (String)(caliper.read()/100.00) + " mm");
    }
  }

  delay(1000);
}
