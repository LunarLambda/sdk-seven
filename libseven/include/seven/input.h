/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

// Keypad input register. Reports held keys as active-low bits.
//
#define REG_KEYINPUT VOLADDR(0x04000130, const uint16_t)

// Keypad control register. Allows configuring the keypad IRQ.
//
#define REG_KEYCNT   VOLADDR(0x04000132, uint16_t)

// Key bits as used by KEYINPUT and KEYCNT.
enum Key
{
    KEY_A               = BIT(0),
    KEY_B               = BIT(1),
    KEY_SELECT          = BIT(2),
    KEY_START           = BIT(3),
    KEY_RIGHT           = BIT(4),
    KEY_LEFT            = BIT(5),
    KEY_UP              = BIT(6),
    KEY_DOWN            = BIT(7),
    KEY_R               = BIT(8),
    KEY_L               = BIT(9),
};

// Groupings of key bits.
enum KeyGroup
{
    KEYS_DPAD_X         = KEY_LEFT      | KEY_RIGHT,
    KEYS_DPAD_Y         = KEY_UP        | KEY_DOWN,
    KEYS_DPAD           = KEYS_DPAD_X   | KEYS_DPAD_Y,
    KEYS_AB             = KEY_A         | KEY_B,
    KEYS_LR             = KEY_L         | KEY_R,
    KEYS_STARTSELECT    = KEY_START     | KEY_SELECT,
    KEYS_BUTTONS        = KEYS_AB       | KEYS_LR       | KEYS_STARTSELECT,
    KEYS_ALL            = KEYS_DPAD     | KEYS_BUTTONS,
};

// Bit indices of keys bits.
enum KeyIndex
{
    KEY_INDEX_A,
    KEY_INDEX_B,
    KEY_INDEX_SELECT,
    KEY_INDEX_START,
    KEY_INDEX_RIGHT,
    KEY_INDEX_LEFT,
    KEY_INDEX_UP,
    KEY_INDEX_DOWN,
    KEY_INDEX_R,
    KEY_INDEX_L,
    KEY_INDEX_MAX,
};

enum KeyIRQ
{
    KEY_IRQ_ENABLE    = BIT(14),
    KEY_IRQ_PRESS_ALL = BIT(15),
    KEY_IRQ_PRESS_ANY = !KEY_IRQ_PRESS_ALL,
};

_LIBSEVEN_ALIGNED
struct InputState
{
    uint16_t now;
    uint16_t last;
};

_LIBSEVEN_ALIGNED
struct InputRepeat
{
    uint16_t keys;
    uint16_t initial_delay;
    uint16_t repeat_delay;
    uint16_t hold;
    uint16_t _state;
    uint16_t _counter;
};

// Returns a fresh InputState.
extern struct InputState inputNew(void);

// Updates the given keypad state. Should be called once per frame.
extern struct InputState inputPoll(struct InputState i);

// Inject the given keys into the given keypad state. Equivalent to calling inputPoll, if REG_KEYINPUT returned keys.
extern struct InputState inputInject(uint16_t keys, struct InputState i);

// Performs SOCD (Simultaneous Opposed Cardinal Direction) filtering on the given input state.
// Uses a neutral resolution, meaning holding opposite direction results in neither direction being held.
extern struct InputState inputFilterSocd(struct InputState i);

// [WIP]
//
// Applies the given repeat state to the given input state. Should be called once per frame.
//
// This input layer should be applied last, and the resulting state stored separately from the input state.
// This is because to track the repeat state correctly, the function needs the "true" input state.
// extern struct InputState inputApplyRepeat(struct InputRepeat *r, struct InputState i);

// Returns the keys that were pressed this frame. ("Rising egde")
extern uint16_t inputKeysPressed(uint16_t keys, struct InputState i);

// Returns the keys that were released this frame. ("Falling edge")
extern uint16_t inputKeysReleased(uint16_t keys, struct InputState i);

// Returns the keys whose state changed this frame. ("Any edge")
extern uint16_t inputKeysChanged(uint16_t keys, struct InputState i);

// Returns the keys that are being held this frame.
extern uint16_t inputKeysDown(uint16_t keys, struct InputState i);

// Returns the keys that are not being held this frame.
extern uint16_t inputKeysUp(uint16_t keys, struct InputState i);

// Gets the state of the Dpad X-axis.
// -1: Left
//  0: None
//  1: Right
extern int32_t inputAxisX(struct InputState i);

// Gets the state of the Dpad Y-axis.
// -1: Up
//  0: None
//  1: Down
extern int32_t inputAxisY(struct InputState i);

// Gets the state of the shoulder button axis.
// -1: L
//  0: None/Both
//  1: R
extern int32_t inputAxisLR(struct InputState i);

// Gets the state of the face button axis.
// -1: B
//  0: None/Both
//  1: A
extern int32_t inputAxisAB(struct InputState i);

_LIBSEVEN_EXTERN_C_END
