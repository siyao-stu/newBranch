#include "bitmap.h"
#include <errno.h>
#include <stdio.h>

#define INVALID_INDEX 0xFFFFFFFF
#define SLOT_SIZE (8 * sizeof(char))

typedef struct bitmap {
    uint32_t item_count;
    uint32_t slot_count;
    uint32_t set_count;
    char *data;
} BitMap;

static const unsigned char BITMAPMASK[SLOT_SIZE] = {
    0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

int bitmap_init(BitMap *bitmap, const uint32_t item_count, const bool set_flag)
{
    uint32_t slot_count = (item_count + SLOT_SIZE - 1) >> 3;
    char *data = (char *)malloc(sizeof(char) * slot_count);
    if (data == NULL) {
        return ENOMEM;
    }
    memset(data, set_flag ? 0xFF : 0x00, slot_count * sizeof(char));

    bitmap->item_count = item_count;
    bitmap->slot_count = slot_count;
    bitmap->set_count = 0;
    bitmap->data = data;
    return 0;
}

void bitmap_destroy(BitMap *bitmap)
{
    if (bitmap->data != NULL) {
        free(bitmap->data);
        bitmap->data = NULL;
    }

    bitmap->item_count = bitmap->slot_count = bitmap->set_count = 0;
}

int bitmap_set(BitMap *bitmap, const uint32_t index)
{
    if (index >= bitmap->item_count) {
        return E2BIG;
    }

    uint32_t quot = index / SLOT_SIZE;
    uint32_t rem = index % SLOT_SIZE;
    if ((bitmap->data[quot] & BITMAPMASK[rem]) == 0) {
        bitmap->data[quot] |= BITMAPMASK[rem];
        ++bitmap->set_count;
    }

    return 0;
}

void bitmap_reset(BitMap *bitmap, const uint32_t index)
{
    if (index >= bitmap->item_count) {
        return E2BIG;
    }

    uint32_t quot = index / SLOT_SIZE;
    uint32_t rem = index % SLOT_SIZE;
    if ((bitmap->data[quot] & BITMAPMASK[rem]) == 0) {
        bitmap->data[quot] &= ~BITMAPMASK[rem];
        --bitmap->set_count;
    }

    return 0;
}

bool bitmap_test(BitMap *bitmap, const uint32_t index)
{
    if (index >= bitmap->item_count) {
        return false;
    }

    uint32_t quot = index / SLOT_SIZE;
    uint32_t rem = index % SLOT_SIZE;
    return (bitmap->data[quot] & BITMAPMASK[rem]) != 0;
}
