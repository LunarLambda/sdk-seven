/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define ROR(x, a)                       ((uint32_t)(x) >> (a) | (uint32_t)(x) << (32-(a)))
#define ROL(x, a)                       ((uint32_t)(x) << (a) | (uint32_t)(x) >> (32-(a)))

#define BIT_TRISTATE(val, m, p)         \
    (((val)>>(p)&1)-((val)>>(m)&1))

#define BF_AND(lhs, name, rhs)          ((lhs) &  BITFIELD(name, (rhs)))
#define BF_ORR(lhs, name, rhs)          ((lhs) |  BITFIELD(name, (rhs)))
#define BF_EOR(lhs, name, rhs)          ((lhs) ^  BITFIELD(name, (rhs)))
#define BF_BIC(lhs, name, rhs)          ((lhs) & ~BITFIELD(name, (rhs)))

#define BF_NOT(lhs, name)               ((lhs) ^ BF_MASK(name))
#define BF_NEG(lhs, name)               (BF_SET((lhs), name, -BF_GET((lhs), name)))

#define BF_ADD(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) + (rhs)))
#define BF_SUB(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) - (rhs)))
#define BF_MUL(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) * (rhs)))
#define BF_DIV(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) / (rhs)))
#define BF_MOD(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) % (rhs)))

#define BF_LSL(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) << (rhs)))
#define BF_LSR(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) >> (rhs)))
#define BF_ROL(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) << (rhs) | BF_GET((lhs), name) >> ((BF_##name##_LEN) - (rhs))))
#define BF_ROR(lhs, name, rhs)          (BF_SET((lhs), name, BF_GET((lhs), name) >> (rhs) | BF_GET((lhs), name) << ((BF_##name##_LEN) - (rhs))))

#define BF_MASK(name)                   \
    (BITS((BF_##name##_LEN)) << (BF_##name##_OFF))

#define BF_GET(lhs, name)               \
    ((lhs) >> ((BF_##name##_OFF)) & BITS((BF_##name##_LEN)))

#define BF_SET(lhs, name, rhs)          \
    (BF_ORR((lhs) & ~BF_MASK(name), name, (rhs)))

#define BF_ESET(lhs, name, enum)        \
    (((lhs) & ~BF_MASK(name)) | (name##_##enum))

#define BF_CMP(lhs, name, rhs)          \
    (BF_GET((lhs), name) == (rhs))

#define BF_ECMP(lhs, name, enum)        \
    (((lhs) & BF_MASK(name)) == name##_##enum)

extern uint32_t bitCTZ32(uint32_t value);
extern uint32_t bitCTZ16(uint16_t value);
extern uint32_t bitCTZ8(uint8_t value);

extern uint32_t bitCLZ32(uint32_t value);
extern uint32_t bitCLZ16(uint16_t value);
extern uint32_t bitCLZ8(uint8_t value);

_LIBSEVEN_EXTERN_C_END

