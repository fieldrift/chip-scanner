#include <stdlib.h>
#include <stdio.h>
#include "wokwi-api.h"

typedef struct {
    uart_dev_t port;
} chip_t;

static void uart_data_written(void* user_data) {

}

void chip_init(void) {
    chip_t* chip = malloc(sizeof(chip_t));

    const uart_config_t config = {
        .tx = pin_init("TX", INPUT_PULLUP),
        .baud_rate = 115200,
        .write_done = uart_data_written      
    };

    printf("Hello from custom chip");
}