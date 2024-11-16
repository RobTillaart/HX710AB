
[![Arduino CI](https://github.com/RobTillaart/HX710AB/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![Arduino-lint](https://github.com/RobTillaart/HX710AB/actions/workflows/arduino-lint.yml/badge.svg)](https://github.com/RobTillaart/HX710AB/actions/workflows/arduino-lint.yml)
[![JSON check](https://github.com/RobTillaart/HX710AB/actions/workflows/jsoncheck.yml/badge.svg)](https://github.com/RobTillaart/HX710AB/actions/workflows/jsoncheck.yml)
[![GitHub issues](https://img.shields.io/github/issues/RobTillaart/HX710AB.svg)](https://github.com/RobTillaart/HX710AB/issues)

[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/HX710AB/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/HX710AB.svg?maxAge=3600)](https://github.com/RobTillaart/HX710AB/releases)
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/robtillaart/library/HX710AB.svg)](https://registry.platformio.org/libraries/robtillaart/HX710AB)


# HX710AB

Arduino library for the HX710A and HX710B 24-Bit ADC.


## Description

**Experimental**

This library provides two classes to read the HX710A and the HX710B ADC.

(from datasheet)

_The HX710(A/B) is a precision 24-bit analog-to-digital converter (ADC) with built-in
temperature sensor (HX710A) or DVDD, AVDD voltage difference detection (HX710B).
It’s designed for weigh scales and industrial control applications to interface
directly with a bridge sensor._

The HX710A can read the internal temperature.

THe HX710B can read the DVDD and AVDD supply voltage difference.

The HX710 has no means to detect errors, however several readings without noise
especially zero's might be an indication that something is wrong.

The HX710 is closely related to the HX711 which has more features.
These are not 1-to-1 replaceable devices.


### Performance

Performance depends on platform used and on the time to make a measurement.
The latter is either 10 or 40 Hz, which possibly means optional 100 or 25
milliseconds extra waiting time. (needs investigations)


### Related

- https://github.com/RobTillaart/HX710AB  this library.
- https://github.com/RobTillaart/HX711  for load cells.
- https://github.com/RobTillaart/HX711_MP  for load cells with multipoint calibration.
- https://swharden.com/blog/2022-11-14-hx710b-arduino/  usage with pressure sensor.
- https://http://www.aviaic.com/  (manufacturer)
- https://github.com/RobTillaart/weight  conversions


### Test

Tested HX710B with Arduino UNO.
- raw readings work
- pressure sensor drifts.
- two sensors tested have very different "zero point"
- TODO investigate is calibration, mapping on actual pressure (HOW).


## Interface

```cpp
#include "HX710AB.h"
```

### Constructor

Two classes:

- **HX710A(uint8_t dataPin, uint8_t clockPin)** constructor.
- **HX710B(uint8_t dataPin, uint8_t clockPin)** constructor.
- **void begin(bool fastProcessor = false)** initialises pins.
The fastProcessor option adds a 1 uS delay for each clock half-cycle
to keep the time greater than 200 nS. 
If data does not makes sense, not stable one can try this flag.

### Read, synchronous

- **int32_t read(bool differential = true)** powers up the device,
reads from the device, sets the mode for the **next** read.
The default parameter is true as differential readings are most used.
See table below.
- **uint32_t lastTimeRead()** returns last time a value was read in milliseconds.
- **int32_t lastValueRead()** returns last read value, note this can be
differential or other. The user should keep track of this.

|  differential  |  HX710A         |  HX710B         |  notes    |
|:--------------:|:---------------:|:---------------:|:---------:|
|   true         |  differential   |  differential   |  default  |
|   false        |  temperature    |  DVDD and AVDD  |

### Read, asynchronous

As the device might be blocking for up to 100 millis when using the synchronous
**read()**, the library offers an async way to read the device. 
This allows the user to do other tasks instead of active waiting.
In fact the **read()** is implemented with this async interface.

- **void request()** wakes up the device to make a measurement.
- **bool isReady()** checks if a measurement is ready.
- **int32_t fetch(bool differential = true)** 
reads from the device, sets the mode for the **next** read.
The default parameter is true as differential readings are most used.
See table above.

### Calibration

TODO


### Power

- **void powerDown()** puts the device in sleep mode (after 60 us).
- **void powerUp()** wakes up device.

Note the **read()** function automatically wakes up the device.

## Future

#### Must

- improve documentation

#### Should

- test extensively
- implement calibration (HOW).
  - zero point based (like HX711)
  - two point based P1, P2  ```y = y1 + (x-x1)*(y2-y1)/(x2-x1)```
  - converting to units / temperature  (See HX711)

#### Could

- extend unit tests(?)
- more examples.
- extend performance test sketch
- AVR optimized code - see FastShiftIn.
  (low gain as sensor blocks at 10/40 Hz)

#### Wont

- bool isPowerUp();  //  needed?
- void powerUp() not needed, as read does this.

## Support

If you appreciate my libraries, you can support the development and maintenance.
Improve the quality of the libraries by providing issues and Pull Requests, or
donate through PayPal or GitHub sponsors.

Thank you,


