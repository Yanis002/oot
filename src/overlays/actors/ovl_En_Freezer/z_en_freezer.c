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

u8 boolFreezer = 0, count = 0;

void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;
    char s[5];

    if((player->currentMask == PLAYER_MASK_BUNNY) && (boolFreezer == 0)){  
        boolFreezer = 1;

        Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                                    ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                                    player->actor.world.pos.y,
                                    player->actor.world.pos.z, 0, 0, 0, 2);
    } else if((player->currentMask == PLAYER_MASK_NONE) && (boolFreezer == 1)){
        count = D_801614B0.a = boolFreezer = 0;
        Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, 0);
    }

    if((player->currentMask == PLAYER_MASK_BUNNY)){
        if(count < 35) count++;
        else {
            D_801614B0.a = 1;
            Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, 6000);
            boolFreezer = 1;
        }
    }

    Printf_Print(globalCtx, 0xFEFEFEFE, 0x010200, itoa(count, s));
}