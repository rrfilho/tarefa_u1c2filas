#include "rivers_sensor_producer.h"
#include <stdbool.h>
#include "osal.h"
#include "joystick.h"
#include "rivers_queue.h"

#define JOYSTICK_SIXTET_CENTER 512.0f
#define RIVER_MIN_LEVEL 0
#define RIVER_MAX_LEVEL 100

static unsigned int limit_to_range(int value) {
    if (value < RIVER_MIN_LEVEL) return RIVER_MIN_LEVEL;
    if (value > RIVER_MAX_LEVEL) return RIVER_MAX_LEVEL;
    return value;
}

static void loop() {
    int increment = 0;
    int level = 0;
    while (true) {
        increment = joystick_read_y_axis();
        increment = increment/JOYSTICK_SIXTET_CENTER - 4.0f;
        level += increment;
        level = limit_to_range(level);
        rivers_queue_enqueue(level);
        os_sleep_ms(200);
    }
}

void rivers_sensor_producer_task() {
    joystick_init();
    loop();
}