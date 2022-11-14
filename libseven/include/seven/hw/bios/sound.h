/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_HW_BIOS_SOUND_H
#define _LIBSEVEN_HW_BIOS_SOUND_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

extern void biosSoundDriverMain(void);
extern void biosSoundDriverVSync(void);
extern void biosSoundChannelClear(void);
extern void biosSoundDriverVSyncOff(void);
extern void biosSoundDriverVSyncOn(void);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_HW_BIOS_SOUND_H */
