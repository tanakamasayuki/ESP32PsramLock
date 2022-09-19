#include "ESP32PsramLock.h"

ESP32PsramLock psramLock;

void printMem() {
  Serial.printf("heap_caps_get_free_size(MALLOC_CAP_SPIRAM)            : %7d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM) );
  Serial.printf("heap_caps_get_free_size(MALLOC_CAP_INTERNAL)          : %7d\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL) );
  Serial.printf("heap_caps_get_free_size(MALLOC_CAP_DEFAULT)           : %7d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT) );
  Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM)   : %7d\n", heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM) );
  Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL) : %7d\n", heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL) );
  Serial.printf("heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT)  : %7d\n", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT) );
  Serial.println();
}

void setup() {
  void *p;

  Serial.begin(115200);
  delay(1000);
  Serial.println("Setup");
  printMem();

  // PSRAM Lock
  Serial.println("lock");
  psramLock.Lock();
  printMem();

  // Processes that do not want to use PSRAM. (library initialization)
  Serial.println("malloc");
  p = malloc(10000);
  Serial.printf(" p = %8lX\n", p);
  printMem();

  // Unlock
  Serial.println("unlock");
  psramLock.Unlock();
  printMem();

  // Use PSRAM
  Serial.println("malloc");
  p = malloc(10000);
  Serial.printf(" p = %8lX\n", p);
  printMem();
}

void loop() {
}
