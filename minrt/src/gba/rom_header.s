@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.section        .header,"ax",%progbits
_header:
    b           _start          @ ROM entry point
    .include    "header_data.s" @ ROM header information
    .zero       6               @ Multiboot area

.global         _header
.weak           _header

@ vim: ft=armv4 et sta sw=4 sts=8
