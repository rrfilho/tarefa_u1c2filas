#include "rain_sensor_producer.h"
#include <stdbool.h>
#include "osal.h"
#include "joystick.h"
#include "rain_queue.h"

#define JOYSTICK_SIXTET_CENTER 512.0f
#define RAIN_MIN_LEVEL 0
#define RAIN_MAX_LEVEL 100

static unsigned int limit_to_range(int value) {
    if (value < RAIN_MIN_LEVEL) return RAIN_MIN_LEVEL;
    if (value > RAIN_MAX_LEVEL) return RAIN_MAX_LEVEL;
    return value;
}

static void loop() {
    int increment = 0;
    int volume = 0;
    while (true) {
        increment = joystick_read_x_axis();
        increment = increment/JOYSTICK_SIXTET_CENTER - 4.0f;
        volume += increment;
        volume = limit_to_range(volume);
        rain_queue_enqueue(volume);
        os_sleep_ms(200);
    }
}

void rain_sensor_producer_task() {
    joystick_init();
    loop();
}