
#include "prodcon.h"
#include "buffer.h"
#include <pthread.h>
#include <unistd.h> //for sleep()
#include <stdio.h> // for printf()
#include <stdlib.h>// for strtod()


int main(int argc, char *argv[]){
    if(argc != 4){
        printf("Incorrect number of arguments.");
        return -1;
    }
    
    double delay = strtod(argv[1], NULL);
    int num_producers = strtol(argv[2], NULL, 10);
    int num_consumers = strtol(argv[3], NULL, 10);

    //make buffer

    if(create_producer_theads(num_producers) < 0){
        return -1;
    }

    if(create_consumer_threads(num_consumers) <0){
        return -1;
    }

    sleep(delay);

    return 0;

}

int create_producer_theads(int numThreads){
    while(numThreads > 0){
        pthread_t producer_id;
        void *producer_args;

        int producer_result = pthread_create(&producer_id, NULL, producer(), producer_args);

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

        int consumer_result = pthread_create(&consumer_id, NULL, consumer(), consumer_args);

        if(consumer_result != 0){
            printf("Failed to create consumer.");
            return -1;
        }
        numThreads--;
    }
    return 0;
}

void *producer(){
    while (1){
        //
        //produce an item in next_produced
        //
        //wait(empty);
        //wait(mutex);
        //
        //add next_produced to the buffer
        //
        //signal(mutex);
        //signal(full);
    }
    return NULL;
}

void *consumer(){
    while(1){
        //wait(full);
        //wait(mutex);
        //
        //remove an item from buffer to next_consumed
        //
        //signal(mutex);
        //signal(empty);
        //
        //consume the item in next_consumed
        //
    }
    return NULL;
}