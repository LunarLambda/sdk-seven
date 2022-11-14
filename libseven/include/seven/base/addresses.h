/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_BASE_ADDRESSES_H
#define _LIBSEVEN_BASE_ADDRESSES_H

#define VOLADDR(addr, type)             (*(type volatile *)(addr))
#define VOLARRAY(addr, type, size)      (*(type volatile (*)[size])(addr))

#define MEMADDR(addr, type)             (*(type *)(addr))
#define MEMARRAY(addr, type, size)      (*(type (*)[size])(addr))

#endif /* !_LIBSEVEN_BASE_ADDRESSES_H */
