#ifndef Z_EN_RIVER_SOUND_H
#define Z_EN_RIVER_SOUND_H

#include "ultra64.h"
#include "global.h"

struct EnRiverSound;

typedef struct EnRiverSound {
    /* 0x0000 */ Actor actor;
    /* 0x014C */ u8 playSound;
    /* 0x014D */ u8 soundPitchIndex;
    /* 0x014E */ s16 pathIndex;
} EnRiverSound; // size = 0x0150

typedef enum {
    /* 0x00 */ RS_UNK_0, // river (multi point)
    /* 0x01 */ RS_SMALL_WATERFALL,
    /* 0x02 */ RS_LAVA_BUBBLES_1,
    /* 0x03 */ RS_LARGE_WATERFALL,
    /* 0x04 */ RS_UNK_4, // small stream
    /* 0x05 */ RS_UNK_5, // water stream sound
    /* 0x06 */ RS_LAVA_BUBBLES_2,
    /* 0x07 */ RS_LAVA_BUBBLES_3,
    /* 0x08 */ RS_DRIPPING_WATER,
    /* 0x09 */ RS_FOUNTAIN_WATER,
    /* 0x0A */ RS_MARKET_CROWD,
    /* 0x0B */ RS_UNK_11, // used to decrease the volume of the market music in market entrance scene
    /* 0x0C */ RS_SARIAS_SONG,
    /* 0x0D */ RS_UNK_13, // proximity saria's song
    /* 0x0E */ RS_SANDSTORM,
    /* 0x0F */ RS_LAKESIDE_LAB_TANK,
    /* 0x10 */ RS_CHAMBER_OF_SAGES_1,
    /* 0x11 */ RS_CHAMBER_OF_SAGES_2,
    /* 0x12 */ RS_RUMBLING,
    /* 0x13 */ RS_UNK_19, // plays fairy fountain BGM
    /* 0x14 */ RS_TORCH_CRACKLING,
    /* 0x15 */ RS_COW_MOOING,
    // change the current BGM to the nighttime BGM in areas where time don't pass
    // also used in lost woods for the bridge entrances from field and forest
    /* 0xF7 */ RS_UNK_F7 = 0xF7,
    /* 0xF8 */ RS_MAX
} RiverSoundType;

#endif
