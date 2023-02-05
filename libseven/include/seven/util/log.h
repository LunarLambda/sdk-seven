/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef _LIBSEVEN_UTIL_LOG_H
#define _LIBSEVEN_UTIL_LOG_H

#include <seven/base.h>

_LIBSEVEN_EXTERN_C

enum LogLevel
{
    // logSetMaxLevel(LOG_OFF);
    LOG_OFF = 0,
    LOG_FATAL,
    LOG_ERROR,
    LOG_WARN,
    LOG_INFO,
    LOG_DEBUG,
    LOG_TRACE,
};

// Supported log interfaces
enum LogInterface
{
    // No interface available
    LOGIF_NONE = 0,
    LOGIF_MGBA,
    LOGIF_NOCASH,
    LOGIF_VBA,
    LOGIF_CUSTOM = 255,
};

typedef void LogCustomOutputFunction(uint8_t, const char *);

// Initializes the first available log interface, or returns LOGIF_NONE
extern uint8_t logInit(void);

// Tries to initialize the given log interface.
extern bool logInitInterface(uint8_t interface);

// Register a custom logging function.
extern void logInitCustom(LogCustomOutputFunction *f);

// Gets the current log interface.
extern uint8_t logGetInterface(void);

// Gets the name of the current log interface.
extern const char* logGetInterfaceName(void);

// Sets the current max log level.
extern void logSetMaxLevel(uint8_t level);

// Gets the current max log level.
extern uint8_t logGetMaxLevel(void);

// Output a message via the currently initialized log interface
extern void logOutput(uint8_t level, const char *message);

_LIBSEVEN_EXTERN_C_END

#endif /* !_LIBSEVEN_UTIL_LOG_H */
