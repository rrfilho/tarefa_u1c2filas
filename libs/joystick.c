#include "joystick.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define JOYSTICK_X_AXIS 27
#define JOYSTICK_X_SELECTOR 1
#define JOYSTICK_Y_AXIS 26
#define JOYSTICK_Y_SELECTOR 0
#define JOYSTICK_SIXTET_CENTER 512.0f
#define JOYSTICK_SHIFT 4.0f
#define MIN_LEVEL 0
#define MAX_LEVEL 100

static int _x_accumulator = 0;
static int _y_accumulator = 0;

void joystick_init() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_AXIS);
    adc_gpio_init(JOYSTICK_Y_AXIS);
}

static unsigned int limit_to_range(int value) {
    if (value < MIN_LEVEL) return MIN_LEVEL;
    if (value > MAX_LEVEL) return MAX_LEVEL;
    return value;
}

static unsigned int joystick_read(unsigned int selector) {
    adc_select_input(selector);
    sleep_us(2);
    return adc_read();
}

unsigned int joystick_read_x_axis() {
    int increment = joystick_read(JOYSTICK_X_SELECTOR);
    increment = increment/JOYSTICK_SIXTET_CENTER - JOYSTICK_SHIFT;
    _x_accumulator += increment;
    _x_accumulator = limit_to_range(_x_accumulator);
    return _x_accumulator;
}

unsigned int joystick_read_y_axis() {
    int increment = joystick_read(JOYSTICK_Y_SELECTOR);
    increment = increment/JOYSTICK_SIXTET_CENTER - JOYSTICK_SHIFT;
    _y_accumulator += increment;
    _y_accumulator = limit_to_range(_y_accumulator);
    return _y_accumulator;
}