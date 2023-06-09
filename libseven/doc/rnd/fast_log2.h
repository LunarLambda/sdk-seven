#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static int fast_log2_16bit(uint16_t v)
{
    static const int table[] = {
    	0, 1, 2, 4, 9, 3, 6, 13, 10, 5, 11, 7, 15, 14, 12, 8
    }

    if (!irq || (irq & (irq - 1)))
    {
	return -1;
    }

    uint32_t idx = (uint32_t)(0x09AF0000 * irq) >> 28;

    return table[idx];
}

