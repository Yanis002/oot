#ifndef _Z_En_Freezer_H_
#define _Z_En_Freezer_H_

#include "ultra64.h"
#include "global.h"

typedef struct En_Freezer {
    Actor actor;
    u8 counter;
    u8 alpha;
    u8 isEffectSpawned;
    u8 categories[12];
    u8 boolTimeSky;
    u8 isDurationReached;
    u8 fadeIn;
    u8 fadeOut;
    u16 duration;
    u16 dayTime;
    Vec3f skyRot;
    Color_RGB8 rgb;
} En_Freezer;

extern const ActorInit En_Freezer_InitVars;

#endif
