#include <seven/input.h>

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

extern uint16_t inputKeysPressed(uint16_t keys, struct InputState i)
{
    return (~i.now & i.last) & keys;
}

extern uint16_t inputKeysReleased(uint16_t keys, struct InputState i)
{
    return (i.now & ~i.last) & keys;
}

extern uint16_t inputKeysChanged(uint16_t keys, struct InputState i)
{
    return (i.now ^ i.last) & keys;
}

extern uint16_t inputKeysDown(uint16_t keys, struct InputState i)
{
    return ~i.now & keys;
}

extern uint16_t inputKeysUp(uint16_t keys, struct InputState i)
{
    return i.now & keys;
}

extern int32_t inputAxisX(struct InputState i)
{
    int keys = (i.now << 26) >> 30;

    return -keys >> 1;
}

extern int32_t inputAxisY(struct InputState i)
{
    int keys = ((i.now << 24) >> 30) + 1;

    return keys >> 1;
}

extern int32_t inputAxisLR(struct InputState i)
{
    int keys = (i.now << 22) >> 30;

    return -keys >> 1;
}

extern int32_t inputAxisAB(struct InputState i)
{
    int keys = (i.now << 30) >> 30;

    return -keys >> 1;
}
