#include "z_en_freezer.h"

#define THIS ((En_Freezer*)thisx)

void En_Freezer_Init(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Process(GlobalContext* globalCtx);
void En_Freezer_Wait();

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
}

void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;
    Input* sControlInput;
    char s[2];
    u8 i;

    if((player->currentMask == PLAYER_MASK_BUNNY) && (D_801614B0.a == 0)){     
        Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                    ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                    player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 1);

        this->actor.freezeTimer = 100;
        Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, 72000);
        D_801614B0.a ^= 1;
    } else if((player->currentMask == PLAYER_MASK_NONE) && (D_801614B0.a == 1)){
        Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, 0);
        D_801614B0.a ^= 1;
    }
}

void En_Freezer_Process(GlobalContext* globalCtx){
   
}

void En_Freezer_Wait(){}