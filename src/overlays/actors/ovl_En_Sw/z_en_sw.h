#ifndef Z_EN_SW_H
#define Z_EN_SW_H

#include "ultra64.h"
#include "global.h"

struct EnSw;

typedef void (*EnSwActionFunc)(struct EnSw* this, PlayState* play);

typedef enum {
    /* 0x00 */ TYPE_SKULLWALLTULA,
    /* 0x01 */ TYPE_GS_FREESTANDING,
    /* 0x02 */ TYPE_GS_APPEARS,
    /* 0x03 */ TYPE_GS_SPAWN_UP_SFX_DUST,
    /* 0x04 */ TYPE_GS_SPAWN_NO_UP_SFX_DUST,
    /* 0x05 */ TYPE_MAX
} EnSwType;

typedef struct EnSw {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ EnSwActionFunc actionFunc;
    /* 0x0194 */ ColliderJntSph collider;
    /* 0x01B4 */ ColliderJntSphElement sphs[1];
    /* 0x01F4 */ Color_RGBA8 unk_1F4;
    /* 0x01F8 */ Vec3s jointTable[30];
    /* 0x02AC */ Vec3s morphTable[30];
    /* 0x0360 */ u8 isFalling; // bool
    /* 0x0364 */ Vec3f unk_364;
    /* 0x0370 */ Vec3f unk_370;
    /* 0x037C */ Vec3f unk_37C;
    /* 0x0388 */ s16 unk_388; // timer
    /* 0x038A */ s16 unk_38A; // timer
    /* 0x038C */ s16 unk_38C; // (spawn + ?) timer
    /* 0x038E */ s16 unk_38E; // timer
    /* 0x0390 */ s16 atOffTimer;
    /* 0x0392 */ s16 invisibilityTimer;
    /* 0x0394 */ s16 unk_394; // timer
    /* 0x0396 */ char pad1[0x42];
    /* 0x03D8 */ MtxF unk_3D8;
    /* 0x0418 */ char pad2[8];
    /* 0x0420 */ f32 unk_420;
    /* 0x0424 */ char pad3[0x8];
    /* 0x042C */ u8 unusedBool;
    /* 0x0430 */ CollisionPoly* skullwalltulaPoly;
    /* 0x0434 */ Vec3f unk_434; // unused pos
    /* 0x0440 */ s16 unk_440; // used for SFX
    /* 0x0442 */ s16 seenTimer; // for skullwalltulas
    /* 0x0444 */ s16 unk_444;
    /* 0x0446 */ s16 unk_446; // unused
    /* 0x0448 */ Vec3f skullwalltulaDest;
    /* 0x0454 */ Vec3f unk_454;
    /* 0x0460 */ Vec3f unk_460;
    /* 0x046C */ Vec3f unk_46C;
    /* 0x0478 */ Vec3f unk_478;
    /* 0x0484 */ Vec3f unk_484;
    /* 0x0490 */ char pad4[0x48];
} EnSw; // size = 0x04D8

#endif
