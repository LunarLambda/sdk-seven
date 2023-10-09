#include <seven/video.h>
#include <seven/video/memory.h>

#define BF_MASK(name)                   \
    (BITS((BF_##name##_LEN)) << (BF_##name##_OFF))

#define BF_GET(lhs, name)               \
    ((lhs) >> ((BF_##name##_OFF)) & BITS((BF_##name##_LEN)))

int32_t vramAddrToBgTileIndex(const void *addr, uint16_t bgcnt)
{
    uintptr_t p = (uintptr_t)addr;

    uint32_t base = BF_GET(bgcnt, BG_GFX_BASE) << 14;
    uint32_t size = bgcnt & BG_TILE_8BPP ? 6 : 5;

    // de-mirror address
    p &= ~0xFE0000;
    p -= 0x06000000 + base;

    return p < UNIT_KIB(16) ? (int32_t)(p >> size) : -1;
}

int32_t vramAddrToObjTileIndex(const void *addr)
{
    uintptr_t p = (uintptr_t)addr;

    // de-mirror address
    // this "re-mirrors" the lower half of BG VRAM, but that's out of range.
    p &= ~0xFE8000;
    p -= 0x06010000;

    return p < UNIT_KIB(32) ? (int32_t)(p >> 5) : -1;
}

struct MapIndex vramAddrToMapIndex(const void *addr, uint16_t bgcnt, bool is_affine)
{
    static const uint16_t LIMITS[] =
    {
        // Regular
        UNIT_KIB(2),
        UNIT_KIB(4),
        UNIT_KIB(4),
        UNIT_KIB(8),
        // Affine
        256,
        UNIT_KIB(1),
        UNIT_KIB(4),
        UNIT_KIB(16),
    };

    uintptr_t p = (uintptr_t)addr;

    // background size (index)
    uint32_t size = BF_GET(bgcnt, BG_SIZE);
    // background width in tiles
    uint32_t width = is_affine ? 4 + size : 5;
    // lower address limit
    uint32_t base = BF_GET(bgcnt, BG_MAP_BASE) << 11;
    // upper address limit
    uint32_t limit = LIMITS[size + (is_affine ? 4 : 0)];

    // de-mirror address
    p &= ~0xFE0000;
    p -= 0x06000000 + base;

    if (p >= limit)
    {
        return (struct MapIndex){0};
    }

    p -= base;

    uint8_t block = is_affine ? base >> 11 : p >> 11;

    // Shift down for regular maps
    p >>= is_affine ? 0 : 1;

    uint8_t x = p & BITS(width);
    uint8_t y = p >> width;

    return (struct MapIndex){ true, block, x, y };
}
