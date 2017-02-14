#include <opticalCaliper.h>

#define clkPin  4
#define dataPin 5

opticalCaliper caliper;

void setup()
{
  caliper.begin(clkPin, dataPin);
  Serial.begin(9600);
}

void loop()
{
  // Reading values:
  float reading = caliper.read();

  // Printing values:
  Serial.print("distance in mm: ");
  Serial.print(reading/100.00);
  Serial.println(" mm");

  delay(1000);
}
