#include "rivers_queue.h"
#include "FreeRTOS.h"
#include "queue.h"

static QueueHandle_t _queueData;
static unsigned int _level;

void rivers_queue_init() {
    _queueData = xQueueCreate(10, sizeof(unsigned int));
}

void rivers_queue_enqueue(unsigned int level) {
    xQueueSendToBack(_queueData, &level, 100);
}

// caso um dos componentes realize uma leitura em uma pilha vazia, retorna o último valor registrado
unsigned int rivers_queue_dequeue() {
    unsigned int level;
    if (xQueueReceive(_queueData, &level, 100)) _level = level;
    return _level;
}