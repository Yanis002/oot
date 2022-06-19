.include "macro.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .rodata

.balign 16

glabel gSoundFontTable
    .incbin "baserom_non_mq.z64", 0xBCC290, 0x270

glabel gSequenceFontTable
    .incbin "baserom_non_mq.z64", 0xBCC500, 0x1C0

glabel gSequenceTable
    .incbin "baserom_non_mq.z64", 0xBCC6C0, 0x6F0

glabel gSampleBankTable
    .incbin "baserom_non_mq.z64", 0xBCCDB0, 0x80
