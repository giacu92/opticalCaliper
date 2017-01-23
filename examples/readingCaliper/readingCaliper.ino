#include <opticalCaliper.h>

int clkPin  = 4;
int dataPin = 5;

opticalCaliper caliper(clkPin, dataPin);
// opticalCaliper caliper(); //<-- can also use default declaration

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Reading values:
  double mmValue = caliper.mmRead();
  double inValue = caliper.inRead();
  int32_t data   = caliper.read();

  // Printing values:
  Serial.println("distance in mm: " + mmValue + " mm");
  Serial.println("distance in in: " + inValue + " in");
  Serial.print("bytes read: ");
  Serial.println(data, BIN);
}
