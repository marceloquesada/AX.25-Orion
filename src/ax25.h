
#ifndef AX25_h
#define AX25_h

#include "Arduino.h"

class AX25
{
public:
  AX25(int pin);
  int readHumidity();
  int readTemperature();
  static String getErrorString(int errorCode);

private:
  int _pin; // Pin number used for communication with the AX25 sensor.
  byte readByte();
  void startSignal();
};

#endif
