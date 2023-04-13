#include "buffer.h"//put this here so the function prototypes would make sence

int create_producer_theads(int numThreads);
int create_consumer_threads(int numThreads);
void *producer();
void *consumer();
void produce_item(buffer_item *item);
int consume_item(buffer_item item)