#ifndef BG_POISONED_WATER_H
#define BG_POISONED_WATER_H

#include "ultra64.h"
#include "global.h"
#include "vt.h"

#define INTERACTS_WITH_WATERBOX(this) (((this)->actor.bgCheckFlags & 0x020) ? true : false)

typedef struct BgPoisonedWater {
    Actor actor;
    s8 size;
    s8 damageAmount;
    u8 switchFlag;
    u8 colorIndex;
} BgPoisonedWater;

#endif
