/* buffer.h */
//#include <stdint.h>

#define BUFFER_SIZE 30
struct buffer_item {
    uint16_t cksum;
    uint8_t buffer[BUFFER_SIZE];
};
typedef struct buffer_item buffer_item;

void buffer_init();
int insert_item(buffer_item item);
int remove_item(buffer_item *item);