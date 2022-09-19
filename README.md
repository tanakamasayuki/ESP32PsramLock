# ESP32 PSRAM Lock

This library limits memory allocation from PSRAM.

## Usage
```c
#include "ESP32PsramLock.h"

ESP32PsramLock psramLock;

void setup() {
  psramLock.Lock();

  // Processes that do not want to use PSRAM. (library initialization)

  psramLock.Unlock();

  // Use PSRAM
}

void loop() {
}
```
