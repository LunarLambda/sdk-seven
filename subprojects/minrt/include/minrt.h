#ifndef _GBA_MINRT_H
#define _GBA_MINRT_H

#include <stddef.h>

// Returns the amount of IWRAM allocated to static variables.
size_t minrt_used_static_iwram(void);

// Returns the amount of EWRAM allocated to static variables.
size_t minrt_used_static_ewram(void);

// Returns the amount of stack space used.
//
// NOTE: This function currently assumes that the
// initial stack pointer is always at 0x03007F00.
size_t minrt_used_stack(void);

// Returns the amount of stack space left.
//
// NOTE: This function currentlz assumes that the
// initial stack pointer is always at 0x03007F00.
//
// If the function returns a negative value, the stack has overflown
// into the area allocated for static variables.
ptrdiff_t minrt_stack_left(void);

#endif /* _GBA_MINRT_H */
