#ifndef _Z_OBJ_MURE4_H_
#define _Z_OBJ_MURE4_H_

#include "ultra64.h"
#include "global.h"

typedef struct ObjMure4 {
    Actor actor;
    Actor* actorPtrList[255];
    s16 ptrNb;
} ObjMure4;

extern const ActorInit Obj_Mure4_InitVars;

#endif
