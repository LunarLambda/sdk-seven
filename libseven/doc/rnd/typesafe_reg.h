#pragma once
// https://godbolt.org/z/MWfTx9x9v

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VOLADDR(type, addr) (*(type volatile (*)(addr)))
#define STRUCT(reg)         VOLADDR(reg##_STRUCT_T, &reg)

#define REG_DISPCNT VOLADDR(uint16_t, 0x04000000)
#define REG_DISPCNT_STRUCT_T struct Dispcnt

struct Dispcnt
{
    uint16_t mode:3;
    uint16_t cgb_mode:1;
    uint16_t frame_select:1;
    uint16_t hblank_obj_processing_disable:1;
    uint16_t obj_mapping:1;
    uint16_t force_blank:1;
    uint16_t bg0_enable:1;
    uint16_t bg1_enable:1;
    uint16_t bg2_enable:1;
    uint16_t bg3_enable:1;
    uint16_t obj_enable:1;
    uint16_t win0_enable:1;
    uint16_t win1_enable:1;
    uint16_t obj_win_enable:1;
};

static void init_raw(void)
{
    REG_DISPCNT = 0x0403;
}

static void init_struct(void)
{
    STRUCT(REG_DISPCNT) = (struct Dispcnt) {
        .mode = 3,
        .bg2_enable = true,
    };
}
