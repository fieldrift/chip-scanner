#pragma once

#include <stdlib.h>
#include "wokwi-api.h"

struct Chip {
public:
    static inline void Init();
    static Chip* Create();

    static const uint8_t NUM_CODES = 4;
private:
    void send(const char* code, size_t size);
    uart_dev_t port = 0;

    struct send_pin_t {
        Chip* instance;
        char const* code;
        size_t size;
    };

    send_pin_t sendPins[NUM_CODES]{};

    static void onTransmitted(void* context);
    static void sendPinStateChanged(void *context, pin_t, uint32_t);
};
