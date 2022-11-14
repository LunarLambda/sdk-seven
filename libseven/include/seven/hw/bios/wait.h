/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_BIOS_WAIT_H
#define _LIBSEVEN_HW_BIOS_WAIT_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

extern void biosHalt(void);
extern void biosStop(void);

extern void biosIntrWait(bool wait_next, u16 intr_flags);
extern void biosVBlankIntrWait(void);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_BIOS_WAIT_H */
