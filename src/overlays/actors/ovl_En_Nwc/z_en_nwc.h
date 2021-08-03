#ifndef _Z_EN_NWC_H_
#define _Z_EN_NWC_H_

#include "ultra64.h"
#include "global.h"

struct EnNwc;

typedef void (*EnNwcActionFunc)(struct EnNwc*, GlobalContext*);
typedef void (*EnNwcSpawnFunc)(struct EnNwc*, GlobalContext*);

typedef struct EnNwc {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ EnNwcActionFunc actionFunc;
    /* 0x0150 */ Actor* actorSpawnPtrList[12]; // pointers to all of the actors spawned by the parent
    /* 0x0180 */ u16 currentActorNum; // used to keep track of of the index to actorSpawnPtrList
    /* 0x0184 */ u16 unk_16C;
} EnNwc; // size = 0x0170

extern const ActorInit Obj_EnNwc_InitVars;

// struct EnNwc;
// struct EnNwcChick;

// typedef void (*EnNwcUpdateFunc)(struct EnNwc*, GlobalContext*);
// typedef void (*EnNwcChickFunc)(struct EnNwcChick*, struct EnNwc*, GlobalContext*);

// typedef struct EnNwcChick {
//     /* 0x00 */ s8 type;
//     /* 0x01 */ u8 bgFlags;
//     /* 0x04 */ f32 floorY;
//     /* 0x08 */ Vec3f pos;
//     /* 0x14 */ char unk_14[8];
//     /* 0x1C */ Vec3f lastPos;
//     /* 0x28 */ char unk_28[4];
//     /* 0x2C */ f32 velY;
//     /* 0x30 */ Vec3s rot;
//     /* 0x36 */ u16 height;
//     /* 0x38 */ CollisionPoly* floorPoly;
//     /* 0x44 */ char unk_3C[0x20]; 
// } EnNwcChick; // size = 0x5C

// typedef struct EnNwc {
//     /* 0x0000 */ Actor actor;
//     /* 0x014C */ ColliderJntSph collider;
//     /* 0x016C */ u8 count;
//     /* 0x0170 */ EnNwcChick chicks[16];
//     /* 0x0730 */ EnNwcUpdateFunc updateFunc;
// } EnNwc; // size = 0x0734

// extern const ActorInit En_Nwc_InitVars;

#endif
