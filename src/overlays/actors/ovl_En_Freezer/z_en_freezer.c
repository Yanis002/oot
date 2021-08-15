/*
* File: z_en_freezer.c
* Overlay: ovl_En_Freezer
* Description: Time stop (literally)
*/

/*
    TO DO:
        fix bombs not drawing
        fix freezing appearing before the effect ends
        fix bow and slingshot
        allow NL to be used underwater
        make timers freezing
        make everything back to normal is link don't move for 15s
        make time freeze and skybox pausing

    WIP:
        make hookshot, ocarina, DF, FW, magic arrows not being affected by the freeze
            (TODO: check and complete the blacklist in z_actor.c)
*/

#include "z_en_freezer.h"

#define THIS ((En_Freezer*)thisx)

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFreezer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFreezer_Update(Actor* thisx, GlobalContext* globalCtx);

void EnFreezer_Freeze(En_Freezer* this);
void EnFreezer_SpawnEffect(GlobalContext* globalCtx, En_Freezer* this, Player* player);

const ActorInit En_Freezer_InitVars = {
    ACTOR_EN_FREEZER,
    ACTORCAT_MISC,
    0x00000030, // always run update and draw
    OBJECT_GAMEPLAY_KEEP,
    sizeof(En_Freezer),
    (ActorFunc)EnFreezer_Init,
    (ActorFunc)EnFreezer_Destroy,
    (ActorFunc)EnFreezer_Update,
    NULL,
};

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    player->isFreezerSpawned = !player->isFreezerSpawned;

    player->itemActionParam = PLAYER_AP_NONE;
    this->counter = 0;
    this->isEffectSpawned = 0;
}

void EnFreezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnFreezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

   EnFreezer_SpawnEffect(globalCtx, this, player);
   EnFreezer_Freeze(this);
}

void EnFreezer_SpawnEffect(GlobalContext* globalCtx, En_Freezer* this, Player* player){
    if(!this->isEffectSpawned){
        this->isEffectSpawned = 1;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                    ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                    player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 2);
    }
}

void EnFreezer_Freeze(En_Freezer* this){
    if(this->counter < 35) this->counter++;
    else {
        Actor_Kill(&this->actor);
    }
}
