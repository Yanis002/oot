/*
IDEAS:
- Spawns a waterbox, checks if Player's inside, if so deals damages

PARAMETERS:
0000 0000 0011 1111 - Switch Flag                                      - 0x003F, ``params & 0x3F``
0000 0001 1100 0000 - Color Array Index                                - 0x01C0, ``(params >> 6) & 0x3``
0000 1110 0000 0000 - Size                                             - 0x0E00, ``(params >> 9) & 0x3``
1111 0000 0000 0000 - Amount of Damages % Increase (base = 1/4 hearts) - 0xF000, ``(params >> 12) & 0xF``

POISONED WATER ACTOR:
- Switch Flag: set = water not poisoned, cleared = water poisoned
- if poisoned: green color for the water
- if not poisoned: blue color for the water
- if actor not in a waterbox: actor_kill
- if actor in a waterbox: get the index and set damages

Draw:
- 1 surface with multitexture/moving thing
- 1 "color filter" surface to change the color
*/

#include "z_bg_poisoned_water.h"
#include "objects/object_poisoned_water/object_poisoned_water.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void BgPoisonedWater_Init(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_Update(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Bg_Poisoned_Water_InitVars = {
    ACTOR_BG_POISONED_WATER,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_POISONED_WATER,
    sizeof(BgPoisonedWater),
    (ActorFunc)BgPoisonedWater_Init,
    (ActorFunc)BgPoisonedWater_Destroy,
    (ActorFunc)BgPoisonedWater_Update,
    (ActorFunc)BgPoisonedWater_Draw,
};

static Color_RGB8 poisonColors[] = {
    {128,   0,      0},       // red
    {0,     128,    255},     // blue
    {0,     128,    0},       // green
    {128,   128,    0},       // yellow
    {255,   128,    0},       // orange
    {64,    0,      128},     // purple
    {128,   64,     0},       // brown
};

void BgPoisonedWater_Init(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    s16 params = this->actor.params;

    osSyncPrintf("---- BG_POISONED_WATER INIT: START! ----\n");

    this->size = ((params >> 9) & 0x3);
    this->damageAmount = ((params >> 12) & 0xF);
    this->switchFlag = (params & 0x3F);
    this->colorIndex = (((params >> 6) & 0x3) >= ARRAY_COUNT(poisonColors)) ? 0 : ((params >> 6) & 0x3);
    
    osSyncPrintf(VT_FGCOL(YELLOW) "Parameters joined the game.\nParams: 0x%hX\nSize: %d\nDamage Amount: %d\nFlag: %d\n" VT_FGCOL(WHITE),
        params, this->size, this->damageAmount, this->switchFlag);

    osSyncPrintf("True Colors: %d, %d, %d\n", poisonColors[this->colorIndex].r, poisonColors[this->colorIndex].g, poisonColors[this->colorIndex].b);

    if (this->size != 0) {
        osSyncPrintf("Parameter Power, Scale-Up!\n");
        Actor_SetScale(&this->actor, (this->size * 0.25));
    }

    osSyncPrintf("---- BG_POISONED_WATER INIT: END! ----\n");
}

void BgPoisonedWater_Destroy(Actor* thisx, GlobalContext* globalCtx){
}

void BgPoisonedWater_Update(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    // osSyncPrintf("INTERACTS_WITH_WATERBOX: %d\n", INTERACTS_WITH_WATERBOX(this));
}

void BgPoisonedWater_Draw(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    s32 gameplayFrames;

    OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

    gameplayFrames = globalCtx->gameplayFrames;
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 127 - (gameplayFrames % 128), (gameplayFrames * 1) % 128,
                                32, 32, 1, gameplayFrames % 128, (gameplayFrames * 1) % 128, 32, 32));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0,
        poisonColors[this->colorIndex].r, poisonColors[this->colorIndex].g, poisonColors[this->colorIndex].b, 127);
    gSPDisplayList(POLY_XLU_DISP++, gColorFilterDL);
    gSPDisplayList(POLY_XLU_DISP++, gPoisonedWaterDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}
