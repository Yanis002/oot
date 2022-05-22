#ifndef Z_EN_TRAP_ITEM_H
#define Z_EN_TRAP_ITEM_H

#include "ultra64.h"
#include "global.h"

extern const ActorInit En_Trap_Item_InitVars;

struct EnTrapItem;
typedef void (*EnTrapItemActionFunc)(struct EnTrapItem*, PlayState*);

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
    /* 0x00 */ ENEMY_TYPE_MUSCLE,
    /* 0x01 */ ENEMY_TYPE_DODONGO,
    /* 0x02 */ ENEMY_TYPE_FREEZARD,
    /* 0x03 */ ENEMY_TYPE_KNUCKLE,
    /* 0x04 */ ENEMY_TYPE_PEAHAT,
    /* 0x05 */ ENEMY_TYPE_REDEAD,
    /* 0x06 */ ENEMY_TYPE_STALFOS,
    /* 0x07 */ ENEMY_TYPE_LIZALFOS,
    /* 0x08 */ ENEMY_TYPE_WALLMASTER,
    /* 0x09 */ ENEMY_TYPE_LIKELIKE,
    /* 0x0A */ ENEMY_TYPE_MAX
} EnTrapItemEnemyType;

typedef enum {
    /* 0x00 */ TRAP_TYPE_ICE,
    /* 0x01 */ TRAP_TYPE_EXPLOSION,
    /* 0x02 */ TRAP_TYPE_VOID,
    /* 0x03 */ TRAP_TYPE_FIRE,
    /* 0x04 */ TRAP_TYPE_ELECTRICITY,
    /* 0x05 */ TRAP_TYPE_CUCCO,
    /* 0x06 */ TRAP_TYPE_ENEMY,
    /* 0x07 */ TRAP_TYPE_MAX
} EnTrapItemTrapType;

typedef enum {
    /* 0x00 */ MODE_DEFAULT,
    /* 0x01 */ MODE_SWITCH,
    /* 0x02 */ MODE_MAX
} EnTrapItemMode;

typedef struct EnTrapItem {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ ColliderCylinder collider;
    /* 0x0198 */ EnTrapItemActionFunc actionFunc;
    /* 0x019C */ f32 scale;
    /* 0x01A0 */ f32 shadowScale;
    /* 0x01A4 */ f32 yOffset;
    /* 0x01A6 */ s16 enemySwitchFlag;
    /* 0x01A8 */ s16 switchFlag;
    /* 0x01A9 */ u8 bankIndex;
    /* 0x01AA */ u8 enemyCount;
    /* 0x01AB */ u8 enemyType;
    /* 0x01AC */ u8 isNotFreestanding;
    /* 0x01AD */ u8 itemSubType;
    /* 0x01AE */ u8 itemType;
    /* 0x01AF */ u8 mode;
    /* 0x01B0 */ u8 texIndex;
    /* 0x01B1 */ u8 killTimer;
    /* 0x01B2 */ u8 trapType;
} EnTrapItem; // size = 0x01B3

#endif
