/*
IDEAS:
- Spawns a waterbox, checks if Player's inside, if so deals damages

PARAMETERS:
0000 0000 0000 0111 - size (0 to 0x7) | ``params & 0x7``
0000 0001 1111 1000 - amount of damages (0 to 0x32) | ``(params >> 3) & 0x1F``
0001 1110 0000 0000 - frequency of damages (0 to 0xA) | ``(params >> 9) & 0xF``
1110 0000 0000 0000 - color (hue shift) | ``(params >> 13) & 0x7``
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

void BgPoisonedWater_Init(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    s16 params = this->actor.params;
    osSyncPrintf("---- BG_POISONED_WATER INIT: START! ----\n");

    this->size = (params & 0x7);
    this->damageAmount = (params >> 3) & 0x1F;
    this->damageFreq = (params >> 9) & 0xF;
    this->hueShift = (params >> 13) & 0x7;

    osSyncPrintf(VT_FGCOL(YELLOW));
    osSyncPrintf("Parameters joined the game.\n Size: %d\n Damage Amount: %d\n Damage Frequency: %d\n Hue Shift: %d\n",
        this->size, this->damageAmount, this->damageFreq, this->hueShift);
    osSyncPrintf(VT_FGCOL(WHITE));
    osSyncPrintf("---- BG_POISONED_WATER INIT: END! ----\n");
}

void BgPoisonedWater_Destroy(Actor* thisx, GlobalContext* globalCtx){

}

void BgPoisonedWater_Update(Actor* thisx, GlobalContext* globalCtx){

}

void BgPoisonedWater_Draw(Actor* thisx, GlobalContext* globalCtx){

}
