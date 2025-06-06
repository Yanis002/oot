#include "array_count.h"
#include "printf.h"
#include "translation.h"
#include "collision_check.h"

static DamageTable sDamageTablePresets[] = {
    { {
        // 0
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0xE),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0xF),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0xF),
        /* Master sword  */ DMG_ENTRY(2, 0xF),
        /* Giant's Knife */ DMG_ENTRY(2, 0xF),
        /* Fire arrow    */ DMG_ENTRY(2, 0x2),
        /* Ice arrow     */ DMG_ENTRY(1, 0x0),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(2, 0x2),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(2, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 1 Used by En_Karebaba
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0xE),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0xF),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0xF),
        /* Master sword  */ DMG_ENTRY(2, 0xF),
        /* Giant's Knife */ DMG_ENTRY(2, 0xF),
        /* Fire arrow    */ DMG_ENTRY(2, 0x2),
        /* Ice arrow     */ DMG_ENTRY(1, 0x0),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(2, 0x2),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(2, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 2 Used by En_St, En_Ssh
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(2, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x1),
        /* Normal arrow  */ DMG_ENTRY(2, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(2, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(4, 0x0),
        /* Fire arrow    */ DMG_ENTRY(4, 0x0),
        /* Ice arrow     */ DMG_ENTRY(4, 0x0),
        /* Light arrow   */ DMG_ENTRY(4, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(3, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(4, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
        /* Giant jump    */ DMG_ENTRY(4, 0x0),
        /* Master jump   */ DMG_ENTRY(8, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 3
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(1, 0x0),
        /* Hookshot      */ DMG_ENTRY(1, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(1, 0x0),
        /* Giant's Knife */ DMG_ENTRY(1, 0x0),
        /* Fire arrow    */ DMG_ENTRY(1, 0x0),
        /* Ice arrow     */ DMG_ENTRY(1, 0x0),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(1, 0x0),
        /* Fire magic    */ DMG_ENTRY(1, 0x0),
        /* Ice magic     */ DMG_ENTRY(1, 0x0),
        /* Light magic   */ DMG_ENTRY(1, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(2, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(2, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
        /* Giant jump    */ DMG_ENTRY(2, 0x0),
        /* Master jump   */ DMG_ENTRY(2, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 4 Used by En_Dodojr
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(2, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(2, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(2, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(4, 0x0),
        /* Fire arrow    */ DMG_ENTRY(4, 0x0),
        /* Ice arrow     */ DMG_ENTRY(4, 0x0),
        /* Light arrow   */ DMG_ENTRY(4, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(4, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
        /* Giant jump    */ DMG_ENTRY(4, 0x0),
        /* Master jump   */ DMG_ENTRY(8, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 5
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x1),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(1, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(1, 0x0),
        /* Giant's Knife */ DMG_ENTRY(1, 0x0),
        /* Fire arrow    */ DMG_ENTRY(1, 0x0),
        /* Ice arrow     */ DMG_ENTRY(1, 0x3),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(1, 0x3),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(1, 0x0),
        /* Master spin   */ DMG_ENTRY(1, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 6
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(3, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(6, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(4, 0x0),
        /* Hammer swing  */ DMG_ENTRY(4, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(2, 0x0),
        /* Master sword  */ DMG_ENTRY(6, 0x0),
        /* Giant's Knife */ DMG_ENTRY(0, 0x0),
        /* Fire arrow    */ DMG_ENTRY(6, 0x0),
        /* Ice arrow     */ DMG_ENTRY(0, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 7
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(3, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(6, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(4, 0x0),
        /* Hammer swing  */ DMG_ENTRY(4, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(2, 0x0),
        /* Master sword  */ DMG_ENTRY(6, 0x0),
        /* Giant's Knife */ DMG_ENTRY(0, 0x0),
        /* Fire arrow    */ DMG_ENTRY(6, 0x0),
        /* Ice arrow     */ DMG_ENTRY(6, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(4, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 8
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(3, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(4, 0x0),
        /* Hammer swing  */ DMG_ENTRY(4, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(2, 0x0),
        /* Master sword  */ DMG_ENTRY(0, 0x0),
        /* Giant's Knife */ DMG_ENTRY(0, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(0, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(4, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 9 Used by En_Bubble
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(2, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(0, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(2, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(4, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(4, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(4, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
        /* Giant jump    */ DMG_ENTRY(4, 0x0),
        /* Master jump   */ DMG_ENTRY(8, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 10
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0xE),
        /* Boomerang     */ DMG_ENTRY(0, 0x1),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0xF),
        /* Master sword  */ DMG_ENTRY(2, 0xF),
        /* Giant's Knife */ DMG_ENTRY(2, 0xF),
        /* Fire arrow    */ DMG_ENTRY(2, 0x2),
        /* Ice arrow     */ DMG_ENTRY(2, 0x3),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(2, 0x2),
        /* Ice magic     */ DMG_ENTRY(2, 0x3),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(2, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 11 Used by En_Horse
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(0, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(0, 0x0),
        /* Hammer swing  */ DMG_ENTRY(0, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(9, 0x0),
        /* Master sword  */ DMG_ENTRY(0, 0x0),
        /* Giant's Knife */ DMG_ENTRY(0, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(0, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 12
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(4, 0x0),
        /* Hammer swing  */ DMG_ENTRY(4, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(2, 0x0),
        /* Master sword  */ DMG_ENTRY(4, 0x0),
        /* Giant's Knife */ DMG_ENTRY(4, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(0, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(4, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 13
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x1),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(2, 0x0),
        /* Fire arrow    */ DMG_ENTRY(2, 0x2),
        /* Ice arrow     */ DMG_ENTRY(1, 0x0),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(2, 0x2),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(1, 0x0),
        /* Master spin   */ DMG_ENTRY(1, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 14 Used by En_Sw
        /* Deku nut      */ DMG_ENTRY(1, 0x0),
        /* Deku stick    */ DMG_ENTRY(2, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(2, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(2, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(4, 0x0),
        /* Fire arrow    */ DMG_ENTRY(4, 0x0),
        /* Ice arrow     */ DMG_ENTRY(4, 0x0),
        /* Light arrow   */ DMG_ENTRY(4, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(4, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
        /* Giant jump    */ DMG_ENTRY(4, 0x0),
        /* Master jump   */ DMG_ENTRY(8, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 15 Used by En_Fd
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(0, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(0, 0x0),
        /* Hammer swing  */ DMG_ENTRY(0, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(0, 0x0),
        /* Master sword  */ DMG_ENTRY(0, 0x0),
        /* Giant's Knife */ DMG_ENTRY(0, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(0, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 16 Used by En_Fw
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(2, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(2, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(2, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(4, 0x0),
        /* Fire arrow    */ DMG_ENTRY(4, 0x0),
        /* Ice arrow     */ DMG_ENTRY(4, 0x0),
        /* Light arrow   */ DMG_ENTRY(4, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(4, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(4, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(2, 0x0),
        /* Giant jump    */ DMG_ENTRY(4, 0x0),
        /* Master jump   */ DMG_ENTRY(8, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 17
        /* Deku nut      */ DMG_ENTRY(1, 0x0),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(1, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(1, 0x0),
        /* Hookshot      */ DMG_ENTRY(1, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(1, 0x0),
        /* Giant's Knife */ DMG_ENTRY(1, 0x0),
        /* Fire arrow    */ DMG_ENTRY(1, 0x0),
        /* Ice arrow     */ DMG_ENTRY(1, 0x0),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(1, 0x0),
        /* Fire magic    */ DMG_ENTRY(1, 0x0),
        /* Ice magic     */ DMG_ENTRY(1, 0x0),
        /* Light magic   */ DMG_ENTRY(1, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 18
        /* Deku nut      */ DMG_ENTRY(1, 0x0),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(1, 0x0),
        /* Boomerang     */ DMG_ENTRY(1, 0x0),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(1, 0x0),
        /* Hookshot      */ DMG_ENTRY(1, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(1, 0x0),
        /* Giant's Knife */ DMG_ENTRY(1, 0x0),
        /* Fire arrow    */ DMG_ENTRY(1, 0x0),
        /* Ice arrow     */ DMG_ENTRY(1, 0x0),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(1, 0x0),
        /* Fire magic    */ DMG_ENTRY(1, 0x0),
        /* Ice magic     */ DMG_ENTRY(1, 0x0),
        /* Light magic   */ DMG_ENTRY(1, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 19
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x1),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0xF),
        /* Master sword  */ DMG_ENTRY(2, 0xF),
        /* Giant's Knife */ DMG_ENTRY(2, 0xF),
        /* Fire arrow    */ DMG_ENTRY(2, 0x2),
        /* Ice arrow     */ DMG_ENTRY(2, 0x3),
        /* Light arrow   */ DMG_ENTRY(1, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(2, 0x2),
        /* Ice magic     */ DMG_ENTRY(2, 0x3),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(2, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 20
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(1, 0x0),
        /* Explosive     */ DMG_ENTRY(2, 0xF),
        /* Boomerang     */ DMG_ENTRY(0, 0xE),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(2, 0xD),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(2, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(2, 0x3),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(2, 0x3),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(2, 0x0),
        /* Master spin   */ DMG_ENTRY(2, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 21
        /* Deku nut      */ DMG_ENTRY(0, 0x1),
        /* Deku stick    */ DMG_ENTRY(1, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0xF),
        /* Boomerang     */ DMG_ENTRY(0, 0x1),
        /* Normal arrow  */ DMG_ENTRY(1, 0x0),
        /* Hammer swing  */ DMG_ENTRY(0, 0xF),
        /* Hookshot      */ DMG_ENTRY(0, 0x1),
        /* Kokiri sword  */ DMG_ENTRY(1, 0x0),
        /* Master sword  */ DMG_ENTRY(2, 0x0),
        /* Giant's Knife */ DMG_ENTRY(2, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(2, 0x1),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(2, 0x1),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(1, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
    { {
        // 22 Used by En_Du, En_Go, En_Ma1, En_Ma2, En_Ma3
        /* Deku nut      */ DMG_ENTRY(0, 0x0),
        /* Deku stick    */ DMG_ENTRY(0, 0x0),
        /* Slingshot     */ DMG_ENTRY(0, 0x0),
        /* Explosive     */ DMG_ENTRY(0, 0x0),
        /* Boomerang     */ DMG_ENTRY(0, 0x0),
        /* Normal arrow  */ DMG_ENTRY(0, 0x0),
        /* Hammer swing  */ DMG_ENTRY(0, 0x0),
        /* Hookshot      */ DMG_ENTRY(0, 0x0),
        /* Kokiri sword  */ DMG_ENTRY(0, 0x0),
        /* Master sword  */ DMG_ENTRY(0, 0x0),
        /* Giant's Knife */ DMG_ENTRY(0, 0x0),
        /* Fire arrow    */ DMG_ENTRY(0, 0x0),
        /* Ice arrow     */ DMG_ENTRY(0, 0x0),
        /* Light arrow   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 1   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 2   */ DMG_ENTRY(0, 0x0),
        /* Unk arrow 3   */ DMG_ENTRY(0, 0x0),
        /* Fire magic    */ DMG_ENTRY(0, 0x0),
        /* Ice magic     */ DMG_ENTRY(0, 0x0),
        /* Light magic   */ DMG_ENTRY(0, 0x0),
        /* Shield        */ DMG_ENTRY(0, 0x0),
        /* Mirror Ray    */ DMG_ENTRY(0, 0x0),
        /* Kokiri spin   */ DMG_ENTRY(0, 0x0),
        /* Giant spin    */ DMG_ENTRY(0, 0x0),
        /* Master spin   */ DMG_ENTRY(0, 0x0),
        /* Kokiri jump   */ DMG_ENTRY(0, 0x0),
        /* Giant jump    */ DMG_ENTRY(0, 0x0),
        /* Master jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 1     */ DMG_ENTRY(0, 0x0),
        /* Unblockable   */ DMG_ENTRY(0, 0x0),
        /* Hammer jump   */ DMG_ENTRY(0, 0x0),
        /* Unknown 2     */ DMG_ENTRY(0, 0x0),
    } },
};

// Gets the pointer to one of the 23 preset damage tables. Returns NULL if index is out of range.
DamageTable* DamageTable_Get(s32 index) {
    if (!(0 <= index && index < ARRAY_COUNT(sDamageTablePresets))) {
        PRINTF(T("CollisionBtlTbl_get():インデックスオーバー\n", "CollisionBtlTbl_get(): Index over\n"));
        return NULL;
    }
    return &sDamageTablePresets[index];
}

// Sets all entries in the damage table to 0x00
void DamageTable_Clear(DamageTable* table) {
    s32 i;
    for (i = 0; i < 32; i++) {
        table->table[i] = 0;
    }
}
