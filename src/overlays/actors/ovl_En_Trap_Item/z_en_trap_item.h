#ifndef Z_EN_TRAP_ITEM_H
#define Z_EN_TRAP_ITEM_H

#include "ultra64.h"
#include "global.h"

extern const ActorInit En_Trap_Item_InitVars;

#define GET_ITEM_TYPE(params) (((params) & 0xF) < ITEM_TYPE_MAX ? ((params) & 0xF) : ITEM_TYPE_HEART)
#define GET_TRAP_TYPE(params) ((((params) >> 0x4) & 0x7) < TRAP_TYPE_MAX ? (((params) >> 0x4) & 0x7) : TRAP_TYPE_ICE)
#define GET_ITEM_SUBTYPE(params) ((((params) >> 0x7) & 0x1F) < SUBTYPE_MAX ? (((params) >> 0x7) & 0x1F) : SUBTYPE_NONE)

typedef enum {
    /* 0x00 */ ITEM_TYPE_HEART,
    /* 0x01 */ ITEM_TYPE_RUPEE,
    /* 0x02 */ ITEM_TYPE_MAGIC,
    /* 0x03 */ ITEM_TYPE_SHIELD,
    /* 0x04 */ ITEM_TYPE_ARROW,
    /* 0x05 */ ITEM_TYPE_TUNIC,
    /* 0x06 */ ITEM_TYPE_SMALL_KEY,
    /* 0x07 */ ITEM_TYPE_BOMBS,
    /* 0x08 */ ITEM_TYPE_NUTS,
    /* 0x09 */ ITEM_TYPE_STICK,
    /* 0x0A */ ITEM_TYPE_SEEDS,
    /* 0x0B */ ITEM_TYPE_MAX
} EnTrapItemItemType;

typedef enum {
    /* 0x00 */ SUBTYPE_MAGIC_LARGE,
    /* 0x01 */ SUBTYPE_MAGIC_SMALL,
    /* 0x02 */ SUBTYPE_SHIELD_DEKU,
    /* 0x03 */ SUBTYPE_SHIELD_HYLIAN,
    /* 0x04 */ SUBTYPE_TUNIC_ZORA,
    /* 0x05 */ SUBTYPE_TUNIC_GORON,
    /* 0x06 */ SUBTYPE_HEART_RECOVERY,
    /* 0x07 */ SUBTYPE_HEART_PIECE,
    /* 0x08 */ SUBTYPE_HEART_CONTAINER,
    /* 0x09 */ SUBTYPE_ARROW_SINGLE,
    /* 0x0A */ SUBTYPE_ARROW_SMALL,
    /* 0x0B */ SUBTYPE_ARROW_MEDIUM,
    /* 0x0C */ SUBTYPE_ARROW_LARGE,
    /* 0x0D */ SUBTYPE_RUPEE_GREEN,
    /* 0x0E */ SUBTYPE_RUPEE_BLUE,
    /* 0x0F */ SUBTYPE_RUPEE_RED,
    /* 0x10 */ SUBTYPE_RUPEE_PURPLE,
    /* 0x11 */ SUBTYPE_RUPEE_ORANGE,
    /* 0x12 */ SUBTYPE_MAX,
    /* 0xFF */ SUBTYPE_NONE = 0xFF
} EnTrapItemSubType;

typedef enum {
    /* 0x00 */ TRAP_TYPE_ICE,
    /* 0x01 */ TRAP_TYPE_EXPLOSION,
    /* 0x02 */ TRAP_TYPE_CRUSH,
    /* 0x03 */ TRAP_TYPE_FIRE,
    /* 0x04 */ TRAP_TYPE_ELECTRICITY,
    /* 0x05 */ TRAP_TYPE_MAX
} EnTrapItemTrapType;

typedef struct EnTrapItem {
    Actor actor;
    ColliderCylinder collider;
    f32 yOffset;
    f32 shadowScale;
    u8 texIndex;
    u8 bankIndex;
} EnTrapItem;

#endif
