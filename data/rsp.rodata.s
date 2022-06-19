.include "macro.inc"

# assembler directives
.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches
.set gp=64     # allow use of 64-bit general purpose registers

.section .rodata

.balign 16

glabel aspMainDataStart
    .incbin "baserom_non_mq.z64", 0xBCCE30, 0x2E0
glabel aspMainDataEnd

glabel gspF3DZEX2_NoN_PosLight_fifoTextStart
    .incbin "baserom_non_mq.z64", 0xBCD110, 0x1630
glabel gspF3DZEX2_NoN_PosLight_fifoTextEnd

glabel gspF3DZEX2_NoN_PosLight_fifoDataStart
    .incbin "baserom_non_mq.z64", 0xBCE740, 0x420
glabel gspF3DZEX2_NoN_PosLight_fifoDataEnd

glabel gspS2DEX2d_fifoDataStart
    .incbin "baserom_non_mq.z64", 0xBCEB60, 0x390
glabel gspS2DEX2d_fifoDataEnd

glabel njpgdspMainDataStart
    .incbin "baserom_non_mq.z64", 0xBCEEF0, 0x60
glabel njpgdspMainDataEnd
