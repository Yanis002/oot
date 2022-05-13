/*
* File: z_en_trap_item.c
* Overlay: ovl_En_Trap_Item
* Description: Fake Items
*/

/* PARAMETERS:
    - Item Type:     0000 0000 0000 0111 - 0x003
    - Trap Type:     0000 0000 0011 1000 - 0x038
    - Rupee Subtype: 0000 0001 1100 0000 - 0x1C0
    - Example:       0000 0000 1001 0001 - 0x091
*/

#include "z_en_trap_item.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTrapItem_DrawHeartPiece(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_DrawRupee(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Trap_Item_InitVars = {
    ACTOR_EN_TRAP_ITEM,
    ACTORCAT_ITEMACTION,
    0x00000030, // always run update and draw
    OBJECT_GAMEPLAY_KEEP,
    sizeof(EnTrapItem),
    (ActorFunc)EnTrapItem_Init,
    (ActorFunc)EnTrapItem_Destroy,
    (ActorFunc)EnTrapItem_Update,
    (ActorFunc)EnTrapItem_Draw,
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
    gRupeeGreenTex, gRupeeBlueTex, gRupeeRedTex, gRupeePinkTex, gRupeeOrangeTex,
};

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;
    f32 yOffset = 0.0f;
    f32 shadowScale = 6.0f;

    osSyncPrintf("En_Trap_Item: Init started!\n");
    osSyncPrintf("Item Type: %X\nTrap Type: %X\nRupee Type: %X\n",
                    GET_ITEM_TYPE(this->actor.params),
                    GET_TRAP_TYPE(this->actor.params),
                    GET_RUPEE_TYPE(this->actor.params));

    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = -12.0f;

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    switch (GET_ITEM_TYPE(this->actor.params)) {
        case ITEM_TYPE_HEART_PIECE:
            yOffset = 650.0f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case ITEM_TYPE_RUPEE:
            Actor_SetScale(&this->actor, 0.015f);
            yOffset = 750.0f;
            break;
        default:
            break;
    }

    ActorShape_Init(&this->actor.shape, yOffset, ActorShadow_DrawCircle, shadowScale);
    this->actor.shape.shadowAlpha = 180;
    this->actor.focus.pos = this->actor.world.pos;

    osSyncPrintf("En_Trap_Item: Init completed!\nExecuting update routine...\n");
}

void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;
    Player* player = GET_PLAYER(globalCtx);
    EnBom* bomb = NULL;
    u8 updateBgBool = false, i;

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

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    switch (GET_ITEM_TYPE(this->actor.params)) {
        case ITEM_TYPE_HEART_PIECE:
            EnTrapItem_DrawHeartPiece(thisx, globalCtx);
            break;
        case ITEM_TYPE_RUPEE:
            EnTrapItem_DrawRupee(thisx, globalCtx);
            break;
        default:
            break;
    }
}

void EnTrapItem_DrawHeartPiece(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    // spin
    this->actor.shape.rot.y += 960;
    this->actor.shape.yOffset = Math_SinS(this->actor.shape.rot.y) * 150.0f + 850.0f;

    // displays the heart piece
    OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

    func_80093D84(globalCtx->state.gfxCtx);
    func_8002ED80(&this->actor, globalCtx, 0);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD);
    gSPDisplayList(POLY_XLU_DISP++, gHeartPieceInteriorDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}

void EnTrapItem_DrawRupee(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    // spin
    this->actor.shape.rot.y += 960;

    // displays the rupee
    OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

    func_80093D18(globalCtx->state.gfxCtx);
    func_8002EBCC(&this->actor, globalCtx, 0);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__),
              G_MTX_MODELVIEW | G_MTX_LOAD);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sRupeeTex[GET_RUPEE_TYPE(this->actor.params)]));

    gSPDisplayList(POLY_OPA_DISP++, gRupeeDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}
