/*
* File: z_en_trap_item.c
* Overlay: ovl_En_Trap_Item
* Description: Fake Items
*/

/* 
    PARAMETERS:
    - Item Type:    0000 0000 0000 1111 - 0x000F
    - Trap Type:    0000 0000 0111 0000 - 0x0070
    - Item Subtype: 0000 1111 1000 0000 - 0x0F80
    - Enemy Type:   1111 0000 0000 0000 - 0xF000

    Z-ROT PARAMETERS:
    - Switch Flag:  0000 0000 0011 1111 - 0x003F
    - Mode:         0000 0000 0100 0000 - 0x0040
    - Enemy Flag:   0001 1111 1000 0000 - 0x1F80
    - Enemy Count:  0110 0000 0000 0000 - 0x6000
    - Is Child:     1000 0000 0000 0000 - 0x8000

    EXAMPLE:
    - Parameters:   0000 0010 0010 0101 - 0x0225
        ((SUBTYPE_TUNIC_ZORA << 0x7) | (TRAP_TYPE_VOID << 0x4) | ITEM_TYPE_TUNIC)
    - Z-Rot Params: 0100 0000 0100 0001 - 0x4041
        ((4 << 0xD) | (MODE_SWITCH << 6) | 0x1)
*/

#include "z_en_trap_item.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5 | ACTOR_FLAG_9) // always run update and draw, hookshotable (brings)

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnTrapItem_ParamsCheck(EnTrapItem* this, u8 condition, u8 index, s16 value);
void EnTrapItem_SetupAction(EnTrapItem* this, EnTrapItemActionFunc actionFunc);
void EnTrapItem_WaitForNewObject(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_Main(EnTrapItem* this, GlobalContext* globalCtx);
u8 EnTrapItem_InitItemType(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_InitItemSubType(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_Trap(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_SpawnBomb(EnTrapItem* this, GlobalContext* globalCtx, Vec3f pos);
void EnTrapItem_SpawnEnemy(EnTrapItem* this, GlobalContext* globalCtx, Vec3f pos, s16 angle);
void EnTrapItem_SpawnAnimation(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawHeart(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawRupee(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawCollectible(EnTrapItem* this, GlobalContext* globalCtx);
void EnTrapItem_DrawEquipment(EnTrapItem* this, GlobalContext* globalCtx);

const ActorInit En_Trap_Item_InitVars = {
    ACTOR_EN_TRAP_ITEM,
    ACTORCAT_MISC,
    FLAGS,
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
        { 0x00000090, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON | BUMP_HOOKABLE,
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

static u8 isHooked = false;
static Color_RGBA8 sEffectPrimColor = { 255, 255, 127, 0 };
static Color_RGBA8 sEffectEnvColor = { 255, 255, 255, 0 };
static Vec3f sEffectVelocity = { 0.0f, 0.1f, 0.0f };
static Vec3f sEffectAccel = { 0.0f, 0.01f, 0.0f };

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    osSyncPrintf("En_Trap_Item: Init started!\n");

    this->itemType = this->actor.params & 0xF;
    this->trapType = (this->actor.params >> 0x4) & 0x7;
    this->itemSubType = (this->actor.params >> 0x7) & 0x1F;
    this->enemyType = (this->actor.params >> 0xC) & 0xF;
    this->switchFlag = this->actor.home.rot.z & 0x3F;
    this->mode = (this->actor.home.rot.z >> 6) & 0x1;
    this->enemySwitchFlag = (this->actor.home.rot.z >> 0x7) & 0x3F;
    this->enemyCount = (this->actor.home.rot.z >> 0xD) & 0x3;
    this->isNotFreestanding = (this->actor.home.rot.z >> 0xF) & 0x1;
    this->actor.home.rot.z = this->actor.world.rot.z = this->actor.shape.rot.z = 0;

    osSyncPrintf("Checking parameters...\n");

    EnTrapItem_ParamsCheck(this, (this->itemType >= ITEM_TYPE_MAX), 1, this->itemType);
    EnTrapItem_ParamsCheck(this, (this->trapType >= TRAP_TYPE_MAX), 2, this->trapType);
    EnTrapItem_ParamsCheck(this, (this->itemSubType >= SUBTYPE_MAX), 3, this->itemSubType);
    EnTrapItem_ParamsCheck(this, ((this->enemyType >= ENEMY_TYPE_MAX) &&
        (this->enemyType >= ENEMY_TYPE_MAX)), 4, this->enemyType);
    EnTrapItem_ParamsCheck(this, (this->switchFlag > 0x3F), 5, this->switchFlag);
    EnTrapItem_ParamsCheck(this, (this->mode >= MODE_MAX), 6, this->mode);
    EnTrapItem_ParamsCheck(this, (this->enemySwitchFlag > 0x3F), 7, this->enemySwitchFlag);
    EnTrapItem_ParamsCheck(this, (this->isNotFreestanding > 0x1), 8, this->isNotFreestanding);

    osSyncPrintf("Raw Parameters: %X\nItem Type: %X\nTrap Type: %X\nItem Subtype: %X\nEnemy Type: %X\n",
                this->actor.params, this->itemType, this->trapType, this->itemSubType, this->enemyType);
    osSyncPrintf("Switch Flag: %X\nMode: %X\nEnemy Flag: %X\nEnemy Count: %X\nIs Child: %X\n",
                this->switchFlag, this->mode, this->enemySwitchFlag, this->enemyCount, this->isNotFreestanding);

    osSyncPrintf("Checking switch flag state...\n");

    if (Flags_GetSwitch(globalCtx, this->switchFlag) && (this->mode == MODE_SWITCH)) {
        osSyncPrintf("Flag set!\n");
        Actor_Kill(&this->actor);
    }

    osSyncPrintf("Let's continue...\n");

    this->killTimer = 41;
    this->actor.room = -1;
    this->shadowScale = 6.0f;
    this->actor.minVelocityY = -12.0f;
    this->scale = this->texIndex = this->bankIndex = 0;
    this->yOffset = this->actor.speedXZ = this->actor.velocity.y = this->actor.gravity = 0.0f;

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
        EnTrapItem_SetupAction(this, EnTrapItem_SpawnAnimation);
        this->actor.draw = EnTrapItem_Draw;
    }

    if (this->trapType == TRAP_TYPE_ENEMY) {
        Actor_ChangeCategory(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_ENEMY);
    }

    osSyncPrintf("En_Trap_Item: Init completed!\n");
}

void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    // handles scaling
    if (this->actor.scale.x < this->scale) {
        Math_SmoothStepToF(&this->actor.scale.x, this->scale, 0.1f, this->scale * 0.1f, 0.0f);
        this->actor.scale.z = this->actor.scale.x;
        this->actor.scale.y = this->actor.scale.x;
    }
    
    if ((this->itemSubType == SUBTYPE_HEART_CONTAINER)) {
        if (this->actor.scale.x < 0.4f) {
            Math_ApproachF(&this->actor.scale.x, 0.4f, 0.1f, 0.01f);
            this->actor.scale.y = this->actor.scale.z = this->actor.scale.x;
        }
    }

    // handles the gravity update
    if (!(this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH))) {
        Actor_MoveForward(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 10.0f, 15.0f, 15.0f,
                                    UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_2 | UPDBGCHECKINFO_FLAG_3 |
                                        UPDBGCHECKINFO_FLAG_4);
    }
    
    if (this->actionFunc != NULL) {
        this->actionFunc(this, globalCtx);
    }

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;

    switch (this->itemType) {
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

void EnTrapItem_ParamsCheck(EnTrapItem* this, u8 condition, u8 index, s16 value) {
    if (condition) {
        osSyncPrintf("ERROR: Something's wrong with check n°%d. Value: 0x%X\n", index, value);
        Actor_Kill(&this->actor);
    }
}

void EnTrapItem_SetupAction(EnTrapItem* this, EnTrapItemActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnTrapItem_WaitForNewObject(EnTrapItem* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        Actor_SetObjectDependency(globalCtx, &this->actor);
        EnTrapItem_SetupAction(this, EnTrapItem_SpawnAnimation);
        this->actor.draw = EnTrapItem_Draw;
    }
}

void EnTrapItem_Main(EnTrapItem* this, GlobalContext* globalCtx) {
    Vec3f effectPos;

    EnTrapItem_Trap(this, globalCtx);

    // if hooked
    if (CHECK_FLAG_ALL(this->actor.flags, ACTOR_FLAG_13)) {
        isHooked = true;
    }

    if (isHooked) {
        this->actor.gravity = -0.9f;
        this->actor.bgCheckFlags &= ~(BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH);
    }

    if ((this->actor.draw == NULL) && (this->killTimer < 41)) {
        if (this->killTimer > 0) {
            this->killTimer--;
        } else {
            osSyncPrintf("En_Trap_Item: My job here is done\n");
            Actor_Kill(&this->actor);
        }
    }
}

u8 EnTrapItem_InitItemType(EnTrapItem* this, GlobalContext* globalCtx){
    switch (this->itemType) {
        case ITEM_TYPE_RUPEE:
            this->yOffset = 750.0f;
            this->scale = 0.015f;
            Actor_SetScale(&this->actor, 0.015f);
            break;
        case ITEM_TYPE_BOMBS:
        case ITEM_TYPE_NUTS:
        case ITEM_TYPE_STICK:
        case ITEM_TYPE_SEEDS:
            this->yOffset = 320.0f;
            this->scale = 0.03f;
            Actor_SetScale(&this->actor, 0.03f);
            break;
        case ITEM_TYPE_SMALL_KEY:
            this->yOffset = 350.0f;
            this->scale = 0.03f;
            Actor_SetScale(&this->actor, 0.03f);
            break;
        default:
            return true;
    }

    return false;
}

void EnTrapItem_InitItemSubType(EnTrapItem* this, GlobalContext* globalCtx){
    switch (this->itemSubType) {
        case SUBTYPE_MAGIC_LARGE:
            this->yOffset = 320.0f;
            this->scale = (0.045 - 1e-10);
            Actor_SetScale(&this->actor, (0.045 - 1e-10));
            break;
        case SUBTYPE_MAGIC_SMALL:
            this->yOffset = 320.0f;
            this->scale = 0.03f;
            Actor_SetScale(&this->actor, 0.03f);
            break;
        case SUBTYPE_SHIELD_DEKU:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_SHIELD_1);
            this->yOffset = 0.0f;
            this->scale = 0.5f;
            Actor_SetScale(&this->actor, 0.5f);
            this->shadowScale = 0.6f;
            this->actor.world.rot.x = 0x4000;
            break;
        case SUBTYPE_SHIELD_HYLIAN:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_SHIELD_2);
            this->yOffset = 0.0f;
            this->scale = 0.5f;
            Actor_SetScale(&this->actor, 0.5f);
            this->shadowScale = 0.6f;
            this->actor.world.rot.x = 0x4000;
            break;
        case SUBTYPE_TUNIC_ZORA:
        case SUBTYPE_TUNIC_GORON:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_CLOTHES);
            this->yOffset = 0.0f;
            this->scale = 0.5f;
            Actor_SetScale(&this->actor, 0.5f);
            this->shadowScale = 0.6f;
            this->actor.world.rot.x = 0x4000;
            break;
        case SUBTYPE_HEART_RECOVERY:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_HEART);
            this->shadowScale = 0.0f;
            this->yOffset = 430.0f;
            this->scale = 0.02f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case SUBTYPE_HEART_PIECE:
            this->shadowScale = 0.0f;
            this->yOffset = 650.0f;
            this->scale = 0.02f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case SUBTYPE_HEART_CONTAINER:
            this->bankIndex = Object_GetIndex(&globalCtx->objectCtx, OBJECT_GI_HEARTS);
            this->shadowScale = 0.0f;
            break;
        case SUBTYPE_ARROW_SINGLE:
            this->yOffset = 400.0f;
            this->scale = 0.02f;
            Actor_SetScale(&this->actor, 0.02f);
            break;
        case SUBTYPE_ARROW_SMALL:
        case SUBTYPE_ARROW_MEDIUM:
        case SUBTYPE_ARROW_LARGE:
            this->yOffset = 250.0f;
            this->scale = 0.035f;
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
    Vec3f pos;
    s16 angle;
    s8 i;

    if (((this->actor.xzDistToPlayer <= 25.0f) &&
        (this->actor.yDistToPlayer >= -50.0f) && (this->actor.yDistToPlayer <= 50.0f)) && (this->killTimer == 41)) {
        switch(this->trapType) {
            case TRAP_TYPE_ICE:
                globalCtx->playerTakeDamage(globalCtx, player, 3, 0.0f, 0.0f, 0, 20);
                break;
            case TRAP_TYPE_EXPLOSION:
                EnTrapItem_SpawnBomb(this, globalCtx, this->actor.world.pos);
                break;
            case TRAP_TYPE_VOID:
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
            case TRAP_TYPE_CUCCO:
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_NIW, this->actor.world.pos.x,
                    this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0xFFFF);
                EnTrapItem_SpawnBomb(this, globalCtx, this->actor.world.pos);
                break;
            case TRAP_TYPE_ENEMY:
                if ((this->enemyCount > 0) && (this->enemyCount <= 3)) {
                    angle = (Rand_ZeroOne() - 0.5f) * 6.28f;
                    pos.y = this->actor.floorHeight;
                    for (i = 1; i <= this->enemyCount; i++) {
                        pos.x = (Math_SinF(angle) * 110.0f) + this->actor.world.pos.x;
                        pos.z = (Math_CosF(angle) * 110.0f) + this->actor.world.pos.z;

                        EnTrapItem_SpawnEnemy(this, globalCtx, pos, this->actor.yawTowardsPlayer);
                        EnTrapItem_SpawnBomb(this, globalCtx, player->actor.world.pos);

                        angle += 6.28f / this->enemyCount;
                    }
                } else {
                    EnTrapItem_SpawnEnemy(this, globalCtx, this->actor.world.pos, this->actor.yawTowardsPlayer);
                }
                break;
            default:
                break;
        }
        if (this->mode == MODE_SWITCH) {
            Flags_SetSwitch(globalCtx, this->switchFlag);
            this->mode = MODE_DEFAULT;
        }
        this->actor.draw = NULL;
        this->killTimer = 40;
    }
}

void EnTrapItem_SpawnBomb(EnTrapItem* this, GlobalContext* globalCtx, Vec3f pos) {
    EnBom* bomb = NULL;

    bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, pos.x,
                    pos.y, pos.z, 0, 0, 0, BOMB_BODY);
    if (bomb != NULL) {
        bomb->timer = 0;
    }
    globalCtx->damagePlayer(globalCtx, -0x8);
    func_8002F71C(globalCtx, &this->actor, 2.0f, this->actor.yawTowardsPlayer, 10.0f);

    osSyncPrintf("En_Trap_Item: Le Bomb has arrived\n");
}

void EnTrapItem_SpawnEnemy(EnTrapItem* this, GlobalContext* globalCtx, Vec3f pos, s16 angle) {
    s16 params = 0;
    u8 randomBool = (Rand_ZeroOne() <= 0.5f);
    s16 enemyActorIDs[] = {
        ACTOR_EN_BROB, ACTOR_EN_DODONGO, ACTOR_EN_FZ, ACTOR_EN_IK,      ACTOR_EN_PEEHAT,  
        ACTOR_EN_RD,   ACTOR_EN_TEST,    ACTOR_EN_ZF, ACTOR_EN_WALLMAS, ACTOR_EN_RR,
    };

    switch (this->enemyType) {
        case ENEMY_TYPE_MUSCLE:
            params = ((!randomBool << 12) | (((Rand_ZeroOne() <= 0.5f) ? 0x14 : 0xFF) & 0x00FF));
            break;
        case ENEMY_TYPE_DODONGO:
        case ENEMY_TYPE_PEAHAT:
        case ENEMY_TYPE_LIKELIKE:
            params = 0xFFFF;
            break;
        case ENEMY_TYPE_FREEZARD:
            params = randomBool ? 0x0 : 0xFFFF;
            break;
        case ENEMY_TYPE_KNUCKLE:
            params = (randomBool ? 0x2 : 0x3) | ((this->enemySwitchFlag << 0x8) & 0xFF00);
            EnTrapItem_SpawnBomb(this, globalCtx, pos);
            break;
        case ENEMY_TYPE_REDEAD:
            params = ((randomBool ? 0x00 : 0x80) | ((((this->enemySwitchFlag) << 8) & 0x7F00) |
                        (!(Rand_ZeroOne() <= 0.5f) << 15) | (0xFE & 0x00FF)));
            break;
        case ENEMY_TYPE_STALFOS:
            params = randomBool ? 0x0 : 0x4;
            break;
        case ENEMY_TYPE_LIZALFOS:
            params = ((randomBool ? 0x80 : 0xFE) | (((0x0 << 8) & 0xFF00)));
            break;
        case ENEMY_TYPE_WALLMASTER:
            // params = 0 by default
            break;
        default:
            break;
    }

    Actor_Spawn(&globalCtx->actorCtx, globalCtx, enemyActorIDs[this->enemyType],
                pos.x, pos.y, pos.z, 0, angle, 0, params);

    osSyncPrintf("En_Trap_Item: Enemy is here! Watch out!\n");
}

void EnTrapItem_SpawnAnimation(EnTrapItem* this, GlobalContext* globalCtx) {
    Vec3f effectPos;

    if (!this->isNotFreestanding) {
        EnTrapItem_SetupAction(this, EnTrapItem_Main);
        return;
    }

    // doing the same rotation things item00 does
    switch (this->itemSubType) {
        case SUBTYPE_HEART_RECOVERY:
            if (this->actor.velocity.y < 0.0f) {
                this->actor.speedXZ = 0.0f;
                this->actor.gravity = -0.4f;
                if (this->actor.velocity.y < -1.5f) {
                    this->actor.velocity.y = -1.5f;
                }
                this->actor.home.rot.z += (s16)((this->actor.velocity.y + 3.0f) * 1000.0f);
                this->actor.world.pos.x +=
                    Math_CosS(this->actor.yawTowardsPlayer) * (-3.0f * Math_CosS(this->actor.home.rot.z));
                this->actor.world.pos.z +=
                    Math_SinS(this->actor.yawTowardsPlayer) * (-3.0f * Math_CosS(this->actor.home.rot.z));
            }
            break;
        case SUBTYPE_RUPEE_GREEN:
        case SUBTYPE_RUPEE_BLUE:
        case SUBTYPE_RUPEE_RED:
        case SUBTYPE_RUPEE_PURPLE:
        case SUBTYPE_RUPEE_ORANGE:
            this->actor.shape.rot.y += 960;
            break;
        case SUBTYPE_SHIELD_DEKU:
        case SUBTYPE_SHIELD_HYLIAN:
        case SUBTYPE_TUNIC_ZORA:
        case SUBTYPE_TUNIC_GORON:
            this->actor.world.rot.x -= 700;
            this->actor.shape.rot.y += 400;
            this->actor.shape.rot.x = this->actor.world.rot.x - 0x4000;
            break;
        default:
            break;
    }

    if (this->actor.velocity.y <= 2.0f) {
        if ((this->actor.shape.rot.z + 0x2710) < 0xFFFF) {
            this->actor.shape.rot.z += 0x2710;
        } else {
            this->actor.shape.rot.z = 0;
        }
    }

    if (this->actor.velocity.y <= -2.5f) {
        this->actor.shape.rot.z = 0;
        this->isNotFreestanding = false;
    }

    if (!(globalCtx->gameplayFrames & 1)) {
            effectPos.x = this->actor.world.pos.x + (Rand_ZeroOne() - 0.5f) * 10.0f;
            effectPos.y = this->actor.world.pos.y + (Rand_ZeroOne() - 0.5f) * 10.0f;
            effectPos.z = this->actor.world.pos.z + (Rand_ZeroOne() - 0.5f) * 10.0f;
            EffectSsKiraKira_SpawnSmall(globalCtx, &effectPos, &sEffectVelocity, &sEffectAccel, &sEffectPrimColor,
                                        &sEffectEnvColor);
    }

    if(this->actor.bgCheckFlags & (BGCHECKFLAG_GROUND | BGCHECKFLAG_GROUND_TOUCH)) {
        this->actor.shape.rot.z = 0;
        this->actor.velocity.y = this->actor.speedXZ = 0.0f;
    }
}

void EnTrapItem_DrawHeart(EnTrapItem* this, GlobalContext* globalCtx) {
    // spin
    this->actor.shape.rot.y += 960;

    // displays the heart
    switch (this->itemSubType) {
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

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(sRupeeTex[this->itemSubType - SUBTYPE_RUPEE_GREEN]));

    gSPDisplayList(POLY_OPA_DISP++, gRupeeDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}

void EnTrapItem_DrawCollectible(EnTrapItem* this, GlobalContext* globalCtx) {
    // both magic displays corrupted texture

    if (this->itemType >= ITEM_TYPE_SMALL_KEY) {
        this->texIndex = this->itemType - ITEM_TYPE_SMALL_KEY;
    } else {
        switch(this->itemSubType) {
            case SUBTYPE_MAGIC_LARGE:
            case SUBTYPE_MAGIC_SMALL:
                this->texIndex = this->itemSubType + 6;
                break;
            case SUBTYPE_ARROW_SMALL:
            case SUBTYPE_ARROW_MEDIUM:
            case SUBTYPE_ARROW_LARGE:
                this->texIndex = this->itemSubType - 2;
                break;
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

    switch(this->itemSubType) {
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
