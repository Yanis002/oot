#ifndef Z_EN_ICE_TRAP_H
#define Z_EN_ICE_TRAP_H

#include "ultra64.h"
#include "global.h"

extern const ActorInit En_Trap_Item_InitVars;

#define GET_ITEM_TYPE(params) (((params) & 0x7) < ITEM_TYPE_MAX ? ((params) & 0x7) : ITEM_TYPE_HEART_PIECE)
#define GET_TRAP_TYPE(params) ((((params) >> 0x3) & 0x7) < TRAP_TYPE_MAX ? (((params) >> 0x3) & 0x7) : TRAP_TYPE_ICE)

typedef enum {
    /* 0x00 */ ITEM_TYPE_HEART_PIECE,
    /* 0x01 */ ITEM_TYPE_GREEN_RUPEE,
    /* 0x02 */ ITEM_TYPE_BLUE_RUPEE,
    /* 0x03 */ ITEM_TYPE_RED_RUPEE,
    /* 0x04 */ ITEM_TYPE_PURPLE_RUPEE,
    /* 0x05 */ ITEM_TYPE_GOLD_RUPEE,
    /* 0x06 */ ITEM_TYPE_MAX
} EnTrapItemItemType;

typedef enum {
    /* 0x00 */ TRAP_TYPE_ICE,
    /* 0x01 */ TRAP_TYPE_EXPLOSION,
    /* 0x02 */ TRAP_TYPE_CRUSH,
    /* 0x03 */ TRAP_TYPE_FIRE,
    /* 0x04 */ TRAP_TYPE_ELECTRICITY,
    /* 0x05 */ TRAP_TYPE_MAX
} EnTrapItemTrapType;

typedef struct En_Ice_Trap {
    Actor actor;
} EnTrapItem;

#endif
