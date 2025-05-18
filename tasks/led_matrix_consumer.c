#include "led_matrix_consumer.h"
#include <stdbool.h>
#include "osal.h"
#include "led_matrix.h"
#include "rivers_queue.h"

static void loop() {
    while (true) {
        unsigned int level = rivers_queue_dequeue();
        led_matrix_draw(level);
        os_sleep_ms(100);
    }
}

void led_matrix_consumer_task() {
    led_matrix_init();
    loop();
}