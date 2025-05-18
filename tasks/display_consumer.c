#include "display_consumer.h"
#include <stdbool.h>
#include "osal.h"
#include "display.h"
#include "rain_queue.h"
#include "rivers_queue.h"

static void loop() {
    while (true) {
        unsigned int volume = rain_queue_dequeue();
        unsigned int level = rivers_queue_dequeue();
        display_set_rain_volume(volume);
        display_set_river_level(level);
        os_sleep_ms(100);
    }
}

void display_consumer_task() {
    display_init();
    loop();
}