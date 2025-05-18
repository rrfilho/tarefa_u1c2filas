#include "joystick.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define JOYSTICK_X_AXIS 27
#define JOYSTICK_X_SELECTOR 1
#define JOYSTICK_Y_AXIS 26
#define JOYSTICK_Y_SELECTOR 0

void joystick_init() {
    adc_init();
    adc_gpio_init(JOYSTICK_X_AXIS);
    adc_gpio_init(JOYSTICK_Y_AXIS);
}

unsigned int joystick_read(unsigned int selector) {
    adc_select_input(selector);
    sleep_us(2);
    return adc_read();
}

unsigned int joystick_read_x_axis() {
    return joystick_read(JOYSTICK_X_SELECTOR);
}

unsigned int joystick_read_y_axis() {
    return joystick_read(JOYSTICK_Y_SELECTOR);
}