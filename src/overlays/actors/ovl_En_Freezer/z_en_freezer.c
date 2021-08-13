/*
 * File: z_en_freezer.c
 * Overlay: ovl_En_Freezer
 * Description: Time stop (literally)
 */

//TODO: prevent using c-buttons while time is stopped

#include "z_en_freezer.h"

#define THIS ((En_Freezer*)thisx)

void En_Freezer_Init(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Freezer_InitVars = {
    ACTOR_EN_FREEZER,
    ACTORCAT_MISC,
    0x00000030, // always run update and draw
    OBJECT_GAMEPLAY_KEEP,
    sizeof(En_Freezer),
    (ActorFunc)En_Freezer_Init,
    (ActorFunc)En_Freezer_Destroy,
    (ActorFunc)En_Freezer_Update,
    NULL,
};

void En_Freezer_Init(Actor* thisx, GlobalContext* globalCtx) {
    osSyncPrintf("Hello Jack, Dragorn, Tharo and Fig!");
    D_801614B0.a = 0;
}

void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

u8 boolFreezer = 0;
s32 duration = 0;

void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;
    u8 count;

    if((player->currentMask == PLAYER_MASK_BUNNY) && (boolFreezer == 0)){  
        this->actorPtr = Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                            ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                            player->actor.world.pos.y,
                            player->actor.world.pos.z, 0, 0, 0, 1);
   
        duration = 72000;
        D_801614B0.a ^= 1;
        boolFreezer ^= 1;

    } else if((player->currentMask == PLAYER_MASK_NONE) && (boolFreezer == 1)){
        Actor_Kill(this->actorPtr);
        duration = 0;
        D_801614B0.a ^= 1;
        boolFreezer ^= 1;
    }

    Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, duration);
}