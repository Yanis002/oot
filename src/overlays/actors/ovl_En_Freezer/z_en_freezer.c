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

void En_Freeze_Freeze(GlobalContext *globalCtx, u16 duration);

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

static u8 boolFreezer = 0, boolFreezer2 = 0, counter = 0;

void En_Freezer_Init(Actor* thisx, GlobalContext* globalCtx) {
    osSyncPrintf("Hello Jack, Dragorn, Tharo and Fig!");
}

void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    if((player->currentMask == PLAYER_MASK_BUNNY)){
        if((boolFreezer == 0))
        {
            boolFreezer = 1; counter = 0;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                        ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                        player->actor.world.pos.y,
                        player->actor.world.pos.z, 0, 0, 0, 2);
        }
        En_Freeze_Freeze(globalCtx, 6000);
    } 
   
    else if((player->currentMask == PLAYER_MASK_NONE)){
        if((boolFreezer == 1))
        {
            boolFreezer = boolFreezer2 = counter = 0;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                        ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                        player->actor.world.pos.y,
                        player->actor.world.pos.z, 0, 0, 0, 2);
        }
        En_Freeze_Freeze(globalCtx, 0);
    }
}

void En_Freeze_Freeze(GlobalContext *globalCtx, u16 duration){
    if(counter < 35) counter++;
    else if(boolFreezer2 == 0){
        boolFreezer2 ^= 1;
        Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, duration);
    } 
}