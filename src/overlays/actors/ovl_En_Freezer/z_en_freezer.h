#ifndef _Z_En_Freezer_H_
#define _Z_En_Freezer_H_

#include "ultra64.h"
#include "global.h"

typedef struct En_Freezer {
    Actor actor;
    u8 counter;
    u8 isEffectSpawned;
    u8 isCase1;
    u16 duration;
} En_Freezer;

extern const ActorInit En_Freezer_InitVars;

#endif
