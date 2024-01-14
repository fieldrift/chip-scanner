#include <string.h>
#include <stdio.h>
#include "chip.h"

namespace {
    static char const* codes[Chip::NUM_CODES]{
        "CODE1",
        "CODE2",
        "CODE3",
        "CODE4"
    };

    static char const* codePins[Chip::NUM_CODES]{
        "SEND1",
        "SEND2",
        "SEND3",
        "SEND4"
    };
}

inline void chip_init() {
    Chip::Init();
}

void Chip::Init() {
    const auto inst = Chip::Create();

    const uart_config_t config = {
        .user_data = inst,
        .tx = pin_init("TX", INPUT_PULLUP),
        .baud_rate = 115200,
        .write_done = onTransmitted,
    };

    inst->port = uart_init(&config);

    for (auto i = 0; i < Chip::NUM_CODES; i++) {
        inst->sendPins[i] = {
            .instance = inst,
            .code = ::codes[i],
            .size = strlen(::codes[i])
        };

        auto pin = pin_init(codePins[i], INPUT_PULLUP);

        const pin_watch_config_t watch_config = {
            .user_data = &inst->sendPins[i],
            .edge = FALLING,
            .pin_change = sendPinStateChanged,
        };

        pin_watch(pin, &watch_config);
    }

    printf("Initialized");
}

Chip* Chip::Create() {
    // need to use malloc instead of using the c++ `new` operator, since we only compile against libc, not std-c++
    return static_cast<Chip*>(malloc(sizeof(Chip)));
}

void Chip::send(const char* code, size_t size) {
    printf("Sending code: %s\n", code);
    uart_write(this->port, (uint8_t*)code, size);
    //
    static uint8_t LF = 10;
    uart_write(this->port, &LF, 1);
}

void Chip::onTransmitted(void* context) {
    printf("Transmitted");
}

void Chip::sendPinStateChanged(void *context, pin_t, uint32_t) {
    auto const info = static_cast<send_pin_t*>(context);
    info->instance->send(info->code, info->size);
}
