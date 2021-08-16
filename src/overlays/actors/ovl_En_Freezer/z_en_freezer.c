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

void EnFreezer_Freeze(GlobalContext* globalCtx, u16 duration);

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

//every actors in these categories will be frozen
static u8 categories[] = 
    {         
        ACTORCAT_ENEMY,         
        ACTORCAT_BOSS,         
        ACTORCAT_NPC,        
        ACTORCAT_ITEMACTION,         
        ACTORCAT_EXPLOSIVE    
    }; 

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    player->isFreezerSpawned = !player->isFreezerSpawned;
    player->itemActionParam = PLAYER_AP_NONE;
    this->counter = this->isEffectSpawned = 0;
}

void EnFreezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnFreezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    if(!this->isEffectSpawned){
        this->isEffectSpawned = 1;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                    ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                    player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 2);
    }

    if(player->isFreezerSpawned == 1){
        if(this->counter < 35) this->counter++;
        else EnFreezer_Freeze(globalCtx, 35);
    } else Actor_Kill(&this->actor);
}

void EnFreezer_Freeze(GlobalContext* globalCtx, u16 duration) {
    Actor* actor;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(categories); i++) {
        actor = globalCtx->actorCtx.actorLists[categories[i]].head;

        while (actor != NULL) {
            //preventing some actors to be frozen
            switch(actor->id){
                case ACTOR_EN_ELF:
                case ACTOR_OCEFF_SPOT:
                case ACTOR_OCEFF_WIPE:
                case ACTOR_OCEFF_WIPE2:
                case ACTOR_OCEFF_WIPE3:
                case ACTOR_OCEFF_WIPE4:
                case ACTOR_OCEFF_STORM:
                case ACTOR_END_TITLE:
                case ACTOR_EN_OKARINA_EFFECT:
                case ACTOR_ARROW_FIRE:
                case ACTOR_ARROW_ICE:
                case ACTOR_ARROW_LIGHT:
                case ACTOR_MAGIC_FIRE:
                case ACTOR_MAGIC_WIND:
                case ACTOR_ARMS_HOOK:
                    actor->freezeTimer = 0;
                    break;

                default:
                    actor->freezeTimer = duration;
                    break;
            }
            actor = actor->next;
        }
    }
}
