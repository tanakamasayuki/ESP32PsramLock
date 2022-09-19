#ifndef __ESP32PSRAMLOCK_H__
#define __ESP32PSRAMLOCK_H__

class ESP32PsramLock {
  private:
    static const int maxLockCount = 32;
    int lockCount;
    void* _lockList[maxLockCount];

  public:
    ESP32PsramLock() {
      lockCount = 0;
      for (int i = 0; i < maxLockCount; i++) {
        _lockList[i] = NULL;
      }
    }

    void Lock(void) {
      for (int i = 0; i < maxLockCount; i++) {
        _lockList[i] = heap_caps_malloc(heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM), MALLOC_CAP_SPIRAM);
        if (_lockList[i] == NULL) {
          break;
        }
        lockCount++;
      }
    }

    void Unlock(void) {
      for (int i = 0; i < lockCount; i++) {
        free(_lockList[i]);
        _lockList[i] = NULL;
      }
      lockCount = 0;
    }
};

#endif
