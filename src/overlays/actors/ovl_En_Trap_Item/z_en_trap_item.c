/*
* File: z_en_trap_item.c
* Overlay: ovl_En_Trap_Item
* Description: Fake Items
*/

/* 
    PARAMETERS:
    - Item Type:      0000 0000 0000 1111 - 0x00F
    - Trap Type:      0000 0000 0111 0000 - 0x070
    - Item Subtype:   0000 1111 1000 0000 - 0xF80
    - Example:        0000 0000 1001 0001 - 0x091
*/

#include "z_en_trap_item.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTrapItem_SetupAction(EnTrapItem* this, EnTrapItemActionFunc actionFunc);
void EnTrapItem_WaitForNewObject(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_Main(EnTrapItem* this, GlobalContext* globalCtx);
u8 EnTrapItem_InitItemType(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_InitItemSubType(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_Trap(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawHeart(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawRupee(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawCollectible(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawEquipment(EnTrapItem* this, GlobalContext* globalCtx);

const ActorInit En_Trap_Item_InitVars = {
    ACTOR_EN_TRAP_ITEM,
    ACTORCAT_MISC,
    0x00000030, // always run update and draw
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnTrapItem),
    (ActorFunc)EnTrapItem_Init,
    (ActorFunc)EnTrapItem_Destroy,
    (ActorFunc)EnTrapItem_Update,
    NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000010, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 10, 30, 0, { 0, 0, 0 } },
};

static void* sRupeeTex[] = {
    gRupeeGreenTex, gRupeeBlueTex, gRupeeRedTex, gRupeeOrangeTex, gRupeePinkTex,
};

static void* sItemDropTex[] = {
    gDropKeySmallTex, gDropBombTex, gDropDekuNutTex, gDropDekuStickTex, gDropDekuSeedsTex,
    gDropRecoveryHeartTex, gDropMagicLargeTex, gDropMagicSmallTex, gDropArrows1Tex,
    gDropArrows2Tex, gDropArrows3Tex,
};

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    osSyncPrintf("En_Trap_Item: Init started!\n");
    osSyncPrintf("Raw Parameters: %X\nItem Type: %X\nTrap Type: %X\nItem Subtype: %X\n",
                    this->actor.params,
                    GET_ITEM_TYPE(this->actor.params),
                    GET_TRAP_TYPE(this->actor.params),
                    GET_ITEM_SUBTYPE(this->actor.params));

    this->yOffset = 0.0f;
    this->texIndex = 0;
    this->shadowScale = 6.0f;
    this->bankIndex = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = -12.0f;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    if (EnTrapItem_InitItemType(this, globalCtx)) {
        EnTrapItem_InitItemSubType(this, globalCtx);
    }

    ActorShape_Init(&this->actor.shape, this->yOffset, ActorShadow_DrawCircle, this->shadowScale);
    this->actor.shape.shadowAlpha = 180;
    this->actor.focus.pos = this->actor.world.pos;

    // if ``bankIndex`` is 0 at this point it means the user doesn't want to use specific object
    if (this->bankIndex) {
        EnTrapItem_SetupAction(this, EnTrapItem_WaitForNewObject);
    } else {
        EnTrapItem_SetupAction(this, EnTrapItem_Main);
        this->actor.draw = EnTrapItem_Draw;
    }

    osSyncPrintf("En_Trap_Item: Init completed!\n");
}

void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;
    
    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
    }
}

void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    switch (GET_ITEM_TYPE(this->actor.params)) {
        case ITEM_TYPE_HEART:
            EnTrapItem_DrawHeart(this, globalCtx);
            break;
        case ITEM_TYPE_RUPEE:
            EnTrapItem_DrawRupee(this, globalCtx);
            break;
        case ITEM_TYPE_SHIELD:
        case ITEM_TYPE_TUNIC:
            EnTrapItem_DrawEquipment(this, globalCtx);
            break;
        case ITEM_TYPE_MAGIC:
        case ITEM_TYPE_ARROW:
        case ITEM_TYPE_SMALL_KEY:
        case ITEM_TYPE_BOMBS:
        case ITEM_TYPE_NUTS:
        case ITEM_TYPE_STICK:
        case ITEM_TYPE_SEEDS:
            EnTrapItem_DrawCollectible(this, globalCtx);
            break;
        default:
            break;
    }
}

void EnTrapItem_SetupAction(EnTrapItem* this, EnTrapItemActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnTrapItem_WaitForNewObject(EnTrapItem* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(globalCtx, &this->actor);
        EnTrapItem_SetupAction(this, EnTrapItem_Main);
        this->actor.draw = EnTrapItem_Draw;
    }
}

void EnTrapItem_Main(EnTrapItem* this, GlobalContext* globalCtx) {
    u8 updateBgBool = false;

    if (GET_ITEM_SUBTYPE(this->actor.params) == SUBTYPE_HEART_CONTAINER) {
        Math_ApproachF(&this->actor.scale.x, 0.4f, 0.1f, 0.01f);
        this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
    }

    // handles the gravity update
    if (!(this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH))) {
        updateBgBool = true;
        Actor_MoveForward(&this->actor);
    }

    if (updateBgBool) {
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 15.0f, 15.0f,
                                    UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 |
                                        UPDBGCHECKINFO_FLAG_4);
    }

    EnTrapItem_Trap(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

u8 EnTrapItem_InitItemType(EnTrapItem* this, GlobalContext* globalCtx){
    switch (GET_ITEM_TYPE(this->actor.params)) {
        case ITEM_TYPE_RUPEE:
            this->yOffset = 750.0f;
            Actor_SetScale(&this->actor, 0.015f);
            break;
        case ITEM_TYPE_BOMBS:
        case ITEM_TYPE_NUTS:
        case ITEM_TYPE_STICK:
        case ITEM_TYPE_SEEDS:
            this->yOffset = 320.0f;
            Actor_SetScale(&this->actor, 0.03f);
            break;
        case ITEM_TYPE_SMALL_KEY:
            this->yOffset = 350.0f;
            Actor_SetScale(&this->actor, 0.03f);
            break;
        default:
            return true;
    }

    return false;
}

void EnTrapItem_InitItemSubType(EnTrapItem* this, GlobalContext* globalCtx){
    switch (GET_ITEM_SUBTYPE(this->actor.params)) {
        case SUBTYPE_MAGIC_LARGE:
            this->yOffset = 320.0f;
            Actor_SetScale(&this->actor, 0.045 - 1e-10);
            break;
        case SUBTYPE_MAGIC_SMALL:
            this->yOffset = 320.0f;
            Actor_SetScale(&this->actor, 0.03f);
            break;
        case SUBTYPE_SHIELD_DEKU:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_SHIELD_1);
            this->yOffset = 0.0f;
            Actor_SetScale(&this->actor, 0.5f);
            this->shadowScale = 0.6f;
            this->actor.world.rot.x = 0x4000;
            break;
        case SUBTYPE_SHIELD_HYLIAN:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_SHIELD_2);
            this->yOffset = 0.0f;
            Actor_SetScale(&this->actor, 0.5f);
            this->shadowScale = 0.6f;
            this->actor.world.rot.x = 0x4000;
            break;
        case SUBTYPE_TUNIC_ZORA:
        case SUBTYPE_TUNIC_GORON:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_CLOTHES);
            this->yOffset = 0.0f;
            Actor_SetScale(&this->actor, 0.5f);
            this->shadowScale = 0.6f;
            this->actor.world.rot.x = 0x4000;
            break;
        case SUBTYPE_HEART_RECOVERY:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_HEART);
            this->shadowScale = 0.0f;
            this->yOffset = 430.0f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case SUBTYPE_HEART_PIECE:
            this->shadowScale = 0.0f;
            this->yOffset = 650.0f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case SUBTYPE_HEART_CONTAINER:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_HEARTS);
            this->shadowScale = 0.0f;
            break;
        case SUBTYPE_ARROW_SINGLE:
            this->yOffset = 400.0f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case SUBTYPE_ARROW_SMALL:
        case SUBTYPE_ARROW_MEDIUM:
        case SUBTYPE_ARROW_LARGE:
            this->yOffset = 250.0f;
            Actor_SetScale(&this->actor, 0.035f);
            break;
        case SUBTYPE_NONE:
            osSyncPrintf("ERROR: Invalid item subtype!\n");
            Actor_Kill(&this->actor);
        default:
            break;
    }
}

void EnTrapItem_Trap(EnTrapItem* this, GlobalContext* globalCtx){
    Player* player = GET_PLAYER(globalCtx);
    EnBom* bomb = NULL;
    u8 i;

    if (((this->actor.xzDistToPlayer <= 25.0f) &&
        (this->actor.yDistToPlayer >= -50.0f) && (this->actor.yDistToPlayer <= 50.0f))) {
        switch(GET_TRAP_TYPE(this->actor.params)) {
            case TRAP_TYPE_ICE:
                globalCtx->playerTakeDamage(globalCtx, player, 3, 0.0f, 0.0f, 0, 20);
                break;
            case TRAP_TYPE_EXPLOSION:
                bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, BOMB_BODY);
                if (bomb != NULL) {
                    bomb->timer = 0;
                }
                globalCtx->damagePlayer(globalCtx, -0x8);
                func_8002F71C(globalCtx, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 0.0f);
                break;
            case TRAP_TYPE_CRUSH:
                Gameplay_TriggerRespawn(globalCtx);
                gSaveContext.respawnFlag = -2;
                Audio_QueueSeqCmd(SEQ_PLAYER_BGM_MAIN << 24 | NA_BGM_STOP);
                globalCtx->transitionType = TRANS_TYPE_FADE_BLACK;
                func_800788CC(NA_SE_OC_ABYSS);
                break;
            case TRAP_TYPE_FIRE:
                for (i = 0; i < PLAYER_BODYPART_MAX; i++) {
                    player->flameTimers[i] = Rand_S16Offset(0, 200);
                }
                if (!player->isBurning) {
                    player->isBurning = true;
                }
                globalCtx->playerTakeDamage(globalCtx, player, 1, 0.0f, 0.0f, 0, 0);
                break;
            case TRAP_TYPE_ELECTRICITY:
                globalCtx->playerTakeDamage(globalCtx, player, 4, 0.0f, 0.0f, 0, 20);
                break;
            default:
                break;
        }
        Actor_Kill(&this->actor);
    }
}

void EnTrapItem_DrawHeart(EnTrapItem* this, GlobalContext* globalCtx) {
    // spin
    this->actor.shape.rot.y += 960;

    // displays the heart
    switch (GET_ITEM_SUBTYPE(this->actor.params)) {
        case SUBTYPE_HEART_PIECE:
            this->actor.shape.yOffset = Math_SinS(this->actor.shape.rot.y) * 150.0f + 850.0f;

            OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

            func_80093D84(globalCtx->state.gfxCtx);
            func_8002ED80(&this->actor, globalCtx, 0);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__),
                    G_MTX_MODELVIEW | G_MTX_LOAD);
            gSPDisplayList(POLY_XLU_DISP++, gHeartPieceInteriorDL);

            CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
            break;
        case SUBTYPE_HEART_CONTAINER:
            this->actor.shape.yOffset = Math_SinS(this->actor.shape.rot.y) * 12.0f + 44.0f;
            GetItem_Draw(globalCtx, GID_HEART_CONTAINER);
            break;
        case SUBTYPE_HEART_RECOVERY:
            Matrix_Scale(16.0f, 16.0f, 16.0f, MTXMODE_APPLY);
            GetItem_Draw(globalCtx, GID_HEART);
        default:
            break;
    }
}

void EnTrapItem_DrawRupee(EnTrapItem* this, GlobalContext* globalCtx) {
    // spin
    this->actor.shape.rot.y += 960;

    // displays the rupee
    OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

    func_80093D18(globalCtx->state.gfxCtx);
    func_8002EBCC(&this->actor, globalCtx, 0);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sRupeeTex[GET_ITEM_SUBTYPE(this->actor.params) - SUBTYPE_RUPEE_GREEN]));

    gSPDisplayList(POLY_OPA_DISP++, gRupeeDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}

void EnTrapItem_DrawCollectible(EnTrapItem* this, GlobalContext* globalCtx) {
    // both magic displays corrupted texture

    if (GET_ITEM_TYPE(this->actor.params) >= ITEM_TYPE_SMALL_KEY) {
        this->texIndex = GET_ITEM_TYPE(this->actor.params) - ITEM_TYPE_SMALL_KEY;
    } else {
        this->texIndex = 5; 
        switch(GET_ITEM_SUBTYPE(this->actor.params)) {
            case SUBTYPE_MAGIC_LARGE:
            case SUBTYPE_MAGIC_SMALL:
                this->texIndex += GET_ITEM_SUBTYPE(this->actor.params) + 1;
            case SUBTYPE_ARROW_SMALL:
            case SUBTYPE_ARROW_MEDIUM:
            case SUBTYPE_ARROW_LARGE:
                this->texIndex = GET_ITEM_SUBTYPE(this->actor.params) - 2;
            default:
                break;
        }
    }

    OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

    POLY_OPA_DISP = Gameplay_SetFog(globalCtx, POLY_OPA_DISP);
    POLY_OPA_DISP = func_800946E4(POLY_OPA_DISP);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sItemDropTex[this->texIndex]));

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, gItemDropDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}

void EnTrapItem_DrawEquipment(EnTrapItem* this, GlobalContext* globalCtx) {
    this->actor.shape.yOffset = Math_CosS(this->actor.shape.rot.x) * 37.0f;
    this->actor.shape.yOffset = ABS(this->actor.shape.yOffset);
    this->actor.world.rot.x -= 700;
    this->actor.shape.rot.y += 400;
    this->actor.shape.rot.x = this->actor.world.rot.x - 0x4000;

    switch(GET_ITEM_SUBTYPE(this->actor.params)) {
        case SUBTYPE_SHIELD_DEKU:
            GetItem_Draw(globalCtx, GID_SHIELD_DEKU);
            break;
        case SUBTYPE_SHIELD_HYLIAN:
            GetItem_Draw(globalCtx, GID_SHIELD_HYLIAN);
            break;
        case SUBTYPE_TUNIC_GORON:
            GetItem_Draw(globalCtx, GID_TUNIC_GORON);
            break;
        case SUBTYPE_TUNIC_ZORA:
            GetItem_Draw(globalCtx, GID_TUNIC_ZORA);
            break;
    }
}
