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
    En_Freezer* this = THIS;

    osSyncPrintf("Hello Jack, Dragorn, Tharo and Fig!");
}

void En_Freezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

u16 duration = 0;

void En_Freezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;
    char dst[200];
    s8 actionParam = player->itemActionParam;

    switch(actionParam){
        case PLAYER_AP_NAYRUS_LOVE:
            break;

        default:
            actionParam = PLAYER_AP_NONE;
            break;
    }

   //si nayru activé
   if(actionParam == PLAYER_AP_NAYRUS_LOVE){
       //prevents z_player from spawning infinite en_freezer
       player->isFreezerSpawned = 1;

       switch(boolFreezer){
            case 0:
                if(boolFreezer2 == 0){
                    boolFreezer2 = 1;
                    //afficher effet
                    this->actorPtr = Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                                        ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                                        player->actor.world.pos.y,
                                        player->actor.world.pos.z, 0, 0, 0, 2);
                }
                if(counter < 35) counter++;
                else {
                    duration = 35;
                    counter = boolFreezer2 = 0;
                    boolFreezer = 1;
                    player->itemActionParam = PLAYER_AP_NONE;
                }
                break;

            case 1:
                if(boolFreezer2 == 0){
                    boolFreezer2 = 1;
                    //afficher effet
                    this->actorPtr = Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                                        ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                                        player->actor.world.pos.y,
                                        player->actor.world.pos.z, 0, 0, 0, 2);
                }

                //attendre fin animation puis unfreeze les actors en continu
                if(counter < 35) counter++;
                else duration = 0;
                break;
        }

        En_Freeze_Freeze(globalCtx, duration);

        //si la durée est 0 on est forcément dans le cas "2e fois" donc on reset tout et on kill l'actor
        if(duration == 0){
            player->isFreezerSpawned = 0;
            player->itemActionParam = PLAYER_AP_NONE;
            //Actor_Kill(&this->actor);
        }

       /*
            si nayru activé la première fois:
                reset l'action parameter
                afficher effet
                freeze les actors à la fin de l'animation
                continuer a freeze jusqu'à la prochaine utilisation de nayru
            si nayru activé la 2e fois:
                reset l'action parameter
                afficher effet
                unfreeze les actors à la fin de l'animation
                reset isFreezerSpawned
                kill l'actor en_freezer
        */

    //    //si c'est la première fois
    //    if(boolFreezer == 0){
    //        if(boolFreezer2 == 0){
    //             boolFreezer2 = 1;
    //             //afficher effet
    //             this->actorPtr = Actor_Spawn(&globalCtx->actorCtx, globalCtx,
    //                                 ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
    //                                 player->actor.world.pos.y,
    //                                 player->actor.world.pos.z, 0, 0, 0, 2);
    //        }

    //         //attendre fin animation puis freeze les actors en continu
    //         if(counter < 35) En_Freeze_Freeze(globalCtx, 0);
    //         else {
    //             duration = 35;
    //             counter = boolFreezer2 = 0;
    //             boolFreezer = 1;
    //             player->itemActionParam = PLAYER_AP_NONE;
    //         }
    //    }

    //    //si c'est la 2e fois
    //    else if(boolFreezer == 1){
    //         if(boolFreezer2 == 0){
    //             boolFreezer2 = 1;
    //             //afficher effet
    //             this->actorPtr = Actor_Spawn(&globalCtx->actorCtx, globalCtx,
    //                                 ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
    //                                 player->actor.world.pos.y,
    //                                 player->actor.world.pos.z, 0, 0, 0, 2);
    //         }

    //         //attendre fin animation puis unfreeze les actors en continu
    //         if(counter < 35) En_Freeze_Freeze(globalCtx, 0);
    //         else duration = 0;
    //    }

   }   

    sprintf(dst, "duration: %d \n counter: %d \n boolFreezer: %d \n actionParam: %d \n boolFreezer2: %d", 
                  duration,       counter,       boolFreezer,       actionParam,       boolFreezer2);
    Printf_Print(globalCtx, 0xFEFEFEFE, 0x010500, dst);
}

void En_Freeze_Freeze(GlobalContext *globalCtx, u16 duration){
    if(counter < 35) counter++;
    else {
        Actor_FreezeAllActors(globalCtx, &globalCtx->actorCtx, duration);
    }
}