#include <opticalCaliper.h>

int clkPin  = 4;
int dataPin = 5;

opticalCaliper caliper(clkPin, dataPin);

void setup()
{
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(clkPin), myISR, FALLING);
}

void loop()
{
  double mmValue = caliper.mmReadInt();

  // Printing values:
  Serial.print("distance in mm: ");
  Serial.print(mmValue);
  Serial.println(" mm");

  delay(1000);
}

void myISR()
{
  caliper.readInterrupt();
}
