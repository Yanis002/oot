#ifndef BG_POISONED_WATER_H
#define BG_POISONED_WATER_H

#include "ultra64.h"
#include "global.h"
#include "vt.h"

typedef struct BgPoisonedWater {
    Actor actor;
    s8 size;
    s8 damageAmount;
    s8 damageFreq;
    s8 hueShift;
} BgPoisonedWater;

#endif
