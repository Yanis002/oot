/*
* File: z_en_freezer.c
* Overlay: ovl_En_Freezer
* Description: Time stop (literally)
*/

/*
    TO DO:
        fix NL still need magic to use (but don't actually use magic)
        fix can't use items after using NL
        allow NL to be used underwater
        make timers freezing (might be too broken)
        make everything back to normal is link don't move for 15s
        if possible, make link & en_freezer not being affected by color change
        actor number restriction?
    
    WIP:
        fix bow and slingshot
            bug: elemental arrows half working
    DONE:
        make hookshot, ocarina, DF, FW, magic arrows not being affected by the freeze
        fix bombs not drawing (Pog)
        make time freeze and skybox pausing
        fix bugs and fishes unfreezing the actors
*/

#include "z_en_freezer.h"
#include "../ovl_En_Arrow/z_en_arrow.h"

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
    this->counter = this->counter2 = this->isEffectSpawned = this->dayTime = this->boolTimeSky = 0;
    this->skyRot.x = this->skyRot.y = this->skyRot.z = 0;
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

    if(this->counter < 35) this->counter++;
    else if(player->isFreezerSpawned == 1) EnFreezer_Freeze(globalCtx, this, 35);
    else Actor_Kill(&this->actor);
}

void EnFreezer_Freeze(GlobalContext* globalCtx, En_Freezer* this, u16 duration){
    Actor *wlActor, *blActor;
    Player* player = PLAYER;
    u8 i;

    //process actors
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

                //add a case to skip an actor if needed
                case ACTOR_EN_ARROW:
                    break;

                default:
                    wlActor->freezeTimer = duration;
                    break;
            } 
            
            if(wlActor->id == ACTOR_EN_ARROW){
                switch(wlActor->params){
                        case ARROW_SEED:
                        case ARROW_NORMAL_SILENT:
                        case ARROW_NORMAL_LIT: 
                        case ARROW_NORMAL_HORSE:
                        case ARROW_NORMAL:
                        case ARROW_FIRE:
                        case ARROW_ICE:
                        case ARROW_LIGHT:
                            if(player->isArrowShot) wlActor->freezeTimer = duration;
                            else if(this->counter2 < 7){
                                this->counter2++;
                                wlActor->freezeTimer = 0;
                            } else player->isArrowShot = 0;
                            break;

                        case ARROW_CS_NUT:
                        case ARROW_NUT:
                        default:
                            wlActor->freezeTimer = duration;
                            break;
                    }
            }
            
            wlActor = wlActor->next;
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

    //process time of day and skybox rotation
    if(this->boolTimeSky == 0){
        this->dayTime = gSaveContext.dayTime;
        this->skyRot = globalCtx->skyboxCtx.rot;
        this->boolTimeSky = 1;
    }

    gSaveContext.dayTime = this->dayTime;
    globalCtx->skyboxCtx.rot = this->skyRot;
}
