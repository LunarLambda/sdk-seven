#include <seven/video/prelude.h>
#include <seven/video/bg_bitmap.h>
#include <seven/video/color_constants.h>

int main(void)
{
    REG_DISPCNT = DISPLAY_MODE_BITMAP | DISPLAY_BG2_ENABLE;

    MODE3_FRAME[80][120] = COLOR_RED;
    MODE3_FRAME[80][136] = COLOR_GREEN;
    MODE3_FRAME[96][120] = COLOR_BLUE;

    while (1) {}
}
