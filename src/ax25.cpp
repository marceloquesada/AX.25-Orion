
#include "DHT11.h"


DHT11::DHT11(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}


