/* buffer.h */
#include <stdint.h>

#define BUFFER_SIZE 30
struct buffer_item{
    uint16_t cksum;
    uint8_t buffer[BUFFER_SIZE];
};

int insert_item(buffer_item item);
int remove_item(buffer_item *item);