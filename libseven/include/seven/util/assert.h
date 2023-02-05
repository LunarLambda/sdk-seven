/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_UTIL_ASSERT_H
#define _LIBSEVEN_UTIL_ASSERT_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

#ifdef NDEBUG

#define assertCheck(condition) ((void)0)
#define assertCheckWithFilename(condition, filename) ((void)0)
#define assertCheckWithLocation(condition, function, filename, line) ((void)0)

#else

#ifndef _LIBSEVEN_ASSERT_FUNC
    #ifdef __GNUC__
        #define _LIBSEVEN_ASSERT_FUNC __PRETTY_FUNCTION__
    #elif __STDC_VERSION >= 199901L
        #define _LIBSEVEN_ASSERT_FUNC __func__
    #elif __GNUC__ >= 2
        #define _LIBSEVEN_ASSERT_FUNC __FUNCTION__
    #else
        #define _LIBSEVEN_ASSERT_FUNC ((char*)0)
    #endif
#endif

#ifndef _LIBSEVEN_ASSERT_FILE
    #ifdef __FILE_NAME__
        #define _LIBSEVEN_ASSERT_FILE __FILE_NAME__
    #else
        #define _LIBSEVEN_ASSERT_FILE __FILE__
    #endif
#endif

#define assertCheck(condition) \
    assertCheckWithFilename(condition, _LIBSEVEN_ASSERT_FILE)

#define assertCheckWithFilename(condition, filename) \
    assertCheckWithLocation(condition, _LIBSEVEN_ASSERT_FUNC, filename, __LINE__)

#define assertCheckWithLocation(condition, function, filename, line) \
    do { \
        if (!(condition)) { \
            assertRaise(#condition, function, filename, line); \
        } \
    } while(0)

#endif /* !NDEBUG */

typedef void AssertHandlerFn(const char*, const char*, const char*, uint32_t);

extern AssertHandlerFn* assertSetHandler(AssertHandlerFn *handler);

extern AssertHandlerFn* assertGetHandler(void);

extern void _LIBSEVEN_NORETURN assertRaise(
        const char *message,
        const char *function,
        const char *file,
        uint32_t line);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_UTIL_ASSERT_H */
