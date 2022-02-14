#ifndef BG_POISONED_WATER_H
#define BG_POISONED_WATER_H

#include "ultra64.h"
#include "global.h"
#include "vt.h"

// Colors
#define CUSTOM_COLOR_MODE(this) ((((this)->actor.home.rot.z >> 12) & 0x1) == 1 ? true : false)
#define COLOR_R(this) ((((this)->actor.home.rot.x) >> 8) & 0xFF)
#define COLOR_G(this) (((this)->actor.home.rot.x) & 0xFF)
#define COLOR_B(this) ((((this)->actor.home.rot.y) >> 8) & 0xFF)
#define COLOR_A(this) ((((this)->actor.home.rot.y) & 0xFF) >= 64 ? 63 : (((this)->actor.home.rot.y) & 0xFF))
#define ALPHA(this) (CUSTOM_COLOR_MODE(this) ? COLOR_A(this) : 32)
#define GET_POISON_COLOR(this) (CUSTOM_COLOR_MODE(this) ? (this)->customRGB : poisonColors[(this)->poisonColorIndex])
#define GET_HEAL_COLOR(this) (healColors[(this)->healColorIndex])

// Parameters
#define MODE_HEAL(this) (((this)->actor.home.rot.z >> 8) & 0x1)
#define GET_DIVISOR(this) ((((this)->actor.home.rot.z >> 4) & 0xF) == 0 ? 1 : (((this)->actor.home.rot.z >> 4) & 0xF))
#define GET_TIMER(this) (((this)->actor.home.rot.z & 0xF) * (20 / GET_DIVISOR(this)))
#define GET_SWITCH_FLAG(globalCtx, this) ((MODE_HEAL(this) == true) ? Flags_GetSwitch(globalCtx, (this)->switchFlag) : false)

// GET_POS return true if Player's inside WaterBox bounds
#define POINT1(playerX, playerZ, this) (((playerX > (this)->pos1.x) && (playerZ > (this)->pos1.z)) ? true : false)
#define POINT2(playerX, playerZ, this) (((playerX < (this)->pos2.x) && (playerZ > (this)->pos2.z)) ? true : false)
#define POINT3(playerX, playerZ, this) (((playerX > (this)->pos3.x) && (playerZ < (this)->pos3.z)) ? true : false)
#define POINT4(playerX, playerZ, this) (((playerX < (this)->pos4.x) && (playerZ < (this)->pos4.z)) ? true : false)
#define GET_POS(playerX, playerZ, this) ((POINT1(playerX, playerZ, this) && POINT2(playerX, playerZ, this) && POINT3(playerX, playerZ, this) && POINT4(playerX, playerZ, this)) ? true : false)
#define INTERACTS_WITH_WATERBOX(actor) (((actor).bgCheckFlags & 0x020) ? true : false)

typedef struct BgPoisonedWater {
    Actor actor;
    u8 poisonColorIndex;
    u8 healColorIndex;
    u8 alpha; // color filter alpha
    s8 size;
    s8 timer; // used to set the frequency of damages
    s32 damageAmount; // 1 for 1/4 hearts
    s32 switchFlag;
    Vec3f pos1; // corner 1 of the waterbox
    Vec3f pos2; // corner 2 of the waterbox
    Vec3f pos3; // corner 3 of the waterbox
    Vec3f pos4; // corner 4 of the waterbox
    WaterBox* waterBox;
    Color_RGB8 rgb;
    Color_RGB8 customRGB;
} BgPoisonedWater;

#endif
