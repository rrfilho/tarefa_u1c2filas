#include <stdio.h>
#include "pico/stdlib.h"

#include "osal.h"
#include "libs/bootsel.h"
#include "libs/rivers_queue.h"
#include "libs/rain_queue.h"

#include "tasks/rivers_sensor_producer.h"
#include "tasks/rain_sensor_producer.h"
#include "tasks/led_matrix_consumer.h"
#include "tasks/display_consumer.h"
#include "tasks/alerts_consumer.h"

void init() {
    stdio_init_all();
    bootsel_init();
    rain_queue_init();
    rivers_queue_init();
    sleep_ms(1000); // tempo para terminal abrir via USB
}

int main() {
    init();
    os_create_task(rain_sensor_producer_task, "Rain Sensor Task");
    os_create_task(rivers_sensor_producer_task, "Rivers Sensor Task");
    os_create_task(led_matrix_consumer_task, "LED Matrix Task");
    os_create_task(display_consumer_task, "Display OLED Task");
    os_create_task(alerts_consumer_task, "Alerts Task");
    os_start();
}