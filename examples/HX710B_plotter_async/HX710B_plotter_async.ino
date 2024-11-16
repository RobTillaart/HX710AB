//
//    FILE: HX710B_plotter_async.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour
//     URL: https://github.com/RobTillaart/HX710AB


#include "HX710AB.h"

//  adjust pins to your setup
uint8_t dataPin = 6;
uint8_t clockPin = 7;

HX710B HX(dataPin, clockPin);

float __beta;
float __alpha;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("HX710AB_LIB_VERSION: ");
  Serial.println(HX710AB_LIB_VERSION);
  Serial.println();

  HX.begin();

  //  adjust two points to your pressure sensor.
  //  calibrateUnit(x1 y1, x2, y2);
  HX.calibrateUnit( 0, 0, 1000, 10);
  //  start async
  HX.request();

}


void loop()
{
  if (HX.isReady())
  {
    Serial.println(HX.readUnit(1), 1);
  }
  //  do other tasks
}


//  -- END OF FILE --
