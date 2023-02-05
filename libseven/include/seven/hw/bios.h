/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

enum SoftwareInterruptNumber
{
    SWI_SOFTRESET                       =  0,
    SWI_REGISTERRAMRESET                =  1,

    SWI_HALT                            =  2,
    SWI_STOP                            =  3,
    SWI_INTRWAIT                        =  4,
    SWI_VBLANKINTRWAIT                  =  5,

    SWI_DIV                             =  6,
    SWI_SQRT                            =  8,
    SWI_ARCTAN                          =  9,
    SWI_ARCTAN2                         = 10,

    SWI_CPUSET                          = 11,
    SWI_CPUFASTSET                      = 12,

    SWI_BIOSCHECKSUM                    = 13,

    SWI_BGAFFINESET                     = 14,
    SWI_OBJAFFINESET                    = 15,

    SWI_BITUNPACK                       = 16,
    SWI_LZ77UNCOMPWRAM                  = 17,
    SWI_LZ77UNCOMPVRAM                  = 18,
    SWI_HUFFUNCOMP                      = 19,
    SWI_RLUNCOMPWRAM                    = 20,
    SWI_RLUNCOMPVRAM                    = 21,
    SWI_DIFF8BITUNFILTERWRAM            = 22,
    SWI_DIFF8BITUNFILTERVRAM            = 23,
    SWI_DIFF16BITUNFILTER               = 24,

    SWI_SOUNDBIAS                       = 25,
    SWI_SOUNDDRIVERINIT                 = 26,
    SWI_SOUNDDRIVERMODE                 = 27,
    SWI_SOUNDDRIVERMAIN                 = 28,
    SWI_SOUNDDRIVERVSYNC                = 29,
    SWI_SOUNDCHANNELCLEAR               = 30,
    SWI_MIDIKEY2FREQ                    = 31,
    SWI_MUSICPLAYEROPEN                 = 32,
    SWI_MUSICPLAYERSTART                = 33,
    SWI_MUSICPLAYERSTOP                 = 34,
    SWI_MUSICPLAYERCONTINUE             = 35,
    SWI_MUSICPLAYERFADEOUT              = 36,

    SWI_MULTIBOOT                       = 37,

    SWI_HARDRESET                       = 38,

    SWI_SOUNDDRIVERVSYNCOFF             = 40,
    SWI_SOUNDDRIVERVSYNCON              = 41,
};
