#ifndef _Z_En_Freezer_H_
#define _Z_En_Freezer_H_

#include "ultra64.h"
#include "global.h"

typedef struct En_Freezer {
    Actor actor;
    u8 counter;
    u8 isEffectSpawned;
    u8 categories[12];
    u16 dayTime;
} En_Freezer;

extern const ActorInit En_Freezer_InitVars;

#endif
