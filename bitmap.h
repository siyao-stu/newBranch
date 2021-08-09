#ifndef BIT_MAP_H
#define BIT_MAP_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bitmap;

int bitmap_init(struct bitmap *bitmap, const uint32_t item_count,
        const bool set_flag);
int bitmap_destroy(struct bitmap *bitmap);
int bitmap_set(struct bitmap *bitmap, const uint32_t index);
void bitmap_reset(struct bitmap *bitmap, const uint32_t index);
bool bitmap_test(struct bitmap *bitmap, const uint32_t index);

#ifdef __cplusplus
}
#endif

#endif
