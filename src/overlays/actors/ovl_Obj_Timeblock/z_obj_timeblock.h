#ifndef Z_OBJ_TIMEBLOCK_H
#define Z_OBJ_TIMEBLOCK_H

#include "ultra64.h"
#include "global.h"

struct ObjTimeblock;

typedef s32 (*ObjTimeblockSongObserverFunc)(struct ObjTimeblock*, GlobalContext*);
typedef void (*ObjTimeblockActionFunc)(struct ObjTimeblock*, GlobalContext*);

typedef struct ObjTimeblock {
    /* 0x0000 */ DynaPolyActor dyna;
    /* 0x0164 */ ObjTimeblockActionFunc actionFunc;
    /* 0x0168 */ ObjTimeblockSongObserverFunc songObserverFunc;
    /* 0x016C */ s16 demoEffectTimer;
    /* 0x016E */ s16 songEndTimer;
    /* 0x0170 */ s16 demoEffectFirstPartTimer;
    /* 0x0172 */ u16 unk_172;   // last song played, 254 = is staff active
    /* 0x0174 */ u8 unk_174;    // switchFlagIsSet
    /* 0x0175 */ u8 unk_175;    // age inversion: 0 = normal - not inverted, 1 = age inverted
    /* 0x0176 */ u8 unk_176;    // used for alt behavior, same value as unk_174 when the cutscene plays
    /* 0x0177 */ u8 unk_177;    // default visibility: 0 = child visible, 1 = adult visible
    /* 0x0178 */ u8 isVisible;
} ObjTimeblock; // size = 0x017C

#endif
