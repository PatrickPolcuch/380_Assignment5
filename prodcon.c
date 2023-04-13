
#include "prodcon.h"
#include <pthread.h>
#include <unistd.h> //for sleep()
#include <stdio.h> // for printf()
#include <stdlib.h>// for strtod()
#include <semaphore.h>

#define NUM_ITEMS_IN_BUFFER 10
buffer_item buffer[NUM_ITEMS_IN_BUFFER];
int buffer_head;
int buffer_tail;

sem_t empty;
sem_t full;
pthread_mutex_t mutex;

int main(int argc, char *argv[]){
    if(argc != 4){
        printf("Incorrect number of arguments.");
        return -1;
    }
    
    double delay = strtod(argv[1], NULL);
    int num_producers = strtol(argv[2], NULL, 10);
    int num_consumers = strtol(argv[3], NULL, 10);

    //do buffer stuff
    buffer_init();
    

    if(create_producer_theads(num_producers) < 0){
        return -1;
    }

    if(create_consumer_threads(num_consumers) <0){
        return -1;
    }

    sleep(delay);

    return 0;

}

void buffer_init(){
    sem_init(&empty, 0, NUM_ITEMS_IN_BUFFER);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    buffer_head = -1;
    buffer_tail = -1;
}


int insert_item(buffer_item item){
    if((buffer_tail+1)%NUM_ITEMS_IN_BUFFER == buffer_head){
        //queue is full
        printf("queue was full unexpectedly");
        return -1;
    }
    buffer_tail = (buffer_tail+1)%NUM_ITEMS_IN_BUFFER;
    buffer[buffer_tail] = item;
    if(buffer_head == -1){
        buffer_head++;
    }
    return 0;
}

int remove_item(buffer_item *item){
    if(buffer_head < 0 || buffer_tail < 0){
        printf("queue was full enexpectedly");
        return -1;
    }
    *item = buffer[buffer_head];
    buffer_head = (buffer_head+1)%NUM_ITEMS_IN_BUFFER;
    if(buffer_head == (buffer_tail+1)%NUM_ITEMS_IN_BUFFER){//if buffer is empty
        buffer_head = -1;
        buffer_tail = -1;
    }
    return 0;
}

int create_producer_theads(int numThreads){
    while(numThreads > 0){
        pthread_t producer_id;
        void *producer_args;

        int producer_result = pthread_create(&producer_id, NULL, producer, producer_args);

        if(producer_result != 0){
            printf("Failed to create producer.");
            return -1;
        }
        numThreads--;
    }
    return 0;
}

int create_consumer_threads(int numThreads){
    while(numThreads > 0){
        pthread_t consumer_id;
        void *consumer_args;

        int consumer_result = pthread_create(&consumer_id, NULL, consumer, consumer_args);

        if(consumer_result != 0){
            printf("Failed to create consumer.");
            return -1;
        }
        numThreads--;
    }
    return 0;
}

void produce_item(buffer_item *item){
    item->value = 90;
    for(int i = 0; i < 31; i++) {
      item->data[i] = 1;
    }

}

int consume_item(buffer_item item){
    return 1;
}

void *producer(){
    buffer_item next_produced;
    while (1){
        //
        //produce an item in next_produced
        produce_item(&next_produced);
        //
        sem_wait(&empty);
         pthread_mutex_lock(&mutex);
        //
        //add next_produced to the buffer
        if(insert_item(next_produced) < 0){
            break;//something went wrong and we want to get out
        }
        //
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(){
    buffer_item next_consumed;
    while(1){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        //remove an item from buffer to next_consumed
        remove_item(&next_consumed);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        
        //consume the item in next_consumed
        if(consume_item(next_consumed) == 1){
            printf("Correct!\n");
        } else {
            printf("Incorrect :(\n");
        }
        
    }
    return NULL;
}