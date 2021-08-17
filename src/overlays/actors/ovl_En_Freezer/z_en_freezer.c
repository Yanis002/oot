/*
* File: z_en_freezer.c
* Overlay: ovl_En_Freezer
* Description: Time stop (literally)
*/

/*
    TO DO: 
        fix freezing appearing before the effect ends (not a bug?)
        fix bow and slingshot
        allow NL to be used underwater
        make timers freezing
        make everything back to normal is link don't move for 15s
    
    WIP:
        make time freeze and skybox pausing
            DONE: time freeze

    DONE:
        make hookshot, ocarina, DF, FW, magic arrows not being affected by the freeze
        fix bombs not drawing (Pog)
*/

#include "z_en_freezer.h"

#define THIS ((En_Freezer*)thisx)

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFreezer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFreezer_Update(Actor* thisx, GlobalContext* globalCtx);

void EnFreezer_Freeze(GlobalContext* globalCtx, En_Freezer* this, u16 duration);

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
static u8 actorCatWhitelist[] = 
    {         
        ACTORCAT_ENEMY,         
        ACTORCAT_BOSS,         
        ACTORCAT_NPC,        
        ACTORCAT_ITEMACTION,         
        ACTORCAT_EXPLOSIVE,
        ACTORCAT_MISC
    };

static u8 actorCatBlacklist[] =
    {
        ACTORCAT_PROP,
        ACTORCAT_BG
    };

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    player->isFreezerSpawned = !player->isFreezerSpawned;
    player->itemActionParam = PLAYER_AP_NONE;
    this->counter = this->isEffectSpawned = this->dayTime = 0;
}

void EnFreezer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnFreezer_Update(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    if(!this->isEffectSpawned){
        this->isEffectSpawned = 1;
        this->dayTime = gSaveContext.dayTime;
        Actor_Spawn(&globalCtx->actorCtx, globalCtx,
                    ACTOR_OCEFF_WIPE, player->actor.world.pos.x,
                    player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 2);
    }

    if(player->isFreezerSpawned == 1){
        if(this->counter < 35){
            this->counter++;
        } else {
            EnFreezer_Freeze(globalCtx, this, 35); //process the actors
            gSaveContext.dayTime = this->dayTime; //process time of day
        }
    } 
    else Actor_Kill(&this->actor);
}

void EnFreezer_Freeze(GlobalContext* globalCtx, En_Freezer* this, u16 duration){
    Actor *wlActor, *blActor;
    u8 i;

    for (i = 0; i < ARRAY_COUNT(actorCatWhitelist); i++) {
        wlActor = globalCtx->actorCtx.actorLists[actorCatWhitelist[i]].head;

        while (wlActor != NULL) {
            switch(wlActor->id){
                //add a case to blacklist an actor
                case ACTOR_EN_FREEZER:
                case ACTOR_BG_SST_FLOOR:
                case ACTOR_BOSS_VA:
                case ACTOR_ITEM_B_HEART:
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
                    wlActor->freezeTimer = 0;
                    break;

                //add a case to run the update function until the actor is drawn
                case ACTOR_EN_BOM:
                    if(wlActor->isDrawn == 0) wlActor->update(wlActor, globalCtx);
                    else wlActor->freezeTimer = duration;    
                    break;

                default:
                    wlActor->freezeTimer = duration;
                    break;
            } wlActor = wlActor->next;
        }
    }

    for (i = 0; i < ARRAY_COUNT(actorCatBlacklist); i++){
        blActor = globalCtx->actorCtx.actorLists[actorCatBlacklist[i]].head;

        while (blActor != NULL) {
            switch(blActor->id){
                //add a case to freeze an actor from the blacklist
                case ACTOR_EN_NIW:
                case ACTOR_BG_SPOT00_HANEBASI:
                case ACTOR_EN_RIVER_SOUND:
                    blActor->freezeTimer = duration;
                    break;
            } blActor = blActor->next;
        }
    }
}
