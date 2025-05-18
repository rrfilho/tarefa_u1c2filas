#include "rain_sensor_producer.h"
#include <stdbool.h>
#include "osal.h"
#include "joystick.h"
#include "rain_queue.h"

static void loop() {
    while (true) {
        unsigned int volume = joystick_read_x_axis();
        rain_queue_enqueue(volume);
        os_sleep_ms(200);
    }
}

void rain_sensor_producer_task() {
    joystick_init();
    loop();
}