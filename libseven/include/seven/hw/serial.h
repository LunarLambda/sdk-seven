/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_SERIAL_H
#define _LIBSEVEN_HW_SERIAL_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#define REG_SIOCNT      VOLADDR(0x04000128, u16)
#define REG_RCNT        VOLADDR(0x04000134, u16)

#define REG_SIODATA8    VOLADDR(0x0400012A, u8)
#define REG_SIODATA32   VOLADDR(0x04000120, u32)

#define REG_MULTISEND   VOLADDR(0x0400012A, u16)
#define REG_MULTIRECV0  VOLADDR(0x04000120, u16)
#define REG_MULTIRECV1  VOLADDR(0x04000122, u16)
#define REG_MULTIRECV2  VOLADDR(0x04000124, u16)
#define REG_MULTIRECV3  VOLADDR(0x04000126, u16)

#define REG_JOYCNT      VOLADDR(0x04000140, u16)
#define REG_JOYRECV     VOLADDR(0x04000150, u32)
#define REG_JOYSEND     VOLADDR(0x04000154, u32)
#define REG_JOYSTAT     VOLADDR(0x04000158, u16)

enum SerialControl
{
    #define BF_SIO_MODE_OFFSET 12
    #define BF_SIO_MODE_LENGTH 2

    #define SIO_MODE(n) BITFIELD(SIO_MODE, (n))

    SIO_MODE_SPI_8BIT     = SIO_MODE(0),
    SIO_MODE_SPI_32BIT    = SIO_MODE(1),
    SIO_MODE_MULTI        = SIO_MODE(2),
    SIO_MODE_UART         = SIO_MODE(3),

    SIO_MODE_RAW          = SIO_MODE(0),
    SIO_MODE_JOYBUS       = SIO_MODE(0),

    SIO_IRQ_ENABLE        = BIT(14),
};

enum RControl
{
    #define BF_R_MODE_OFFSET 14
    #define BF_R_MODE_LENGTH 2

    #define R_MODE(n) BITFIELD(R_MODE, (n))

    R_MODE_SPI_8BIT   = R_MODE(0),
    R_MODE_SPI_32BIT  = R_MODE(0),
    R_MODE_MULTI      = R_MODE(0),
    R_MODE_UART       = R_MODE(0),

    R_MODE_RAW        = R_MODE(2),
    R_MODE_JOYBUS     = R_MODE(3),
};

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_SERIAL_H */
