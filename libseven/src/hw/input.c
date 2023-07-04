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

extern struct InputState inputInject(uint16_t keys, struct InputState i)
{
    i.last = i.now;
    i.now = keys ^ KEYS_ALL;
    return i;
}

extern struct InputState inputFilterSocd(struct InputState i)
{
    if ((i.now & KEYS_DPAD_X) == 0)
    {
        i.now |= KEYS_DPAD_X;
    }

    if ((i.now & KEYS_DPAD_Y) == 0)
    {
        i.now |= KEYS_DPAD_Y;
    }

    return i;
}

extern struct InputState inputApplyRepeat(struct InputRepeat *r, struct InputState i)
{
    bool c = inputKeysChanged(r->keys, i) & inputKeysDown(r->keys, i);

    // If any of the registered keys change, restart and make no changes
    if (c)
    {
        r->_state = 0;
        r->_counter = r->initial_delay;
        return i;
    }

    if (r->_state == 0)
    {
        r->_state = 1;
    }
    else if (r->_state & 1)
    {
        i.last |= r->keys;

        if (r->_counter-- == 0)
        {
            r->_state = 2;
            r->_counter = r->hold;
        }
    }

    // new state is a delay state
    if (r->_state & 1)
    {
        i.now |= r->keys;
    }

    // state = 0 counter = 0
    // if keys pressed, state = 1, counter = initial_delay
    // if keys released (changed?) state = 0
    // if state = 1 and counter = 0, state = 2, counter = repeat_delay
    // if state = 2 and counter = 0, state = 3, counter = hold
    // if state = 3 and counter = 0, state = 2, counter = repeat_delay

    // 1 x input
    // initial_delay x nothing
    // hold x keys & input
    // repeat_delay x nothing
    // hold x keys & input
    // ...
    // problem is we want to correctly propagate the keys through i.last
    // but that requires tracking state changes between frames... 
    // all the user does is hold buttons, so bethere's only 4 meaningful statessides checking inputKeysChange(r->keys), there isn't any useful info there
    //
    // if delay state, unset keys, if hold state set keys (held | keys)
    //
    // start (keys changed) == 0 -> 0, set counter ?
    // 0 -> 1, remove now        - enter delay
    // 1 -> 1, remove now, last  - delay
    // 1 -> 2, remove last       - exit delay
    // 2 -> 2, no change         - hold
    // 2 -> 3, remove now        - enter delay
    // 3 -> 3, remove now, last  - delay
    // 3 -> 2, remove last       - exit delay
    //
    // bit 0: in_delay
    // bit 1: delay_select

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
    int32_t keys = (i.now << 26) >> 30;

    return -keys >> 1;
}

extern int32_t inputAxisY(struct InputState i)
{
    int32_t keys = ((i.now << 24) >> 30) + 1;

    return keys >> 1;
}

extern int32_t inputAxisLR(struct InputState i)
{
    int32_t keys = (i.now << 22) >> 30;

    return -keys >> 1;
}

extern int32_t inputAxisAB(struct InputState i)
{
    int32_t keys = (i.now << 30) >> 30;

    return -keys >> 1;
}
