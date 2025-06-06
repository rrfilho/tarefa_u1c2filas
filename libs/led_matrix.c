#include "led_matrix.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "pio_matrix.h"
#include <stdio.h>

#define PIXELS 25
#define LED_MATRIX_PIN 7
#define ON 180430
#define OFF 0
#define BRIGHTNESS_FACTOR 0.01

static const PIO PIO_ID = pio0;
static unsigned int sm;

void led_matrix_init() {
    set_sys_clock_khz(128000, false);
    unsigned int offset = pio_add_program(PIO_ID, &pio_matrix_program);
    sm = pio_claim_unused_sm(PIO_ID, true);
    pio_matrix_program_init(PIO_ID, sm, offset, LED_MATRIX_PIN);
}

void led_matrix_draw(unsigned int level) {
    unsigned int mapped_level = (level+15)/20;
    for (unsigned int i = 0; i < PIXELS; i++) {
        unsigned int led_value = i/5 < mapped_level ? ON : OFF;
        pio_sm_put_blocking(PIO_ID, sm, led_value * BRIGHTNESS_FACTOR);
    }
}