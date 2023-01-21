#include <seven/hw/input.h>

extern struct InputState inputNew(void)
{
    return (struct InputState){ KEYS_ALL, KEYS_ALL };
}

extern struct InputState inputPoll(struct InputState i)
{
    i.last = i.now;
    i.now = REG_KEYINPUT;
    return i;
}

extern u16 inputKeysPressed(u16 keys, struct InputState i)
{
    return (~i.now & i.last) & keys;
}

extern u16 inputKeysReleased(u16 keys, struct InputState i)
{
    return (i.now & ~i.last) & keys;
}

extern u16 inputKeysChanged(u16 keys, struct InputState i)
{
    return (i.now ^ i.last) & keys;
}

extern u16 inputKeysDown(u16 keys, struct InputState i)
{
    return ~i.now & keys;
}

extern u16 inputKeysUp(u16 keys, struct InputState i)
{
    return i.now & keys;
}

extern i32 inputAxisX(struct InputState i)
{
    int keys = (i.now << 26) >> 30;

    return -keys >> 1;
}

extern i32 inputAxisY(struct InputState i)
{
    int keys = ((i.now << 24) >> 30) + 1;

    return keys >> 1;
}

extern i32 inputAxisLR(struct InputState i)
{
    int keys = (i.now << 22) >> 30;

    return -keys >> 1;
}

extern i32 inputAxisAB(struct InputState i)
{
    int keys = (i.now << 30) >> 30;

    return -keys >> 1;
}
