#include <seven/video/prelude.h>
#include <seven/video/bg_bitmap.h>
#include <seven/video/color_constants.h>

__attribute__((section(".dacs"), target("arm")))
static void dacs(void)
{
    REG_DISPCNT = DISPLAY_MODE_BITMAP | DISPLAY_BG2_ENABLE;

    MODE3_FRAME[80][120] = COLOR_RED;
    MODE3_FRAME[80][136] = COLOR_GREEN;
    MODE3_FRAME[96][120] = COLOR_BLUE;
}

int main(void)
{
    __asm__ (".arch armv5t\nblx r0\n.arch armv4t");

    while (1) {}
}
