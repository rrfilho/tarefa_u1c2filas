#include "alerts_consumer.h"
#include <stdbool.h>
#include "osal.h"
#include "display.h"
#include "leds.h"
#include "buzzer.h"
#include "rain_queue.h"
#include "rivers_queue.h"

#define RIVERS_LEVEL_LIMIT 70
#define RAIN_VOLUME_LIMIT 80

static void rivers_alert() {
    display_set_alert("ALERTA ALAGAMENTO");
    leds_set_red(true);
    buzzer_set(true);
    os_sleep_ms(100);
    buzzer_set(false);
}

static void rain_alert() {
    display_set_alert("ALERTA CHUVAS");
    leds_set_red(true);
    buzzer_set(true);
    os_sleep_ms(50);
    buzzer_set(false);
    os_sleep_ms(50);
    buzzer_set(true);
    os_sleep_ms(50);
    buzzer_set(false);
}

static void loop() {
    while (true) {
        os_sleep_ms(100);
        unsigned int volume = rain_queue_dequeue();
        unsigned int level = rivers_queue_dequeue();
        if (level >= RIVERS_LEVEL_LIMIT) {
            rivers_alert();
            continue;
        }
        if (volume >= RAIN_VOLUME_LIMIT) {
            rain_alert();
            continue;
        }
        display_set_alert("Sem alertas");
        leds_set_green(true);
    }
}

void alerts_consumer_task() {
    buzzer_init();
    leds_init();
    loop();
}