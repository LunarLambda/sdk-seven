@
@ This Source Code Form is subject to the terms of the Mozilla Public
@ License, v. 2.0. If a copy of the MPL was not distributed with this
@ file, You can obtain one at https://mozilla.org/MPL/2.0/.
@

.syntax         unified
.cpu            arm7tdmi

.section        .header,"ax",%progbits
_header:
    b           _start_rom      @ ROM entry point
    .include    "header_data.s" @ ROM header information
    b           _start          @ Multiboot entry point
    .zero       32              @ Multiboot reserved

.global         _header
.weak           _header

@ vim: ft=armv4 et sta sw=4 sts=8
