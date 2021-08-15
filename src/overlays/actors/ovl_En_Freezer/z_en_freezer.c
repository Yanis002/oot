/*
* File: z_en_freezer.c
* Overlay: ovl_En_Freezer
* Description: Time stop (literally)
*/

//TODO: prevent using c-buttons while time is stopped, make bombs draw,
//  limit the amount of spawnable actors during the time stop
//  prevent vismono to make link black and white

#include "z_en_freezer.h"

#define THIS ((En_Freezer*)thisx)

void En_Freezer_Init(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx);

void En_Freeze_Freeze(GlobalContext* globalCtx, En_Freezer* this, Player* player, u16 duration);
void En_Freezer_SpawnEffect(GlobalContext* globalCtx, En_Freezer* this, Player* player);

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
    En_Freezer* this = THIS;

    this->counter = 0;
    this->isEffectSpawned = 0;
    this->isCase1 = 0;
    this->duration = 0;
}

void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;
    s8 actionParam = player->itemActionParam;

    switch(actionParam){
        case PLAYER_AP_NAYRUS_LOVE:
            player->isFreezerSpawned = 1;
            player->itemActionParam = PLAYER_AP_NONE;

            switch(this->isCase1){
                case 0:
                    En_Freezer_SpawnEffect(globalCtx, this, player);
                    this->duration = 35;
                    this->isEffectSpawned = 0;
                    this->isCase1 = 1;
                    break;

                case 1:
                    En_Freezer_SpawnEffect(globalCtx, this, player);
                    this->counter = this->duration = 0;
                    break;
            }
            break;

        default:
            actionParam = PLAYER_AP_NONE;
            break;
    }

    En_Freeze_Freeze(globalCtx, this, player, this->duration);
}

void En_Freeze_Freeze(GlobalContext *globalCtx, En_Freezer* this, Player* player, u16 duration){
    if(this->counter < 35) this->counter++;
    else {
        Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, duration);

        if(!duration && this->isEffectSpawned){
            player->isFreezerSpawned = 0;
            Actor_Kill(&this->actor);
        }
    }
}

void En_Freezer_SpawnEffect(GlobalContext* globalCtx, En_Freezer* this, Player* player){
    if(!this->isEffectSpawned){
        this->isEffectSpawned = 1;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                    ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                    player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 2);
    }
}
