/* buffer.h */
#include <stdint.h>

#define BUFFER_SIZE 30
typedef struct {
    uint16_t cksum;
    uint8_t buffer[BUFFER_SIZE];
} buffer_item;