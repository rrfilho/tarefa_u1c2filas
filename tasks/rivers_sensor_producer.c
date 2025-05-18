#include "rivers_sensor_producer.h"
#include <stdbool.h>
#include "osal.h"
#include "joystick.h"
#include "rivers_queue.h"

static void loop() {
    while (true) {
        unsigned int level = joystick_read_y_axis();
        rivers_queue_enqueue(level);
        os_sleep_ms(200);
    }
}

void rivers_sensor_producer_task() {
    joystick_init();
    loop();
}