/*
* File: z_en_freezer.c
* Overlay: ovl_En_Freezer
* Description: Time stop (literally)
*/

/*
    TO DO:
        allow NL to be used underwater
        make water not moving during freeze
    
    WIP:

    DONE:
        make hookshot, ocarina, DF, FW, magic arrows not being affected by the freeze
        fix bombs not drawing
        make time freeze and skybox pausing
        fix bugs and fishes unfreezing the actors
        fix bow and slingshot
        fix NL still need magic to use (but don't actually use magic)
        fix can't use items after using NL
        make scrolling textures stop while frozen
*/

#include "z_en_freezer.h"
#include "../ovl_En_Arrow/z_en_arrow.h"

#define THIS ((En_Freezer*)thisx)

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFreezer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFreezer_Update(Actor* thisx, GlobalContext* globalCtx);

void EnFreezer_SetupFreeze(GlobalContext* globalCtx, En_Freezer* this);
void EnFreezer_Freeze(GlobalContext* globalCtx, En_Freezer* this, u16 duration);

const ActorInit En_Freezer_InitVars = {
    ACTOR_EN_FREEZER,
    ACTORCAT_ITEMACTION,
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

static u16 duration = 0;

void EnFreezer_Init(Actor* thisx, GlobalContext* globalCtx) {
    En_Freezer* this = THIS;
    Player* player = PLAYER;

    player->isFreezerSpawned = !player->isFreezerSpawned;
    this->counter = this->isEffectSpawned = this->dayTime = this->boolTimeSky = this->duration = 0;
    this->skyRot.x = this->skyRot.y = this->skyRot.z = 0.f;

    //set freeze duration
    if(!gSaveContext.magicAcquired) duration = 100;
    else if(!gSaveContext.doubleMagic) duration = 200;
    else duration = 300;
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
    else if(player->isFreezerSpawned && !this->isDurationReached) EnFreezer_SetupFreeze(globalCtx, this);
    else if(!player->isFreezerSpawned) Actor_Kill(&this->actor);

    if(D_801614B0.a){
        if(this->duration < duration) this->duration++;
        else if(!this->isDurationReached){
            this->isDurationReached = 1;
            player->isFreezerSpawned = this->isEffectSpawned = this->counter = 0;
            EnFreezer_SetupFreeze(globalCtx, this);
        }
    }
}

void EnFreezer_SetupFreeze(GlobalContext* globalCtx, En_Freezer* this){
    if(!this->isDurationReached) EnFreezer_Freeze(globalCtx, this, 36);
    else EnFreezer_Freeze(globalCtx, this, 35);
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
                case ACTOR_EN_SI:
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
                case ACTOR_BG_SPOT00_HANEBASI: //hyrule field
                case ACTOR_BG_SPOT01_FUSYA: //kakariko village
                case ACTOR_BG_SPOT03_TAKI: //zora's river
                case ACTOR_BG_SPOT07_TAKI: //zora's domain
                case ACTOR_BG_SPOT16_DOUGHNUT: //dmt
                case ACTOR_BG_SPOT17_FUNEN: //dmc
                case ACTOR_BG_SPOT18_BASKET: //goron city
                case ACTOR_BG_SPOT18_FUTA:
                case ACTOR_BG_YDAN_HASI: //deku tree, hasi to change
                case ACTOR_BG_YDAN_MARUTA:
                case ACTOR_BG_YDAN_SP:
                case ACTOR_BG_DDAN_JD: //dodongo's cavern
                case ACTOR_BG_BDAN_OBJECTS: //jabu-jabu's belly (watch out for water square)
                case ACTOR_BG_MENKURI_KAITEN: //forest temple (???) & gtg rotating platform
                case ACTOR_BG_MORI_ELEVATOR: //forest temple
                case ACTOR_BG_MORI_HASHIRA4:
                case ACTOR_BG_HIDAN_FIREWALL: //fire temple
                case ACTOR_BG_HIDAN_RSEKIZOU:
                case ACTOR_BG_HIDAN_SEKIZOU:
                case ACTOR_BG_HIDAN_SIMA:
                case ACTOR_BG_HIDAN_SYOKU:
                case ACTOR_BG_HIDAN_HAMSTEP:
                case ACTOR_BG_HIDAN_FWBIG:
                case ACTOR_BG_HIDAN_FSLIFT:
                case ACTOR_BG_MIZU_MOVEBG: //water temple
                case ACTOR_BG_MIZU_SHUTTER:
                case ACTOR_BG_HAKA_MEGANEBG: //shadow temple
                case ACTOR_BG_HAKA_TUBO:
                case ACTOR_BG_HAKA_TRAP:
                case ACTOR_BG_JYA_ZURERUKABE: //spirit temple
                case ACTOR_BG_JYA_1FLIFT:
                case ACTOR_MIR_RAY:
                case ACTOR_EN_NIW:
                case ACTOR_EN_RIVER_SOUND:
                case ACTOR_OBJ_SYOKUDAI:
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
