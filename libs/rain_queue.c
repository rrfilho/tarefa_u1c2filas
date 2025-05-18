#include "rain_queue.h"
#include "FreeRTOS.h"
#include "queue.h"

static QueueHandle_t _queueData;
static unsigned int _volume;

void rain_queue_init() {
    _queueData = xQueueCreate(20, sizeof(unsigned int));
}

void rain_queue_enqueue(unsigned int volume) {
    xQueueSendToBack(_queueData, &volume, 100);
}

// caso um dos componentes realize uma leitura em uma pilha vazia, retorna o último valor registrado
unsigned int rain_queue_dequeue() {
    unsigned int volume;
    if (xQueueReceive(_queueData, &volume, 100)) _volume = volume;
    return _volume;
}