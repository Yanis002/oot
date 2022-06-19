.include "macro.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .data

.balign 16

# temporary file name, rename to something more appropriate when decompiled

glabel gMojiFontTLUTs
    .incbin "baserom_non_mq.z64", 0xBA1900, 0x80

glabel gMojiFontTex
    .incbin "baserom_non_mq.z64", 0xBA1980, 0x400
