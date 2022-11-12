/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <stdint.h>

#define REG_DISPCNT (*(uint16_t volatile *)(0x04000000))
#define MODE3_FRAME (*(uint16_t (*)[160][240])(0x06000000))

int main(void)
{
    REG_DISPCNT = 0x0403; // Mode 3, BG2 on

    MODE3_FRAME[80][120] = 0x001F; // Red
    MODE3_FRAME[80][136] = 0x03E0; // Green
    MODE3_FRAME[96][120] = 0x7C00; // Blue
}
