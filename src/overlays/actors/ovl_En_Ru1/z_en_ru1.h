#ifndef Z_EN_RU1_H
#define Z_EN_RU1_H

#include "ultra64.h"
#include "global.h"

#include "overlays/actors/ovl_Bg_Bdan_Objects/z_bg_bdan_objects.h"
#include "overlays/actors/ovl_Door_Warp1/z_door_warp1.h"

struct EnRu1;

typedef void (*EnRu1ActionFunc)(struct EnRu1*, PlayState*);
typedef void (*EnRu1DrawFunc)(struct EnRu1*, PlayState*);
typedef void (*EnRu1PreLimbDrawFunc)(struct EnRu1*, PlayState*, s32, Vec3s*);

typedef enum {
    /* 0x00 */ RUTO_TYPE_WARP,
    /* 0x01 */ RUTO_TYPE_SAPPHIRE_CS,
    /* 0x02 */ RUTO_TYPE_FIRST_TIME_MEET,
    /* 0x03 */ RUTO_TYPE_CARRY,
    /* 0x04 */ RUTO_TYPE_BIG_OCTO_CS,
    /* 0x05 */ RUTO_TYPE_UNK5,
    /* 0x06 */ RUTO_TYPE_UNK6,
    /* 0x0A */ RUTO_TYPE_UNKA = 0xA
} EnRu1Type;

typedef enum {
    /* 0 */ RUTO_DRAW_NOTHING,
    /* 1 */ RUTO_DRAW_OPA,
    /* 2 */ RUTO_DRAW_XLU
} EnRu1DrawConfig;

typedef enum {
    /* 00 */ RUTO_ACTION_00,
    /* 01 */ RUTO_ACTION_01,
    /* 02 */ RUTO_ACTION_02,
    /* 03 */ RUTO_ACTION_03,
    /* 04 */ RUTO_ACTION_04,
    /* 05 */ RUTO_ACTION_05,
    /* 06 */ RUTO_ACTION_06,
    /* 07 */ RUTO_ACTION_FIRST_TIME_MEET_CS,
    /* 08 */ RUTO_ACTION_08,
    /* 09 */ RUTO_ACTION_09,
    /* 10 */ RUTO_ACTION_10,
    /* 11 */ RUTO_ACTION_11, // unused?
    /* 12 */ RUTO_ACTION_12,
    /* 13 */ RUTO_ACTION_13,
    /* 14 */ RUTO_ACTION_14,
    /* 15 */ RUTO_ACTION_15,
    /* 16 */ RUTO_ACTION_16,
    /* 17 */ RUTO_ACTION_17,
    /* 18 */ RUTO_ACTION_18,
    /* 19 */ RUTO_ACTION_19, // unused?
    /* 20 */ RUTO_ACTION_20,
    /* 21 */ RUTO_ACTION_21,
    /* 22 */ RUTO_ACTION_22,
    /* 23 */ RUTO_ACTION_23,
    /* 24 */ RUTO_ACTION_24,
    /* 25 */ RUTO_ACTION_25,
    /* 26 */ RUTO_ACTION_26,
    /* 27 */ RUTO_ACTION_27,
    /* 28 */ RUTO_ACTION_28,
    /* 29 */ RUTO_ACTION_29,
    /* 30 */ RUTO_ACTION_30,
    /* 31 */ RUTO_ACTION_SIT_AND_SQUIRM,
    /* 32 */ RUTO_ACTION_SIT_IDLE,
    /* 33 */ RUTO_ACTION_33,
    /* 34 */ RUTO_ACTION_34,
    /* 35 */ RUTO_ACTION_35, // unused?
    /* 36 */ RUTO_ACTION_36,
    /* 37 */ RUTO_ACTION_37,
    /* 38 */ RUTO_ACTION_38,
    /* 39 */ RUTO_ACTION_39,
    /* 40 */ RUTO_ACTION_40,
    /* 41 */ RUTO_ACTION_41,
    /* 42 */ RUTO_ACTION_42,
    /* 43 */ RUTO_ACTION_43,
    /* 44 */ RUTO_ACTION_44,
    /* 45 */ RUTO_ACTION_45
} EnRu1Action;

typedef struct EnRu1 {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ SkelAnime skelAnime;
    /* 0x0190 */ Vec3s jointTable[17];
    /* 0x01F6 */ Vec3s morphTable[17];
    /* 0x025C */ s16 eyeIndex;
    /* 0x025E */ s16 blinkTimer;
    /* 0x0260 */ s16 mouthIndex;
    /* 0x0264 */ s32 action;
    /* 0x0268 */ s32 drawConfig;
    /* 0x026C */ f32 unk_26C; // gravity?
    /* 0x0270 */ f32 unk_270;
    /* 0x0274 */ char unk_274[0x4];
    /* 0x0278 */ DoorWarp1* blueWarp;
    /* 0x027C */ f32 unk_27C;
    /* 0x0280 */ s32 unk_280;
    /* 0x0284 */ s8 roomNum1;
    /* 0x0285 */ s8 roomNum2;
    /* 0x0286 */ s8 roomNum3;
    /* 0x0288 */ f32 unused;
    /* 0x028C */ BgBdanObjects* bgBdanObjectsActor;
    /* 0x0290 */ s32 preLimbDrawConfig;
    /* 0x0294 */ char unk_294[0x4];
    /* 0x0298 */ s32 divingSoundPlayed;
    /* 0x029C */ char unk_29C[0x2];
    /* 0x029E */ s16 unk_29E;
    /* 0x02A0 */ char unk_2A0[0x4];
    /* 0x02A4 */ f32 unk_2A4;
    /* 0x02A8 */ s32 alpha;
    /* 0x02AC */ s16 unk_2AC;
    /* 0x02B0 */ s32 unk_2B0;
    /* 0x02B4 */ ColliderCylinder collider;
    /* 0x0300 */ ColliderCylinder collider2;
    /* 0x034C */ s32 ocEnabled;
    /* 0x0350 */ s32 unk_350;
    /* 0x0354 */ f32 unk_354;
    /* 0x0358 */ f32 unk_358;
    /* 0x035C */ s16 unk_35C;
    /* 0x0360 */ f32 unk_360;
    /* 0x0364 */ Vec3f unk_364;
    /* 0x0370 */ f32 sitAnimChangeTimer;
    /* 0x0374 */ struct_80034A14_arg1 unk_374;
} EnRu1; // size = 0x039C

typedef enum {
    /* 0 */ RUTO_CHILD_ROOT,
    /* 1 */ RUTO_CHILD_LEFT_THIGH,
    /* 2 */ RUTO_CHILD_LEFT_SHIN,
    /* 3 */ RUTO_CHILD_LEFT_FOOT,
    /* 4 */ RUTO_CHILD_RIGHT_THIGH,
    /* 5 */ RUTO_CHILD_RIGHT_SHIN,
    /* 6 */ RUTO_CHILD_RIGHT_FOOT,
    /* 7 */ RUTO_CHILD_CHEST,
    /* 8 */ RUTO_CHILD_LEFT_UPPER_ARM,
    /* 9 */ RUTO_CHILD_LEFT_FIN,
    /* 10 */ RUTO_CHILD_LEFT_HAND,
    /* 11 */ RUTO_CHILD_RIGHT_UPPER_ARM,
    /* 12 */ RUTO_CHILD_RIGHT_FIN,
    /* 13 */ RUTO_CHILD_RIGHT_HAND,
    /* 14 */ RUTO_CHILD_HEAD,
    /* 15 */ RUTO_CHILD_TORSO
} RutoLimb;

#endif
