/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <seven/base.h>
#include <seven/video/memory.h>

_LIBSEVEN_EXTERN_C

size_t oamWriteObjects(size_t oam_index, struct Object *objs, size_t n_objs);
size_t oamWriteObjectsUnchecked(size_t oam_index, struct Object *objs, size_t n_objs);

size_t oamWriteMatrices(size_t oam_index, struct Matrix *mats, size_t n_mats);
size_t oamWriteMatricesUnchecked(size_t oam_index, struct Matrix *mats, size_t n_mats);

_LIBSEVEN_EXTERN_C_END
