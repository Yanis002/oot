/*
 * File: z_en_ru1.c
 * Overlay: En_Ru1
 * Description: Ruto (child)
 */

#include "z_en_ru1.h"
#include "assets/objects/object_ru1/object_ru1.h"
#include "vt.h"

#define FLAGS (ACTOR_FLAG_0 | ACTOR_FLAG_4 | ACTOR_FLAG_26)

void EnRu1_Init(Actor* thisx, PlayState* play);
void EnRu1_Destroy(Actor* thisx, PlayState* play);
void EnRu1_Update(Actor* thisx, PlayState* play);
void EnRu1_Draw(Actor* thisx, PlayState* play);

void func_80AEC0B4(EnRu1* this, PlayState* play);
void func_80AEC100(EnRu1* this, PlayState* play);
void func_80AEC130(EnRu1* this, PlayState* play);
void func_80AEC17C(EnRu1* this, PlayState* play);
void func_80AEC1D4(EnRu1* this, PlayState* play);
void func_80AEC244(EnRu1* this, PlayState* play);
void func_80AEC2C0(EnRu1* this, PlayState* play);
void EnRu1_SetupFirstTimeMeetingCS(EnRu1* this, PlayState* play);
void func_80AECAB4(EnRu1* this, PlayState* play);
void func_80AECAD4(EnRu1* this, PlayState* play);
void func_80AECB18(EnRu1* this, PlayState* play);
void func_80AECB60(EnRu1* this, PlayState* play);
void func_80AECBB8(EnRu1* this, PlayState* play);
void func_80AECC1C(EnRu1* this, PlayState* play);
void func_80AECC84(EnRu1* this, PlayState* play);
void func_80AED304(EnRu1* this, PlayState* play);
void func_80AED324(EnRu1* this, PlayState* play);
void func_80AED344(EnRu1* this, PlayState* play);
void func_80AED374(EnRu1* this, PlayState* play);
void func_80AED3A4(EnRu1* this, PlayState* play);
void func_80AED3E0(EnRu1* this, PlayState* play);
void func_80AED414(EnRu1* this, PlayState* play);
void func_80AEF29C(EnRu1* this, PlayState* play);
void func_80AEF2AC(EnRu1* this, PlayState* play);
void func_80AEF2D0(EnRu1* this, PlayState* play);
void func_80AEF354(EnRu1* this, PlayState* play);
void func_80AEF3A8(EnRu1* this, PlayState* play);
void func_80AEEBD4(EnRu1* this, PlayState* play);
void func_80AEEC5C(EnRu1* this, PlayState* play);
void func_80AEECF0(EnRu1* this, PlayState* play);
void func_80AEED58(EnRu1* this, PlayState* play);
void EnRu1_SetupSitAndSquirm(EnRu1* this, PlayState* play);
void EnRu1_SetupSitIdle(EnRu1* this, PlayState* play);
void func_80AEEE9C(EnRu1* this, PlayState* play);
void func_80AEEF08(EnRu1* this, PlayState* play);
void func_80AEEF5C(EnRu1* this, PlayState* play);
void func_80AEF9D8(EnRu1* this, PlayState* play);
void func_80AEFA2C(EnRu1* this, PlayState* play);
void func_80AEFAAC(EnRu1* this, PlayState* play);
void func_80AEFB04(EnRu1* this, PlayState* play);
void func_80AEFB68(EnRu1* this, PlayState* play);
void func_80AEFCE8(EnRu1* this, PlayState* play);
void EnRu1_SetupAbductionCS(EnRu1* this, PlayState* play);
void func_80AEFC24(EnRu1* this, PlayState* play);
void func_80AEFECC(EnRu1* this, PlayState* play);
void func_80AEFF40(EnRu1* this, PlayState* play);

void func_80AF0278(EnRu1* this, PlayState* play, s32 limbIndex, Vec3s* rot);

void EnRu1_DrawNothing(EnRu1* this, PlayState* play);
void EnRu1_DrawOpa(EnRu1* this, PlayState* play);
void EnRu1_DrawXlu(EnRu1* this, PlayState* play);

static ColliderCylinderInitType1 sCylinderInit1 = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    { 0x00, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x00, 0x00, 0x01 },
    { 25, 80, 0, { 0 } },
};

static ColliderCylinderInitType1 sCylinderInit2 = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        COLSHAPE_CYLINDER,
    },
    { 0x00, { 0x00000101, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, 0x01, 0x00, 0x01 },
    { 20, 30, 0, { 0 } },
};

static void* sEyeTextures[] = {
    gRutoChildEyeOpenTex,     gRutoChildEyeHalfTex,  gRutoChildEyeClosedTex,
    gRutoChildEyeRollLeftTex, gRutoChildEyeHalf2Tex, gRutoChildEyeHalfWithBlushTex,
};

static void* sMouthTextures[] = {
    gRutoChildMouthClosedTex,
    gRutoChildMouthFrownTex,
    gRutoChildMouthOpenTex,
};

static s32 sUnused = 0;

#pragma asmproc recurse
#include "z_en_ru1_cutscene_data.c"

static u32 D_80AF1938 = 0;

static EnRu1ActionFunc sActionFuncs[] = {
    func_80AEC0B4, // RUTO_ACTION_00
    func_80AEC100, // RUTO_ACTION_01
    func_80AEC130, // RUTO_ACTION_02
    func_80AEC17C, // RUTO_ACTION_03
    func_80AEC1D4, // RUTO_ACTION_04
    func_80AEC244, // RUTO_ACTION_05
    func_80AEC2C0, // RUTO_ACTION_06
    EnRu1_SetupFirstTimeMeetingCS, // RUTO_ACTION_FIRST_TIME_MEET_CS
    func_80AECAB4, // RUTO_ACTION_08
    func_80AECAD4, // RUTO_ACTION_09
    func_80AECB18, // RUTO_ACTION_10
    func_80AECB60, // RUTO_ACTION_11
    func_80AECBB8, // RUTO_ACTION_12
    func_80AECC1C, // RUTO_ACTION_13
    func_80AECC84, // RUTO_ACTION_14
    func_80AED304, // RUTO_ACTION_15
    func_80AED324, // RUTO_ACTION_16
    func_80AED344, // RUTO_ACTION_17
    func_80AED374, // RUTO_ACTION_18
    func_80AED3A4, // RUTO_ACTION_19
    func_80AED3E0, // RUTO_ACTION_20
    func_80AED414, // RUTO_ACTION_21
    func_80AEF29C, // RUTO_ACTION_22
    func_80AEF2AC, // RUTO_ACTION_23
    func_80AEF2D0, // RUTO_ACTION_24
    func_80AEF354, // RUTO_ACTION_25
    func_80AEF3A8, // RUTO_ACTION_26
    func_80AEEBD4, // RUTO_ACTION_27
    func_80AEEC5C, // RUTO_ACTION_28
    func_80AEECF0, // RUTO_ACTION_29
    func_80AEED58, // RUTO_ACTION_30
    EnRu1_SetupSitAndSquirm, // RUTO_ACTION_SIT_AND_SQUIRM
    EnRu1_SetupSitIdle, // RUTO_ACTION_SIT_IDLE
    func_80AEEE9C, // RUTO_ACTION_33
    func_80AEEF08, // RUTO_ACTION_34
    func_80AEEF5C, // RUTO_ACTION_35
    func_80AEF9D8, // RUTO_ACTION_36
    func_80AEFA2C, // RUTO_ACTION_37
    func_80AEFAAC, // RUTO_ACTION_38
    func_80AEFB04, // RUTO_ACTION_39
    func_80AEFB68, // RUTO_ACTION_40
    func_80AEFCE8, // RUTO_ACTION_41
    EnRu1_SetupAbductionCS, // RUTO_ACTION_42
    func_80AEFC24, // RUTO_ACTION_43
    func_80AEFECC, // RUTO_ACTION_44
    func_80AEFF40, // RUTO_ACTION_45
};

static EnRu1PreLimbDrawFunc sPreLimbDrawFuncs[] = {
    func_80AF0278,
};

static Vec3f sMultVec = { 0.0f, 10.0f, 0.0f };

static EnRu1DrawFunc sDrawFuncs[] = {
    EnRu1_DrawNothing,
    EnRu1_DrawOpa,
    EnRu1_DrawXlu,
};

const ActorInit En_Ru1_InitVars = {
    ACTOR_EN_RU1,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_RU1,
    sizeof(EnRu1),
    (ActorFunc)EnRu1_Init,
    (ActorFunc)EnRu1_Destroy,
    (ActorFunc)EnRu1_Update,
    (ActorFunc)EnRu1_Draw,
};

void func_80AEAC10(EnRu1* this, PlayState* play) {
    s32 pad[5];

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void func_80AEAC54(EnRu1* this, PlayState* play) {
    s32 pad[5];

    Collider_UpdateCylinder(&this->actor, &this->collider2);
    if (this->ocEnabled) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider2.base);
    } else if (this->actor.xzDistToPlayer > 32.0f) {
        this->ocEnabled = true;
    }
}

void func_80AEACDC(EnRu1* this, PlayState* play) {
    s32 pad[5];

    Collider_UpdateCylinder(&this->actor, &this->collider2);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider2.base);
}

void func_80AEAD20(Actor* thisx, PlayState* play) {
    EnRu1* this = (EnRu1*)thisx;

    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinderType1(play, &this->collider, &this->actor, &sCylinderInit1);

    Collider_InitCylinder(play, &this->collider2);
    Collider_SetCylinderType1(play, &this->collider2, &this->actor, &sCylinderInit2);
}

void EnRu1_DestroyColliders(EnRu1* this, PlayState* play) {
    Collider_DestroyCylinder(play, &this->collider);
    Collider_DestroyCylinder(play, &this->collider2);
}

void func_80AEADD8(EnRu1* this) {
    this->ocEnabled = false;
}

u8 EnRu1_GetSwitchFlag(EnRu1* this) {
    u8 params = this->actor.params >> 8;

    return params;
}

u8 EnRu1_GetParameters(EnRu1* this) {
    s16 params = this->actor.params;

    return params;
}

void EnRu1_Destroy(Actor* thisx, PlayState* play) {
    EnRu1* this = (EnRu1*)thisx;

    EnRu1_DestroyColliders(this, play);
}

void EnRu1_UpdateEyes(EnRu1* this) {
    s32 pad[3];
    s16* blinkTimer = &this->blinkTimer;
    s16* eyeIndex = &this->eyeIndex;

    if (DECR(*blinkTimer) == 0) {
        *blinkTimer = Rand_S16Offset(60, 60);
    }

    *eyeIndex = *blinkTimer;
    if (*eyeIndex >= 3) {
        *eyeIndex = 0;
    }
}

void EnRu1_SetEyeIndex(EnRu1* this, s16 eyeIndex) {
    this->eyeIndex = eyeIndex;
}

void EnRu1_SetMouthIndex(EnRu1* this, s16 mouthIndex) {
    this->mouthIndex = mouthIndex;
}

void func_80AEAECC(EnRu1* this, PlayState* play) {
    f32* velocityY = &this->actor.velocity.y;
    f32 velocityYHeld = *velocityY;

    *velocityY = -4.0f;
    Actor_UpdateBgCheckInfo(play, &this->actor, 19.0f, 25.0f, 30.0f,
                            UPDBGCHECKINFO_FLAG_0 | UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_2);
    *velocityY = velocityYHeld;
}

s32 EnRu1_IsCsStateIdle(PlayState* play) {
    if (play->csCtx.state == CS_STATE_IDLE) {
        return true;
    }
    return false;
}

CsCmdActorAction* func_80AEAF58(PlayState* play, s32 npcActionIdx) {
    s32 pad[2];
    CsCmdActorAction* ret = NULL;

    if (!EnRu1_IsCsStateIdle(play)) {
        ret = play->csCtx.npcActions[npcActionIdx];
    }
    return ret;
}

s32 func_80AEAFA0(PlayState* play, u16 action, s32 npcActionIdx) {
    CsCmdActorAction* csCmdNPCAction = func_80AEAF58(play, npcActionIdx);

    if ((csCmdNPCAction != NULL) && (csCmdNPCAction->action == action)) {
        return true;
    }
    return false;
}

s32 func_80AEAFE0(PlayState* play, u16 action, s32 npcActionIdx) {
    CsCmdActorAction* csCmdNPCAction = func_80AEAF58(play, npcActionIdx);

    if ((csCmdNPCAction != NULL) && (csCmdNPCAction->action != action)) {
        return true;
    }
    return false;
}

s32 func_80AEB020(EnRu1* this, PlayState* play) {
    Actor* actorIt = play->actorCtx.actorLists[ACTORCAT_NPC].head;
    EnRu1* someEnRu1;

    while (actorIt != NULL) {
        if (actorIt->id == ACTOR_EN_RU1) {
            someEnRu1 = (EnRu1*)actorIt;
            if (someEnRu1 != this) {
                if ((someEnRu1->action == RUTO_ACTION_SIT_AND_SQUIRM) ||
                    (someEnRu1->action == RUTO_ACTION_SIT_IDLE) || (someEnRu1->action == 24)) {
                    return true;
                }
            }
        }
        actorIt = actorIt->next;
    }
    return false;
}

BgBdanObjects* EnRu1_FindBigOctoPlatformActor(PlayState* play) {
    Actor* actorIt = play->actorCtx.actorLists[ACTORCAT_BG].head;

    while (actorIt != NULL) {
        if (actorIt->id == ACTOR_BG_BDAN_OBJECTS && actorIt->params == 0) {
            return (BgBdanObjects*)actorIt;
        }
        actorIt = actorIt->next;
    }
    // "There is no stand"
    osSyncPrintf(VT_FGCOL(RED) "お立ち台が無い!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
    return NULL;
}

void EnRu1_SetBgBdanObjectsActorCameraSetting(EnRu1* this, s32 cameraSetting) {
    if (this->bgBdanObjectsActor != NULL) {
        this->bgBdanObjectsActor->cameraSetting = cameraSetting;
    }
}

s32 EnRu1_GetBgBdanObjectsActorCameraSetting(EnRu1* this) {
    if (this->bgBdanObjectsActor != NULL) {
        return this->bgBdanObjectsActor->cameraSetting;
    } else {
        return 0;
    }
}

Actor* EnRu1_FindSapphireActor(PlayState* play) {
    Actor* actorIt = play->actorCtx.actorLists[ACTORCAT_BOSS].head;

    while (actorIt != NULL) {
        if ((actorIt->id == ACTOR_DEMO_EFFECT) && ((actorIt->params & 0xFF) == 0x15)) {
            return actorIt;
        }
        actorIt = actorIt->next;
    }
    return NULL;
}

s32 func_80AEB174(PlayState* play) {
    return (Message_GetState(&play->msgCtx) == TEXT_STATE_EVENT) && Message_ShouldAdvance(play);
}

s32 func_80AEB1B4(PlayState* play) {
    return Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING;
}

void func_80AEB1D8(EnRu1* this) {
    this->action = RUTO_ACTION_36;
    this->drawConfig = RUTO_DRAW_NOTHING;
    this->actor.velocity.x = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.velocity.z = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
    EnRu1_SetBgBdanObjectsActorCameraSetting(this, CAM_SET_NONE);
}

void func_80AEB220(EnRu1* this, PlayState* play) {
    if ((EnRu1_IsCsStateIdle(play)) && (this->actor.params == 0xA)) {
        func_80AEB1D8(this);
    }
}

void EnRu1_ChangeAnimation(EnRu1* this, AnimationHeader* animation, u8 arg2, f32 morphFrames, s32 arg4) {
    s32 pad[2];
    AnimationHeader* animHeader = SEGMENTED_TO_VIRTUAL(animation);
    f32 frameCount = Animation_GetLastFrame(animHeader);
    f32 playbackSpeed;
    f32 unk0;
    f32 fc;

    if (arg4 == 0) {
        unk0 = 0.0f;
        fc = frameCount;
        playbackSpeed = 1.0f;
    } else {
        unk0 = frameCount;
        fc = 0.0f;
        playbackSpeed = -1.0f;
    }

    Animation_Change(&this->skelAnime, animHeader, playbackSpeed, unk0, fc, arg2, morphFrames);
}

s32 EnRu1_UpdateSkelAnime(EnRu1* this) {
    // why?
    if (this->action != RUTO_ACTION_SIT_IDLE) {
        return SkelAnime_Update(&this->skelAnime);
    } else {
        return SkelAnime_Update(&this->skelAnime);
    }
}

void func_80AEB364(EnRu1* this, PlayState* play) {
    this->skelAnime.moveFlags |= 1;
    AnimationContext_SetMoveActor(play, &this->actor, &this->skelAnime, 1.0f);
}

void func_80AEB3A4(EnRu1* this, PlayState* play) {
    this->skelAnime.moveFlags |= 1;
    func_80AEB364(this, play);
}

void func_80AEB3CC(EnRu1* this) {
    this->skelAnime.moveFlags &= ~0x1;
}

void EnRu1_SetupSapphireCS(EnRu1* this, PlayState* play) {
    EnRu1_ChangeAnimation(this, &gRutoChildWaitHandsBehindBackAnim, 0, 0, 0);
    this->action = 0;
    this->drawConfig = RUTO_DRAW_OPA;
    EnRu1_SetEyeIndex(this, 4);
    EnRu1_SetMouthIndex(this, 0);
}

CsCmdActorAction* func_80AEB438(PlayState* play) {
    return func_80AEAF58(play, 3);
}

s32 func_80AEB458(PlayState* play, u16 action) {
    return func_80AEAFA0(play, action, 3);
}

s32 func_80AEB480(PlayState* play, u16 action) {
    return func_80AEAFE0(play, action, 3);
}

void EnRu1_SpawnRipple(EnRu1* this, PlayState* play, s16 radiusMax, s16 life) {
    Vec3f pos;
    Actor* thisx = &this->actor;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
    pos.z = this->actor.world.pos.z;
    EffectSsGRipple_Spawn(play, &pos, 100, radiusMax, life);
}

void func_80AEB50C(EnRu1* this, PlayState* play) {
    this->unk_270 += 1.0f;
    if (this->unk_270 >= kREG(3) + 10.0f) {
        EnRu1_SpawnRipple(this, play, kREG(1) + 500, 0);
        this->unk_270 = 0.0f;
    }
}

void func_80AEB59C(EnRu1* this, PlayState* play) {
    EnRu1_SpawnRipple(this, play, kREG(2) + 500, 0);
    EnRu1_SpawnRipple(this, play, kREG(2) + 500, kREG(3) + 10.0f);
    EnRu1_SpawnRipple(this, play, kREG(2) + 500, (kREG(3) + 10.0f) * 2.0f);
}

void EnRu1_SpawnSplash(EnRu1* this, PlayState* play) {
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y + this->actor.yDistToWater;
    pos.z = this->actor.world.pos.z;

    EffectSsGSplash_Spawn(play, &pos, 0, 0, 1, 0);
}

void func_80AEB6E0(EnRu1* this, PlayState* play) {
    SkelAnime* skelAnime = &this->skelAnime;

    if (skelAnime->baseTransl.y < skelAnime->jointTable[0].y) {
        skelAnime->moveFlags |= 3;
        AnimationContext_SetMoveActor(play, &this->actor, skelAnime, 1.0f);
    }
}

void func_80AEB738(EnRu1* this, PlayState* play) {
    SkelAnime* skelAnime = &this->skelAnime;

    skelAnime->baseTransl = skelAnime->jointTable[0];
    skelAnime->prevTransl = skelAnime->jointTable[0];
    if (skelAnime->baseTransl.y < skelAnime->jointTable[0].y) {
        skelAnime->moveFlags |= 3;
        AnimationContext_SetMoveActor(play, &this->actor, skelAnime, 1.0f);
    }
}

void func_80AEB7D0(EnRu1* this) {
    this->skelAnime.moveFlags &= ~0x3;
}

f32 func_80AEB7E0(CsCmdActorAction* csCmdNPCAction, PlayState* play) {
    s32 csCtxFrames = play->csCtx.frames;

    if ((csCtxFrames < csCmdNPCAction->endFrame) && (csCmdNPCAction->endFrame - csCmdNPCAction->startFrame > 0)) {
        return (Math_CosS(((csCtxFrames - csCmdNPCAction->startFrame) /
                           (f32)(csCmdNPCAction->endFrame - csCmdNPCAction->startFrame)) *
                          32768.0f) *
                -0.5f) +
               0.5f;
    }
    return 1.0f;
}

f32 func_80AEB87C(f32 arg0, s32 arg1, s32 arg2) {
    return (((f32)arg2 - arg1) * arg0) + arg1;
}

void func_80AEB89C(EnRu1* this, PlayState* play) {
    CsCmdActorAction* npcAction = func_80AEB438(play);
    s16 npcActionRotY;

    if (npcAction != NULL) {
        npcActionRotY = npcAction->rot.y;
        this->actor.shape.rot.y = npcActionRotY;
        this->actor.world.rot.y = npcActionRotY;
        this->actor.world.pos.x = npcAction->startPos.x;
        this->actor.world.pos.y = npcAction->startPos.y;
        this->actor.world.pos.z = npcAction->startPos.z;
    }
}

void func_80AEB914(EnRu1* this, PlayState* play) {
    func_80AEB89C(this, play);
}

void func_80AEB934(EnRu1* this, PlayState* play) {
    func_80AEB89C(this, play);
}

void func_80AEB954(EnRu1* this, PlayState* play) {
    func_80AEB6E0(this, play);
}

void func_80AEB974(EnRu1* this, PlayState* play) {
    Vec3f* thisPos;
    f32 sp30;
    CsCmdActorAction* csCmdNPCAction = func_80AEB438(play);
    s32 pad;

    if (csCmdNPCAction != NULL) {
        sp30 = func_80AEB7E0(csCmdNPCAction, play);
        thisPos = &this->actor.world.pos;
        thisPos->x = func_80AEB87C(sp30, csCmdNPCAction->startPos.x, csCmdNPCAction->endPos.x);
        thisPos->y = func_80AEB87C(sp30, csCmdNPCAction->startPos.y, csCmdNPCAction->endPos.y);
        thisPos->z = func_80AEB87C(sp30, csCmdNPCAction->startPos.z, csCmdNPCAction->endPos.z);
    }
}

void func_80AEBA0C(EnRu1* this, PlayState* play) {
    func_80AEB6E0(this, play);
}

void func_80AEBA2C(EnRu1* this, PlayState* play) {
    s32 pad;
    Vec3f* unk_364 = &this->unk_364;
    Vec3f* thisPos;
    f32 temp_ret_2;
    CsCmdActorAction* csCmdNPCAction = func_80AEB438(play);
    s32 pad2;

    if (csCmdNPCAction != NULL) {
        temp_ret_2 = func_80AEB7E0(csCmdNPCAction, play);
        thisPos = &this->actor.world.pos;
        thisPos->x = func_80AEB87C(temp_ret_2, unk_364->x, csCmdNPCAction->endPos.x);
        thisPos->y = func_80AEB87C(temp_ret_2, unk_364->y, csCmdNPCAction->endPos.y);
        thisPos->z = func_80AEB87C(temp_ret_2, unk_364->z, csCmdNPCAction->endPos.z);
    }
}

void func_80AEBAFC(EnRu1* this) {
    if (!this->divingSoundPlayed) {
        func_80078914(&this->actor.projectedPos, NA_SE_EV_DIVE_INTO_WATER);
        this->divingSoundPlayed = true;
    }
}

void func_80AEBB3C(EnRu1* this) {
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80078914(&this->actor.projectedPos, NA_SE_PL_FACE_UP);
    }
}

void func_80AEBB78(EnRu1* this) {
    SkelAnime* skelAnime = &this->skelAnime;

    if (Animation_OnFrame(skelAnime, 4.0f) || Animation_OnFrame(skelAnime, 13.0f) ||
        Animation_OnFrame(skelAnime, 22.0f) || Animation_OnFrame(skelAnime, 31.0f)) {
        func_80078914(&this->actor.projectedPos, NA_SE_PL_SWIM);
    }
}

void func_80AEBBF4(EnRu1* this) {
    if (Animation_OnFrame(&this->skelAnime, 8.0f)) {
        func_80078914(&this->actor.projectedPos, NA_SE_PL_SUBMERGE);
    }
}

void func_80AEBC30(PlayState* play) {
    Player* player;

    if (play->csCtx.frames == 0xCD) {
        player = GET_PLAYER(play);
        Audio_PlaySoundGeneral(NA_SE_EV_DIVE_INTO_WATER, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                               &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
    }
}

void func_80AEBC84(EnRu1* this, PlayState* play) {
    if (play->csCtx.frames == 0x82) {
        func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_LAUGH_0);
    }
}

void func_80AEBCB8(EnRu1* this, UNK_TYPE arg1) {
    if (arg1 != 0) {
        Animation_Change(&this->skelAnime, &gRutoChildSwimOnBackAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildSwimOnBackAnim), ANIMMODE_LOOP, -8.0f);
    }
}

void func_80AEBD1C(EnRu1* this, PlayState* play) {
    if (func_80AEB480(play, 2)) {
        this->action = RUTO_ACTION_01;
        this->drawConfig = RUTO_DRAW_NOTHING;
        func_80AEB914(this, play);
        func_80AEAECC(this, play);
        EnRu1_SpawnSplash(this, play);
        func_80AEB59C(this, play);
    }
}

void func_80AEBD94(EnRu1* this, PlayState* play) {
    s32 pad[2];
    f32 frameCount;

    if (func_80AEB480(play, 3)) {
        frameCount = Animation_GetLastFrame(&gRutoChildAnim_009060);
        func_80AEB934(this, play);
        func_80AEB738(this, play);
        Animation_Change(&this->skelAnime, &gRutoChildAnim_009060, 1.0f, 0.0f, frameCount, ANIMMODE_ONCE, 0.0f);
        this->action = RUTO_ACTION_02;
        this->drawConfig = RUTO_DRAW_OPA;
    }
}

void func_80AEBE3C(EnRu1* this, PlayState* play, s32 arg2) {
    s32 pad[2];
    f32 frameCount;

    if (arg2 != 0) {
        frameCount = Animation_GetLastFrame(&gRutoChildTreadWaterAnim);
        func_80AEB7D0(this);
        Animation_Change(&this->skelAnime, &gRutoChildTreadWaterAnim, 1.0f, 0, frameCount, ANIMMODE_LOOP, -8.0f);
        this->action = RUTO_ACTION_03;
    } else {
        func_80AEB954(this, play);
    }
}

void func_80AEBEC8(EnRu1* this, PlayState* play) {
    s32 pad[2];
    f32 frameCount;

    if (func_80AEB458(play, 6)) {
        frameCount = Animation_GetLastFrame(&gRutoChildTransitionToSwimOnBackAnim);
        func_80AEB738(this, play);
        Animation_Change(&this->skelAnime, &gRutoChildTransitionToSwimOnBackAnim, 1.0f, 0, frameCount, ANIMMODE_ONCE,
                         -8.0f);
        this->action = RUTO_ACTION_04;
    }
}

void func_80AEBF60(EnRu1* this, PlayState* play) {
    if (func_80AEB480(play, 6)) {
        func_80AEB7D0(this);
        this->action = RUTO_ACTION_05;
        this->unk_364 = this->actor.world.pos;
    } else {
        func_80AEBA0C(this, play);
    }
}

void func_80AEBFD8(EnRu1* this, PlayState* play) {
    CsCmdActorAction* csCmdNPCAction = func_80AEB438(play);
    f32 frameCount;
    u16 csCtxFrames;
    u16 endFrame;

    if (csCmdNPCAction != NULL) {
        csCtxFrames = play->csCtx.frames;
        endFrame = csCmdNPCAction->endFrame;
        if (csCtxFrames >= endFrame - 2) {
            frameCount = Animation_GetLastFrame(&gRutoChildTransitionFromSwimOnBackAnim);
            Animation_Change(&this->skelAnime, &gRutoChildTransitionFromSwimOnBackAnim, 1.0, 0, frameCount,
                             ANIMMODE_ONCE, -8.0f);
            this->action = RUTO_ACTION_06;
        }
    }
}

void func_80AEC070(EnRu1* this, PlayState* play, UNK_TYPE arg2) {
    if ((func_80AEB458(play, 8)) && (arg2 != 0)) {
        Actor_Kill(&this->actor);
    }
}

void func_80AEC0B4(EnRu1* this, PlayState* play) {
    func_80AEB89C(this, play);
    EnRu1_UpdateSkelAnime(this);
    func_80AEBC84(this, play);
    func_80AEBC30(play);
    func_80AEBD1C(this, play);
}

void func_80AEC100(EnRu1* this, PlayState* play) {
    func_80AEBAFC(this);
    func_80AEBD94(this, play);
}

void func_80AEC130(EnRu1* this, PlayState* play) {
    s32 something = EnRu1_UpdateSkelAnime(this);

    func_80AEAECC(this, play);
    func_80AEBB3C(this);
    func_80AEBE3C(this, play, something);
}

void func_80AEC17C(EnRu1* this, PlayState* play) {
    func_80AEB974(this, play);
    func_80AEAECC(this, play);
    EnRu1_UpdateSkelAnime(this);
    func_80AEB50C(this, play);
    func_80AEBEC8(this, play);
}

void func_80AEC1D4(EnRu1* this, PlayState* play) {
    s32 something;

    something = EnRu1_UpdateSkelAnime(this);
    func_80AEAECC(this, play);
    EnRu1_UpdateEyes(this);
    func_80AEB50C(this, play);
    func_80AEBCB8(this, something);
    func_80AEBBF4(this);
    func_80AEBF60(this, play);
}

void func_80AEC244(EnRu1* this, PlayState* play) {
    s32 something;

    something = EnRu1_UpdateSkelAnime(this);
    func_80AEBA2C(this, play);
    func_80AEAECC(this, play);
    EnRu1_UpdateEyes(this);
    func_80AEB50C(this, play);
    func_80AEBCB8(this, something);
    func_80AEBB78(this);
    func_80AEBFD8(this, play);
}

void func_80AEC2C0(EnRu1* this, PlayState* play) {
    s32 something;

    something = EnRu1_UpdateSkelAnime(this);
    func_80AEAECC(this, play);
    EnRu1_UpdateEyes(this);
    func_80AEB50C(this, play);
    func_80AEC070(this, play, something);
}

void func_80AEC320(EnRu1* this, PlayState* play) {
    s8 actorRoom;

    if (!GET_INFTABLE(INFTABLE_RUTO_FIRST_MEET)) {
        EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
        this->action = RUTO_ACTION_FIRST_TIME_MEET_CS;
        EnRu1_SetMouthIndex(this, 1);
    } else if (GET_INFTABLE(INFTABLE_RUTO_CAN_SPAWN_IN_ROOM_2) && !GET_INFTABLE(INFTABLE_RUTO_HOLDING_SWITCH_38) && !GET_INFTABLE(INFTABLE_RUTO_AFTER_RUTO_HAS_SAPPHIRE)) {
        if (!func_80AEB020(this, play)) {
            EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
            actorRoom = this->actor.room;
            this->action = RUTO_ACTION_22;
            this->actor.room = -1;
            this->drawConfig = RUTO_DRAW_NOTHING;
            this->roomNum1 = actorRoom;
            this->roomNum3 = actorRoom;
            this->roomNum2 = actorRoom;
        } else {
            Actor_Kill(&this->actor);
        }
    } else {
        Actor_Kill(&this->actor);
    }
}

void func_80AEC40C(EnRu1* this) {
    f32 unk_26C = this->unk_26C;

    if (unk_26C < 8.0f) {
        this->actor.speedXZ = (((kREG(3) * 0.01f) + 2.7f) / 8.0f) * unk_26C;
    } else {
        this->actor.speedXZ = (kREG(3) * 0.01f) + 2.7f;
    }
    this->actor.velocity.y = -1.0f;
    Actor_MoveForward(&this->actor);
}

void func_80AEC4CC(EnRu1* this) {
    this->actor.velocity.y = -1.0f;
    Actor_MoveForward(&this->actor);
}

void func_80AEC4F4(EnRu1* this) {
    f32* speedXZ = &this->actor.speedXZ;
    f32* unk_26C = &this->unk_26C;

    if (this->unk_26C < 8.0f) {
        *unk_26C += 1.0f;
        *speedXZ *= (8.0f - *unk_26C) / 8.0f;
        this->actor.velocity.y = -*unk_26C * (((kREG(4) * 0.01f) + 13.0f) / 8.0f);
    } else {
        *speedXZ = 0.0f;
        this->actor.velocity.y = -((kREG(4) * 0.01f) + 13.0f);
    }
    Actor_MoveForward(&this->actor);
}

s32 EnRu1_IsPlayerInRange(EnRu1* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 thisPosZ = this->actor.world.pos.z;
    f32 playerPosZ = player->actor.world.pos.z;

    if ((playerPosZ - thisPosZ <= 265.0f) && (player->actor.world.pos.y >= this->actor.world.pos.y)) {
        return true;
    }
    return false;
}

void func_80AEC650(EnRu1* this) {
    s32 pad[2];

    if (this->unk_280 == 0) {
        if (Animation_OnFrame(&this->skelAnime, 2.0f) || Animation_OnFrame(&this->skelAnime, 7.0f)) {
            func_80078914(&this->actor.projectedPos, NA_SE_PL_WALK_DIRT);
        }
    }
}

void func_80AEC6B0(EnRu1* this) {
    func_80078914(&this->actor.projectedPos, NA_SE_EV_FALL_DOWN_DIRT);
    func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_FALL);
}

void func_80AEC6E4(EnRu1* this, PlayState* play) { // fall animation?
    if ((func_80AEAFA0(play, 4, 3)) && (this->unk_280 == 0)) {
        Animation_Change(&this->skelAnime, &gRutoChildBringArmsUpAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildBringArmsUpAnim), ANIMMODE_ONCE, -8.0f);
        this->unk_280 = 1;
        func_80AEC6B0(this);
    }
}

void EnRu1_PlayFirstTimeMeetingCS(EnRu1* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);

    if ((EnRu1_IsPlayerInRange(this, play)) && (!Play_InCsMode(play)) &&
        (!(player->stateFlags1 & (PLAYER_STATE1_13 | PLAYER_STATE1_14 | PLAYER_STATE1_21))) &&
        (player->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {

        play->csCtx.segment = &sFirstTimeMeetingRutoCS;
        gSaveContext.cutsceneTrigger = 1;
        player->linearVelocity = 0.0f;
        this->action = RUTO_ACTION_08;
    }
}

void func_80AEC81C(EnRu1* this, PlayState* play) {
    CsCmdActorAction* csCmdNPCAction;
    s16 newRotY;

    if (func_80AEAFE0(play, 1, 3)) {
        csCmdNPCAction = play->csCtx.npcActions[3];
        this->actor.world.pos.x = csCmdNPCAction->startPos.x;
        this->actor.world.pos.y = csCmdNPCAction->startPos.y;
        this->actor.world.pos.z = csCmdNPCAction->startPos.z;
        newRotY = csCmdNPCAction->rot.y;
        this->actor.shape.rot.y = newRotY;
        this->actor.world.rot.y = newRotY;
        this->action = RUTO_ACTION_09;
        this->drawConfig = RUTO_DRAW_OPA;
    }
}

void func_80AEC8B8(EnRu1* this, PlayState* play) {
    if (func_80AEAFA0(play, 3, 3)) {
        Animation_Change(&this->skelAnime, &gRutoChildTurnAroundAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildTurnAroundAnim), ANIMMODE_ONCE, -8.0f);
        this->action = RUTO_ACTION_10;
    }
}

void func_80AEC93C(EnRu1* this, UNK_TYPE arg1) {
    if (arg1 != 0) {
        Animation_Change(&this->skelAnime, &gRutoChildWalkAnim, 1.0f, 0, Animation_GetLastFrame(&gRutoChildWalkAnim),
                         ANIMMODE_LOOP, -8.0f);
        this->actor.world.rot.y += 0x8000;
        this->action = 0xB;
        this->unk_26C = 0.0f;
    }
}

void func_80AEC9C4(EnRu1* this) {
    this->unk_26C += 1.0f;
    if (this->unk_26C >= 8.0f) {
        this->action = RUTO_ACTION_12;
        this->unk_26C = 0.0f;
        this->actor.velocity.y = -1.0f;
    }
}

void func_80AECA18(EnRu1* this) {
    if (!(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        this->action = RUTO_ACTION_13;
        this->unk_26C = 0.0f;
        this->actor.velocity.y = 0.0f;
    }
}

void func_80AECA44(EnRu1* this, PlayState* play) {
    if (func_80AEAFA0(play, 5, 3)) {
        SET_INFTABLE(INFTABLE_RUTO_FIRST_MEET);
        this->action = RUTO_ACTION_14;
    }
}

void EnRu1_SetupFirstTimeMeetingCS(EnRu1* this, PlayState* play) {
    EnRu1_PlayFirstTimeMeetingCS(this, play);
}

void func_80AECAB4(EnRu1* this, PlayState* play) {
    func_80AEC81C(this, play);
}

void func_80AECAD4(EnRu1* this, PlayState* play) {
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEC8B8(this, play);
}

void func_80AECB18(EnRu1* this, PlayState* play) {
    s32 something;

    something = EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEC93C(this, something);
}

void func_80AECB60(EnRu1* this, PlayState* play) {
    func_80AEC40C(this);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEC650(this);
    func_80AEC9C4(this);
}

void func_80AECBB8(EnRu1* this, PlayState* play) {
    func_80AEC4CC(this);
    func_80AEC6E4(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEC650(this);
    func_80AECA18(this);
}

void func_80AECC1C(EnRu1* this, PlayState* play) {
    func_80AEC4F4(this);
    func_80AEC6E4(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEC650(this);
    func_80AECA44(this, play);
}

void func_80AECC84(EnRu1* this, PlayState* play) {
    if (play->csCtx.state == CS_STATE_IDLE) {
        Actor_Kill(&this->actor);
    }
}

void func_80AECCB0(EnRu1* this, PlayState* play) {
    s32 pad;
    Vec3f* pos;
    s16 yawTowardsPlayer;
    f32 spawnX;
    f32 spawnY;
    f32 spawnZ;
    s32 pad2[2];

    yawTowardsPlayer = this->actor.yawTowardsPlayer;
    pos = &this->actor.world.pos;
    spawnX = ((kREG(1) + 12.0f) * Math_SinS(yawTowardsPlayer)) + pos->x;
    spawnY = pos->y;
    spawnZ = ((kREG(1) + 12.0f) * Math_CosS(yawTowardsPlayer)) + pos->z;
    this->blueWarp = (DoorWarp1*)Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_DOOR_WARP1, spawnX,
                                                    spawnY, spawnZ, 0, yawTowardsPlayer, 0, WARP_BLUE_RUTO);
}

void EnRu1_SetupBlueWarp(EnRu1* this, PlayState* play) {
    EnRu1_ChangeAnimation(this, &gRutoChildWaitHandsOnHipsAnim, 0, 0, 0);
    this->action = RUTO_ACTION_15;
    this->actor.shape.yOffset = -10000.0f;
    EnRu1_SetEyeIndex(this, 5);
    EnRu1_SetMouthIndex(this, 2);
}

void func_80AECE04(EnRu1* this, PlayState* play) {
    this->actor.shape.yOffset += (250.0f / 3.0f);
}

void func_80AECE20(EnRu1* this, PlayState* play) {
    s32 pad2;
    Player* player = GET_PLAYER(play);
    Vec3f* playerPos = &player->actor.world.pos;
    s16 shapeRotY = player->actor.shape.rot.y;
    s32 pad;
    f32 unk_27C = this->unk_27C;
    Vec3f* pos = &this->actor.world.pos;

    pos->x = (Math_SinS(shapeRotY) * unk_27C) + playerPos->x;
    pos->y = playerPos->y;
    pos->z = (Math_CosS(shapeRotY) * unk_27C) + playerPos->z;
}

void func_80AECEB4(EnRu1* this, PlayState* play) {
    s32 pad;
    Player* player = GET_PLAYER(play);
    Vec3f* player_unk_450 = &player->unk_450;
    Vec3f* pos = &this->actor.world.pos;
    s16 shapeRotY = this->actor.shape.rot.y;

    player_unk_450->x = ((kREG(2) + 30.0f) * Math_SinS(shapeRotY)) + pos->x;
    player_unk_450->z = ((kREG(2) + 30.0f) * Math_CosS(shapeRotY)) + pos->z;
}

s32 func_80AECF6C(EnRu1* this, PlayState* play) {
    s16* shapeRotY;
    Player* player = GET_PLAYER(play);
    Player* otherPlayer;
    s16 temp_f16;
    f32 temp1;
    f32 temp2;
    s32 pad2[5];

    this->unk_26C += 1.0f;
    if ((player->actor.speedXZ == 0.0f) && (this->unk_26C >= 3.0f)) {
        otherPlayer = GET_PLAYER(play);
        player->actor.world.pos.x = otherPlayer->unk_450.x;
        player->actor.world.pos.y = otherPlayer->unk_450.y;
        player->actor.world.pos.z = otherPlayer->unk_450.z;
        shapeRotY = &player->actor.shape.rot.y;
        temp1 = this->actor.world.pos.x - player->actor.world.pos.x;
        temp2 = this->actor.world.pos.z - player->actor.world.pos.z;
        temp_f16 = RAD_TO_BINANG(Math_FAtan2F(temp1, temp2));
        if (*shapeRotY != temp_f16) {
            Math_SmoothStepToS(shapeRotY, temp_f16, 0x14, 0x1838, 0x64);
            player->actor.world.rot.y = *shapeRotY;
        } else {
            return true;
        }
    }
    return false;
}

s32 func_80AED084(EnRu1* this, s32 state) {
    if (this->blueWarp != NULL && this->blueWarp->rutoWarpState == state) {
        return true;
    }
    return false;
}

void func_80AED0B0(EnRu1* this, s32 state) {
    if (this->blueWarp != NULL) {
        this->blueWarp->rutoWarpState = state;
    }
}

void func_80AED0C8(EnRu1* this, PlayState* play) {
    this->action = RUTO_ACTION_16;
}

void func_80AED0D8(EnRu1* this, PlayState* play) {
    this->action = RUTO_ACTION_17;
    this->drawConfig = RUTO_DRAW_OPA;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    func_80AECCB0(this, play);
}

void func_80AED110(EnRu1* this) {
    if (this->actor.shape.yOffset >= 0.0f) {
        this->action = RUTO_ACTION_18;
        this->actor.shape.yOffset = 0.0f;
        func_80AED0B0(this, WARP_BLUE_RUTO_STATE_READY);
    }
}

void func_80AED154(EnRu1* this, PlayState* play) {
    if (func_80AED084(this, WARP_BLUE_RUTO_STATE_ENTERED)) {
        this->action = 0x13;
        this->unk_26C = 0.0f;
        func_80AECEB4(this, play);
    }
}

void func_80AED19C(EnRu1* this, s32 cond) {
    if (cond) {
        Animation_Change(&this->skelAnime, &gRutoChildTransitionHandsOnHipToCrossArmsAndLegsAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildTransitionHandsOnHipToCrossArmsAndLegsAnim), ANIMMODE_ONCE,
                         -8.0f);
        this->action = RUTO_ACTION_20;
        func_80AED0B0(this, WARP_BLUE_RUTO_STATE_3);
    }
}

void func_80AED218(EnRu1* this, UNK_TYPE arg1) {
    if (func_80AED084(this, WARP_BLUE_RUTO_STATE_TALKING)) {
        if (arg1 != 0) {
            Animation_Change(&this->skelAnime, &gRutoChildWaitSittingAnim, 1.0f, 0,
                             Animation_GetLastFrame(&gRutoChildWaitSittingAnim), ANIMMODE_LOOP, -8.0f);
        }
    } else if (func_80AED084(this, WARP_BLUE_RUTO_STATE_WARPING)) {
        Animation_Change(&this->skelAnime, &gRutoChildWaitInBlueWarpAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildWaitInBlueWarpAnim), ANIMMODE_ONCE, -8.0f);
        this->action = RUTO_ACTION_21;
        this->unk_27C = this->actor.xzDistToPlayer;
    }
}

void func_80AED304(EnRu1* this, PlayState* play) {
    func_80AED0C8(this, play);
}

void func_80AED324(EnRu1* this, PlayState* play) {
    func_80AED0D8(this, play);
}

void func_80AED344(EnRu1* this, PlayState* play) {
    func_80AECE04(this, play);
    EnRu1_UpdateSkelAnime(this);
    func_80AED110(this);
}

void func_80AED374(EnRu1* this, PlayState* play) {
    EnRu1_UpdateSkelAnime(this);
    func_80AED154(this, play);
}

void func_80AED3A4(EnRu1* this, PlayState* play) {
    EnRu1_UpdateSkelAnime(this);
    func_80AED19C(this, func_80AECF6C(this, play));
}

void func_80AED3E0(EnRu1* this, PlayState* play) {
    func_80AEAECC(this, play);
    func_80AED218(this, EnRu1_UpdateSkelAnime(this));
}

void func_80AED414(EnRu1* this, PlayState* play) {
    func_80AECE20(this, play);
    func_80AEAECC(this, play);
    EnRu1_UpdateSkelAnime(this);
}

void EnRu1_SetupCarry(EnRu1* this, PlayState* play) {
    s8 actorRoom;

    if (GET_INFTABLE(INFTABLE_RUTO_FIRST_MEET) && !GET_INFTABLE(INFTABLE_RUTO_AFTER_RUTO_HAS_SAPPHIRE) && !GET_INFTABLE(INFTABLE_RUTO_HOLDING_SWITCH_38) &&
        !GET_INFTABLE(INFTABLE_RUTO_CAN_SPAWN_IN_ROOM_2)) {
        if (!func_80AEB020(this, play)) {
            EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
            actorRoom = this->actor.room;
            this->action = RUTO_ACTION_22;
            this->actor.room = -1;
            this->roomNum1 = actorRoom;
            this->roomNum3 = actorRoom;
            this->roomNum2 = actorRoom;
        } else {
            Actor_Kill(&this->actor);
        }
    } else {
        Actor_Kill(&this->actor);
    }
}

void func_80AED4FC(EnRu1* this) {
    func_80078914(&this->actor.projectedPos, NA_SE_EV_LAND_DIRT);
}

void func_80AED520(EnRu1* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    Audio_PlaySoundGeneral(NA_SE_PL_PULL_UP_RUTO, &player->actor.projectedPos, 4, &gSfxDefaultFreqAndVolScale,
                           &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
    func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_LIFT);
}

void EnRu1_PlayThrowingSound(EnRu1* this) {
    if (this->actor.speedXZ != 0.0f) {
        func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_THROW);
    }
}

void func_80AED5B8(EnRu1* this) {
    func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_CRASH);
}

void EnRu1_PlayRutoSquirmSound(EnRu1* this) {
    func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_UNBALLANCE);
}

void func_80AED600(EnRu1* this) {
    func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_DISCOVER);
}

s32 func_80AED624(EnRu1* this, PlayState* play) {
    s8 curRoomNum = play->roomCtx.curRoom.num;

    if (this->roomNum2 != curRoomNum) {
        Actor_Kill(&this->actor);
        return false;
    } else if (((this->roomNum1 != curRoomNum) || (this->roomNum2 != curRoomNum)) &&
               (this->actor.yDistToWater > kREG(16) + 50.0f) && (this->action != RUTO_ACTION_33)) {
        this->action = RUTO_ACTION_33;
        this->drawConfig = RUTO_DRAW_XLU;
        this->alpha = 0xFF;
        this->unk_2A4 = 0.0f;
    }
    return true;
}

void func_80AED6DC(EnRu1* this, PlayState* play) {
    s8 curRoomNum = play->roomCtx.curRoom.num;

    this->roomNum2 = curRoomNum;
    this->unused = 0.0f;
}

void EnRu1_SetRoom2SpawnFlag(PlayState* play) {
    s8 curRoomNum;

    if (!GET_INFTABLE(INFTABLE_RUTO_CAN_SPAWN_IN_ROOM_2)) {
        curRoomNum = play->roomCtx.curRoom.num;
        if (curRoomNum == 2) {
            SET_INFTABLE(INFTABLE_RUTO_CAN_SPAWN_IN_ROOM_2);
        }
    }
}

void func_80AED738(EnRu1* this, PlayState* play) {
    u32 temp_v0;

    if (func_80AED624(this, play)) {
        this->unk_2A4 += 1.0f;
        if (this->unk_2A4 < 20.0f) {
            temp_v0 = ((20.0f - this->unk_2A4) * 255.0f) / 20.0f;
            this->alpha = temp_v0;
            this->actor.shape.shadowAlpha = temp_v0;
        } else {
            Actor_Kill(&this->actor);
        }
    }
}

void func_80AED83C(EnRu1* this) {
    s32 pad[2];
    Vec3s* tempPtr;
    Vec3s* tempPtr2;

    tempPtr = &this->unk_374.unk_08;
    Math_SmoothStepToS(&tempPtr->x, 0, 0x14, 0x1838, 0x64);
    Math_SmoothStepToS(&tempPtr->y, 0, 0x14, 0x1838, 0x64);
    tempPtr2 = &this->unk_374.unk_0E;
    Math_SmoothStepToS(&tempPtr2->x, 0, 0x14, 0x1838, 0x64);
    Math_SmoothStepToS(&tempPtr2->y, 0, 0x14, 0x1838, 0x64);
}

void func_80AED8DC(EnRu1* this) {
    s32 temp_hi;
    s16* unk_2AC = &this->unk_2AC;
    s16* someY = &this->unk_374.unk_08.y;
    s16* unk_29E = &this->unk_29E;
    s32 pad[2];

    if (DECR(*unk_2AC) == 0) {
        *unk_2AC = Rand_S16Offset(0xA, 0x19);
        temp_hi = *unk_2AC % 5;
        if (temp_hi == 0) {
            this->unk_2B0 = 1;
        } else if (temp_hi == 1) {
            this->unk_2B0 = 2;
        } else {
            this->unk_2B0 = 0;
        }
        *unk_29E = 0;
    }

    if (this->unk_2B0 == 0) {
        Math_SmoothStepToS(unk_29E, 0 - *someY, 1, 0x190, 0x190);
        Math_SmoothStepToS(someY, 0, 3, ABS(*unk_29E), 0x64);
    } else if (this->unk_2B0 == 1) {
        Math_SmoothStepToS(unk_29E, -0x2AAA - *someY, 1, 0x190, 0x190);
        Math_SmoothStepToS(someY, -0x2AAA, 3, ABS(*unk_29E), 0x64);
    } else {
        Math_SmoothStepToS(unk_29E, 0x2AAA - *someY, 1, 0x190, 0x190);
        Math_SmoothStepToS(someY, 0x2AAA, 3, ABS(*unk_29E), 0x64);
    }
}

void func_80AEDAE0(EnRu1* this, PlayState* play) {
    DynaPolyActor* dynaPolyActor = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

    if (dynaPolyActor == NULL || dynaPolyActor->actor.id == ACTOR_EN_BOX) {
        this->actor.bgCheckFlags &= ~(BGCHECKFLAG_GROUND | BGCHECKFLAG_WALL | BGCHECKFLAG_CEILING);
    }
}

void func_80AEDB30(EnRu1* this, PlayState* play) {
    DynaPolyActor* dynaPolyActor;
    f32* velocityY;
    f32* speedXZ;
    f32* gravity;
    s16 wallYaw;
    s16 rotY;
    s32 temp_a1_2;
    s32 temp_a0;
    s32 phi_v1;

    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        velocityY = &this->actor.velocity.y;
        dynaPolyActor = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);
        if (*velocityY <= 0.0f) {
            speedXZ = &this->actor.speedXZ;
            if (dynaPolyActor != NULL) {
                if (dynaPolyActor->actor.id != ACTOR_EN_BOX) {
                    *speedXZ = 0.0f;
                }
            } else {
                if (*speedXZ >= (kREG(27) * 0.01f) + 3.0f) {
                    *speedXZ *= (kREG(19) * 0.01f) + 0.8f;
                } else {
                    *speedXZ = 0.0f;
                }
            }
            gravity = &this->actor.gravity;
            if (dynaPolyActor != NULL) {
                if (dynaPolyActor->actor.id != ACTOR_EN_BOX) {
                    *velocityY = 0.0f;
                    this->actor.minVelocityY = 0.0f;
                    *gravity = 0.0f;
                } else {
                    *velocityY *= -1.0f;
                }
            } else {
                *velocityY *= -((kREG(20) * 0.01f) + 0.6f);
                if (*velocityY <= -*gravity * ((kREG(20) * 0.01f) + 0.6f)) {
                    *velocityY = 0.0f;
                    this->actor.minVelocityY = 0.0f;
                    *gravity = 0.0f;
                }
            }
            func_80AED4FC(this);
        }
    }
    if (this->actor.bgCheckFlags & BGCHECKFLAG_CEILING) {
        speedXZ = &this->actor.speedXZ;
        velocityY = &this->actor.velocity.y;
        if (*speedXZ >= (kREG(27) * 0.01f) + 3.0f) {
            *speedXZ *= (kREG(19) * 0.01f) + 0.8f;
        } else {
            *speedXZ = 0.0f;
        }
        if (*velocityY >= 0.0f) {
            *velocityY *= -((kREG(20) * 0.01f) + 0.6f);
            func_80AED4FC(this);
        }
    }
    if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
        speedXZ = &this->actor.speedXZ;
        if (*speedXZ != 0.0f) {
            rotY = this->actor.world.rot.y;
            wallYaw = this->actor.wallYaw;
            temp_a0 = (wallYaw * 2) - rotY;
            temp_a1_2 = temp_a0 + 0x8000;
            if ((s16)((temp_a0 - wallYaw) + 0x8000) >= 0) {
                phi_v1 = (s16)(temp_a1_2 - wallYaw);
            } else {
                phi_v1 = -(s16)(temp_a1_2 - wallYaw);
            }
            if (phi_v1 < 0x4001) {
                if (*speedXZ >= (kREG(27) * 0.01f) + 3.0f) {
                    *speedXZ *= (kREG(21) * 0.01f) + 0.6f;
                } else {
                    *speedXZ = 0.0f;
                }
                this->actor.world.rot.y = temp_a1_2;
                func_80AED4FC(this);
                func_80AED5B8(this);
            }
        }
    }
}

void func_80AEDEF4(EnRu1* this, PlayState* play) {
    f32* speedXZ = &this->actor.speedXZ;
    DynaPolyActor* dynaPolyActor = DynaPoly_GetActor(&play->colCtx, this->actor.floorBgId);

    if (dynaPolyActor != NULL && dynaPolyActor->actor.id == ACTOR_EN_BOX) {
        if (*speedXZ != 0.0f) {
            *speedXZ *= 1.1f;
        } else {
            *speedXZ = 1.0f;
        }
    }
    if (*speedXZ >= (kREG(27) * 0.01f) + 3.0f) {
        *speedXZ *= (kREG(22) * 0.01f) + 0.98f;
    } else {
        *speedXZ = 0.0f;
    }
}

void func_80AEDFF4(EnRu1* this, PlayState* play) {
    func_80AEDB30(this, play);
    func_80AEDEF4(this, play);
    Actor_MoveForward(&this->actor);
}

void func_80AEE02C(EnRu1* this) {
    this->actor.velocity.x = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.velocity.z = 0.0f;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.minVelocityY = 0.0f;
}

void func_80AEE050(EnRu1* this) {
    s32 pad;
    f32 sp28;
    f32 sp24;
    f32 temp_f10;
    EnRu1* thisx = this; // necessary to match

    if (this->unk_350 == 0) {
        if ((this->actor.minVelocityY == 0.0f) && (this->actor.speedXZ == 0.0f)) {
            this->unk_350 = 1;
            func_80AEE02C(this);
            this->unk_35C = 0;
            this->unk_358 = (this->actor.yDistToWater - 10.0f) * 0.5f;
            this->unk_354 = this->actor.world.pos.y + thisx->unk_358; // thisx only used here
        } else {
            this->actor.gravity = 0.0f;
            this->actor.minVelocityY *= 0.2f;
            this->actor.velocity.y *= 0.2f;
            if (this->actor.minVelocityY >= -0.1f) {
                this->actor.minVelocityY = 0.0f;
                this->actor.velocity.y = 0.0f;
            }
            this->actor.speedXZ *= 0.5f;
            if (this->actor.speedXZ <= 0.1f) {
                this->actor.speedXZ = 0.0f;
            }
            this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * this->actor.speedXZ;
            this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * this->actor.speedXZ;
            func_8002D7EC(&this->actor);
        }
    } else {
        if (this->unk_350 == 1) {
            if (this->unk_358 <= 1.0f) {
                func_80AEE02C(this);
                this->unk_350 = 2;
                this->unk_360 = 0.0f;
            } else {
                sp28 = this->unk_358;
                sp24 = this->unk_354;
                temp_f10 = Math_CosS(this->unk_35C) * -sp28;
                this->actor.world.pos.y = temp_f10 + sp24;
                this->unk_35C += 0x3E8;
                this->unk_358 *= 0.95f;
            }
        } else {
            this->unk_360 += 1.0f;
            if (this->unk_360 > 0.0f) {
                this->unk_350 = 3;
            }
        }
    }
}

s32 func_80AEE264(EnRu1* this, PlayState* play) {
    if (!Actor_ProcessTalkRequest(&this->actor, play)) {
        this->actor.flags |= ACTOR_FLAG_0 | ACTOR_FLAG_3;
        if (GET_INFTABLE(INFTABLE_RUTO_AFTER_CARRY)) {
            this->actor.textId = 0x404E;
            func_8002F2F4(&this->actor, play);
        } else if (GET_INFTABLE(INFTABLE_RUTO_BEFORE_CARRY)) {
            this->actor.textId = 0x404D;
            func_8002F2F4(&this->actor, play);
        } else {
            this->actor.textId = 0x404C;
            func_8002F2F4(&this->actor, play);
        }
        return false;
    }
    return true;
}

void EnRu1_SetSpawnNearBlueSwitchFlag(EnRu1* this, PlayState* play) {
    DynaPolyActor* dynaPolyActor;
    s32 floorBgId;

    if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actor.floorBgId != BGCHECK_SCENE)) {
        floorBgId = this->actor.floorBgId;
        dynaPolyActor = DynaPoly_GetActor(&play->colCtx, floorBgId);
        if ((dynaPolyActor != NULL) && (dynaPolyActor->actor.id == ACTOR_BG_BDAN_SWITCH)) {
            if (((dynaPolyActor->actor.params >> 8) & 0x3F) == 0x38) {
                SET_INFTABLE(INFTABLE_RUTO_HOLDING_SWITCH_38);
                return;
            }
        }
    }
    CLEAR_INFTABLE(INFTABLE_RUTO_HOLDING_SWITCH_38);
}

s32 func_80AEE394(EnRu1* this, PlayState* play) {
    s32 pad[2];
    CollisionContext* colCtx;
    DynaPolyActor* dynaPolyActor;
    s32 floorBgId;

    if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && this->actor.floorBgId != BGCHECK_SCENE) {
        colCtx = &play->colCtx;
        floorBgId = this->actor.floorBgId; // necessary match, can't move this out of this block unfortunately
        dynaPolyActor = DynaPoly_GetActor(colCtx, floorBgId);
        if (dynaPolyActor != NULL && dynaPolyActor->actor.id == ACTOR_BG_BDAN_OBJECTS &&
            dynaPolyActor->actor.params == 0 && !Player_InCsMode(play) && play->msgCtx.msgLength == 0) {
            func_80AEE02C(this);
            play->csCtx.segment = &sRutoGettingSapphireCS;
            gSaveContext.cutsceneTrigger = 1;
            this->action = RUTO_ACTION_36;
            this->drawConfig = RUTO_DRAW_NOTHING;
            this->bgBdanObjectsActor = (BgBdanObjects*)dynaPolyActor;
            this->actor.shape.shadowAlpha = 0;
            return true;
        }
    }
    return false;
}

void func_80AEE488(EnRu1* this, PlayState* play) {
    s8 curRoomNum;

    if (Actor_HasParent(&this->actor, play)) {
        curRoomNum = play->roomCtx.curRoom.num;
        this->roomNum3 = curRoomNum;
        this->action = RUTO_ACTION_SIT_AND_SQUIRM;
        func_80AED520(this, play);
    } else if (!func_80AEE394(this, play) && !(this->actor.bgCheckFlags & BGCHECKFLAG_GROUND)) {
        this->actor.minVelocityY = -((kREG(24) * 0.01f) + 6.8f);
        this->actor.gravity = -((kREG(23) * 0.01f) + 1.3f);
        this->action = RUTO_ACTION_28;
    }
}

void func_80AEE568(EnRu1* this, PlayState* play) {
    if (!func_80AEE394(this, play)) {
        if ((this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) && (this->actor.speedXZ == 0.0f) &&
            (this->actor.minVelocityY == 0.0f)) {
            func_80AEE02C(this);
            func_8002F580(&this->actor, play);
            this->action = RUTO_ACTION_27;
            func_80AEADD8(this);
        } else if (this->actor.yDistToWater > 0.0f) {
            this->action = RUTO_ACTION_29;
            this->unk_350 = 0;
        }
    }
}

void func_80AEE628(EnRu1* this, PlayState* play) {
    s32 pad[2];
    s8 curRoomNum = play->roomCtx.curRoom.num;

    if (EnRu1_IsCsStateIdle(play)) {
        Animation_Change(&this->skelAnime, &gRutoChildSittingAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildSittingAnim), ANIMMODE_LOOP, -8.0f);
        SET_INFTABLE(INFTABLE_RUTO_BEFORE_RUTO_HAS_SAPPHIRE);
        this->action = RUTO_ACTION_SIT_AND_SQUIRM;
    }
    this->roomNum3 = curRoomNum;
}

s32 func_80AEE6D0(EnRu1* this, PlayState* play) {
    s32 pad;
    s8 curRoomNum = play->roomCtx.curRoom.num;

    if (!GET_INFTABLE(INFTABLE_RUTO_BEFORE_RUTO_HAS_SAPPHIRE) && (EnRu1_FindSapphireActor(play) != NULL)) {
        if (!Player_InCsMode(play)) {
            Animation_Change(&this->skelAnime, &gRutoChildSeesSapphireAnim, 1.0f, 0,
                             Animation_GetLastFrame(&gRutoChildSquirmAnim), ANIMMODE_LOOP, -8.0f);
            func_80AED600(this);
            this->action = RUTO_ACTION_34;
            this->unk_26C = 0.0f;
            play->csCtx.segment = &sRutoSeeingSapphireCS;
            gSaveContext.cutsceneTrigger = 1;
        }
        this->roomNum3 = curRoomNum;
        return true;
    }
    this->roomNum3 = curRoomNum;
    return false;
}

void EnRu1_SittingIdleAnimation(EnRu1* this, PlayState* play) {
    f32 frameCount;
    s32 pad[13];
    Player* player;
    f32* sitAnimChangeTimer = &this->sitAnimChangeTimer;

    if (Actor_HasNoParent(&this->actor, play)) {
        frameCount = Animation_GetLastFrame(&gRutoChildSittingAnim);
        Animation_Change(&this->skelAnime, &gRutoChildSittingAnim, 1.0f, 0, frameCount, ANIMMODE_LOOP, -8.0f);
        func_80AED6DC(this, play);
        this->actor.speedXZ *= (kREG(25) * 0.01f) + 1.0f;
        this->actor.velocity.y *= (kREG(26) * 0.01f) + 1.0f;
        this->actor.minVelocityY = -((kREG(24) * 0.01f) + 6.8f);
        this->actor.gravity = -((kREG(23) * 0.01f) + 1.3f);
        EnRu1_PlayThrowingSound(this);
        this->action = RUTO_ACTION_28;
        *sitAnimChangeTimer = 0.0f;
        return;
    }

    if (func_80AEE6D0(this, play)) {
        *sitAnimChangeTimer = 0.0f;
        return;
    }

    player = GET_PLAYER(play);
    if (player->stateFlags2 & PLAYER_STATE2_28) {
        this->sitAnimChangeTimer += 1.0f;
        if (this->action != RUTO_ACTION_SIT_IDLE) {
            if (*sitAnimChangeTimer > 30.0f) {
                if (Rand_S16Offset(0, 3) == 0) {
                    frameCount = Animation_GetLastFrame(&gRutoChildSquirmAnim);
                    Animation_Change(&this->skelAnime, &gRutoChildSquirmAnim, 1.0f, 0, frameCount, ANIMMODE_LOOP,
                                     -8.0f);
                    EnRu1_PlayRutoSquirmSound(this);
                    this->action = RUTO_ACTION_SIT_IDLE;
                }
                *sitAnimChangeTimer = 0.0f;
            }
        } else {
            if (*sitAnimChangeTimer > 50.0f) {
                frameCount = Animation_GetLastFrame(&gRutoChildSittingAnim);
                Animation_Change(&this->skelAnime, &gRutoChildSittingAnim, 1.0f, 0, frameCount, ANIMMODE_LOOP, -8.0f);
                this->action = RUTO_ACTION_SIT_AND_SQUIRM;
                *sitAnimChangeTimer = 0.0f;
            }
        }
    } else {
        frameCount = Animation_GetLastFrame(&gRutoChildSittingAnim);
        Animation_Change(&this->skelAnime, &gRutoChildSittingAnim, 1.0f, 0, frameCount, ANIMMODE_LOOP, -8.0f);
        *sitAnimChangeTimer = 0.0f;
    }
}

s32 func_80AEEAC8(EnRu1* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        func_80AEE02C(this);
        func_8002F580(&this->actor, play);
        this->action = RUTO_ACTION_27;
        func_80AEADD8(this);
        return true;
    }
    return false;
}

void func_80AEEB24(EnRu1* this, PlayState* play) {
    if ((func_80AEEAC8(this, play) == 0) && (this->unk_350 == 3)) {
        this->action = RUTO_ACTION_30;
        func_80AEE02C(this);
        this->actor.gravity = -0.1f;
        this->actor.minVelocityY = -((kREG(18) * 0.1f) + 0.7f);
    }
}

void func_80AEEBB4(EnRu1* this, PlayState* play) {
    func_8002F580(&this->actor, play);
}

void func_80AEEBD4(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAC54(this, play);
    func_80AEAECC(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEEBB4(this, play);
    func_80AEE488(this, play);
    func_80AED624(this, play);
    func_80AEDAE0(this, play);
}

void func_80AEEC5C(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEACDC(this, play);
    func_80AEAECC(this, play);
    EnRu1_SetSpawnNearBlueSwitchFlag(this, play);
    func_80AEDFF4(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEE568(this, play);
    func_80AED624(this, play);
    func_80AEDAE0(this, play);
}

void func_80AEECF0(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAECC(this, play);
    func_80AEE050(this);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEEB24(this, play);
    func_80AED624(this, play);
}

void func_80AEED58(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAECC(this, play);
    Actor_MoveForward(&this->actor);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEEAC8(this, play);
    func_80AED624(this, play);
    func_80AEDAE0(this, play);
}

void EnRu1_SetupSitAndSquirm(EnRu1* this, PlayState* play) {
    func_80AED8DC(this);
    EnRu1_UpdateSkelAnime(this);
    func_80AEAECC(this, play);
    EnRu1_SetSpawnNearBlueSwitchFlag(this, play);
    EnRu1_UpdateEyes(this);
    EnRu1_SetRoom2SpawnFlag(play);
    EnRu1_SittingIdleAnimation(this, play);
}

void EnRu1_SetupSitIdle(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    EnRu1_UpdateSkelAnime(this);
    func_80AEAECC(this, play);
    EnRu1_SetSpawnNearBlueSwitchFlag(this, play);
    EnRu1_UpdateEyes(this);
    EnRu1_SetRoom2SpawnFlag(play);
    EnRu1_SittingIdleAnimation(this, play);
}

void func_80AEEE9C(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAECC(this, play);
    func_80AEDFF4(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AED738(this, play);
    func_80AED624(this, play);
}

void func_80AEEF08(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    EnRu1_UpdateSkelAnime(this);
    func_80AEAECC(this, play);
    EnRu1_UpdateEyes(this);
    func_80AEE628(this, play);
}

void func_80AEEF5C(EnRu1* this, PlayState* play) {
}

void func_80AEEF68(EnRu1* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 something;

    this->unk_374.unk_18 = player->actor.world.pos;
    this->unk_374.unk_14 = kREG(16) - 3.0f;
    something = kREG(17) + 0xC;
    func_80034A14(&this->actor, &this->unk_374, something, 2);
}

void func_80AEEFEC(EnRu1* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 something;

    this->unk_374.unk_18 = player->actor.world.pos;
    this->unk_374.unk_14 = kREG(16) - 3.0f;
    something = kREG(17) + 0xC;
    func_80034A14(&this->actor, &this->unk_374, something, 4);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_80AEF080(EnRu1* this) {
    if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
        func_80078914(&this->actor.projectedPos, NA_SE_EV_LAND_DIRT);
    }
}

s32 func_80AEF0BC(EnRu1* this, PlayState* play) {
    s32 frameCount;

    if (GET_INFTABLE(INFTABLE_RUTO_BEFORE_CARRY)) {
        frameCount = Animation_GetLastFrame(&gRutoChildSitAnim);
        Animation_Change(&this->skelAnime, &gRutoChildSitAnim, 1.0f, 0, frameCount, ANIMMODE_ONCE, -8.0f);
        play->msgCtx.msgMode = MSGMODE_PAUSED;
        this->action = RUTO_ACTION_26;
        this->actor.flags &= ~(ACTOR_FLAG_0 | ACTOR_FLAG_3);
        return true;
    }
    return false;
}

void func_80AEF170(EnRu1* this, PlayState* play, s32 cond) {
    if (cond) {
        this->action = RUTO_ACTION_25;
    }
}

void func_80AEF188(EnRu1* this, PlayState* play) {
    if (func_80AEB174(play) && !func_80AEF0BC(this, play)) {
        Message_CloseTextbox(play);
        SET_INFTABLE(INFTABLE_RUTO_BEFORE_CARRY);
        this->action = RUTO_ACTION_24;
    }
}

void func_80AEF1F0(EnRu1* this, PlayState* play, UNK_TYPE arg2) {
    if (arg2 != 0) {
        Animation_Change(&this->skelAnime, &gRutoChildSittingAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gRutoChildSittingAnim), ANIMMODE_LOOP, 0.0f);
        Message_CloseTextbox(play);
        SET_INFTABLE(INFTABLE_RUTO_AFTER_CARRY);
        func_80AED6DC(this, play);
        func_8002F580(&this->actor, play);
        this->action = RUTO_ACTION_27;
        func_80AEADD8(this);
    }
}

void func_80AEF29C(EnRu1* this, PlayState* play) {
    this->action = RUTO_ACTION_23;
}

void func_80AEF2AC(EnRu1* this, PlayState* play) {
    this->action = RUTO_ACTION_24;
    this->drawConfig = RUTO_DRAW_OPA;
    this->actor.flags |= ACTOR_FLAG_0 | ACTOR_FLAG_3;
}

void func_80AEF2D0(EnRu1* this, PlayState* play) {
    s32 cond;

    func_80AEEF68(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAC10(this, play);
    func_80AEAECC(this, play);
    cond = func_80AEE264(this, play);
    func_80AED624(this, play);
    func_80AEF170(this, play, cond);
}

void func_80AEF354(EnRu1* this, PlayState* play) {
    func_80AEEFEC(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEF188(this, play);
}

void func_80AEF3A8(EnRu1* this, PlayState* play) {
    s32 something;

    func_80AED83C(this);
    something = EnRu1_UpdateSkelAnime(this);
    func_80AEF080(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEF1F0(this, play, something);
}

void func_80AEF40C(EnRu1* this) {
    SkelAnime* skelAnime = &this->skelAnime;

    if (Animation_OnFrame(skelAnime, 2.0f) || Animation_OnFrame(skelAnime, 7.0f) ||
        Animation_OnFrame(skelAnime, 12.0f) || Animation_OnFrame(skelAnime, 18.0f) ||
        Animation_OnFrame(skelAnime, 25.0f) || Animation_OnFrame(skelAnime, 33.0f)) {
        func_80078914(&this->actor.projectedPos, NA_SE_PL_WALK_DIRT);
    }
}

void EnRu1_PlayRutoScreamingSound(EnRu1* this, PlayState* play) {
    SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.projectedPos, 20, NA_SE_VO_RT_FALL);
}

void func_80AEF4E0(EnRu1* this) {
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_LAUGH_0);
    }
}

void EnRu1_SurprisedRutoSound(EnRu1* this) {
    // actually this is the sound when ruto gets thrown
    // but it is used as a "ruto is suprised" sound
    func_80078914(&this->actor.projectedPos, NA_SE_VO_RT_THROW);
}

void EnRu1_SuprisedRutoAnimation(EnRu1* this) {
    if (EnRu1_GetBgBdanObjectsActorCameraSetting(this) == CAM_SET_NORMAL1) {
        EnRu1_SetEyeIndex(this, 3);
        EnRu1_SetMouthIndex(this, 2);
        if (this->skelAnime.mode != 2) {
            EnRu1_ChangeAnimation(this, &gRutoChildShutterAnim, 2, -8.0f, 0);
            EnRu1_SurprisedRutoSound(this);
        }
    }
}

void func_80AEF5B8(EnRu1* this) {
    f32 curFrame;

    if (D_80AF1938 == 0) {
        curFrame = this->skelAnime.curFrame;
        if (curFrame >= 60.0f) {
            EnRu1_SetEyeIndex(this, 3);
            EnRu1_SetMouthIndex(this, 0);
            EnRu1_PlayThrowingSound(this);
            D_80AF1938 = 1;
        }
    }
}

void func_80AEF624(EnRu1* this, PlayState* play) {
    f32 frameCount;
    CsCmdActorAction* csCmdNPCAction;
    CsCmdActorAction* csCmdNPCAction2;
    s16 newRotTmp;

    if (func_80AEAFE0(play, 1, 3)) {
        frameCount = Animation_GetLastFrame(&gRutoChildWalkToAndHoldUpSapphireAnim);
        // this weird part with the redundant variable is necessary to match for some reason
        csCmdNPCAction2 = play->csCtx.npcActions[3];
        csCmdNPCAction = csCmdNPCAction2;
        this->actor.world.pos.x = csCmdNPCAction->startPos.x;
        this->actor.world.pos.y = csCmdNPCAction->startPos.y;
        this->actor.world.pos.z = csCmdNPCAction->startPos.z;
        newRotTmp = csCmdNPCAction->rot.x;
        this->actor.shape.rot.x = newRotTmp;
        this->actor.world.rot.x = newRotTmp;
        newRotTmp = csCmdNPCAction->rot.y;
        this->actor.shape.rot.y = newRotTmp;
        this->actor.world.rot.y = newRotTmp;
        newRotTmp = csCmdNPCAction->rot.z;
        this->actor.shape.rot.z = newRotTmp;
        this->actor.world.rot.z = newRotTmp;
        Animation_Change(&this->skelAnime, &gRutoChildWalkToAndHoldUpSapphireAnim, 1.0f, 0.0f, frameCount,
                         ANIMMODE_ONCE, 0.0f);
        func_80AEB3A4(this, play);
        this->action = RUTO_ACTION_37;
        this->drawConfig = RUTO_DRAW_OPA;
        this->actor.shape.shadowAlpha = 0xFF;
    }
}

void func_80AEF728(EnRu1* this, UNK_TYPE arg1) {
    if (arg1 != 0) {
        Animation_Change(&this->skelAnime, &gRutoChildHoldArmsUpAnim, 1.0f, 0.0f,
                         Animation_GetLastFrame(&gRutoChildHoldArmsUpAnim), ANIMMODE_LOOP, 0.0f);
        func_80AEB3CC(this);
        this->action = RUTO_ACTION_38;
    }
}

void func_80AEF79C(EnRu1* this, PlayState* play) {
    if (func_80AEAFE0(play, 2, 3)) {
        Animation_Change(&this->skelAnime, &gRutoChildBringHandsDownAnim, 1.0f, 0,
                         Animation_GetLastFrame(&gRutoChildBringHandsDownAnim), ANIMMODE_ONCE, -8.0f);
        this->action = RUTO_ACTION_39;
    }
}

void func_80AEF820(EnRu1* this, UNK_TYPE arg1) {
    if (arg1 != 0) {
        Animation_Change(&this->skelAnime, &gRutoChildWait2Anim, 1.0f, 0, Animation_GetLastFrame(&gRutoChildWait2Anim),
                         ANIMMODE_LOOP, -8.0f);
        this->action = RUTO_ACTION_40;
    }
}

void func_80AEF890(EnRu1* this, PlayState* play) {
    s32 pad[2];
    s8 curRoomNum;

    if ((gSaveContext.sceneSetupIndex < 4) && (EnRu1_IsCsStateIdle(play))) {
        curRoomNum = play->roomCtx.curRoom.num;
        SET_INFTABLE(INFTABLE_RUTO_AFTER_RUTO_HAS_SAPPHIRE);
        Flags_SetSwitch(play, EnRu1_GetSwitchFlag(this));
        EnRu1_SetBgBdanObjectsActorCameraSetting(this, CAM_SET_NORMAL0);
        this->action = RUTO_ACTION_42;
        this->actor.room = curRoomNum;
    }
}

void EnRu1_SetupRutoAbductionAnimationAndSound(EnRu1* this, PlayState* play) {
    if (EnRu1_GetBgBdanObjectsActorCameraSetting(this) == CAM_SET_DUNGEON0) {
        this->actor.flags |= ACTOR_FLAG_0 | ACTOR_FLAG_3;
        this->actor.textId = 0x4048; // "kyaa is this an octopus" text
        Message_ContinueTextbox(play, this->actor.textId);
        EnRu1_PlayRutoScreamingSound(this, play);
        this->action = RUTO_ACTION_43;
        this->drawConfig = RUTO_DRAW_NOTHING;
    }
}

void func_80AEF99C(EnRu1* this, PlayState* play) {
    if (func_80AEB1B4(play) != 0) {
        EnRu1_SetBgBdanObjectsActorCameraSetting(this, CAM_SET_DUNGEON1);
        Actor_Kill(&this->actor);
    }
}

void func_80AEF9D8(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEF624(this, play);
    func_80AEB220(this, play);
}

void func_80AEFA2C(EnRu1* this, PlayState* play) {
    s32 something;

    func_80AED83C(this);
    func_80AEB364(this, play);
    func_80AEAECC(this, play);
    something = EnRu1_UpdateSkelAnime(this);
    func_80AEF4E0(this);
    func_80AEF5B8(this);
    func_80AEF40C(this);
    func_80AEF728(this, something);
    func_80AEB220(this, play);
}

void func_80AEFAAC(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAECC(this, play);
    EnRu1_UpdateSkelAnime(this);
    func_80AEF79C(this, play);
    func_80AEB220(this, play);
}

void func_80AEFB04(EnRu1* this, PlayState* play) {
    s32 something;

    func_80AED83C(this);
    func_80AEAECC(this, play);
    something = EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEF820(this, something);
    func_80AEB220(this, play);
}

void func_80AEFB68(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAECC(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEF890(this, play);
    func_80AEB220(this, play);
}

void EnRu1_SetupAbductionCS(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEAECC(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    EnRu1_SuprisedRutoAnimation(this);
    EnRu1_SetupRutoAbductionAnimationAndSound(this, play);
}

void func_80AEFC24(EnRu1* this, PlayState* play) {
    func_80AED83C(this);
    func_80AEF99C(this, play);
}

void EnRu1_SetupIdleBeforeBigOctoFight(EnRu1* this, PlayState* play) {
    if (GET_INFTABLE(INFTABLE_RUTO_AFTER_RUTO_HAS_SAPPHIRE) && !GET_INFTABLE(INFTABLE_RUTO_AFTER_RUTO_ABDUCTED)) {
        EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
        this->action = RUTO_ACTION_41;
        this->bgBdanObjectsActor = EnRu1_FindBigOctoPlatformActor(play);
        EnRu1_SetBgBdanObjectsActorCameraSetting(this, CAM_SET_NORMAL0);
        this->actor.flags &= ~(ACTOR_FLAG_0 | ACTOR_FLAG_3);
    } else {
        Actor_Kill(&this->actor);
    }
}

void func_80AEFCE8(EnRu1* this, PlayState* play) {
    this->bgBdanObjectsActor = EnRu1_FindBigOctoPlatformActor(play);
    if (this->bgBdanObjectsActor != NULL) {
        this->action = RUTO_ACTION_42;
        this->drawConfig = RUTO_DRAW_OPA;
        EnRu1_SetBgBdanObjectsActorCameraSetting(this, CAM_SET_NORMAL0);
    }
}

void func_80AEFD38(EnRu1* this, PlayState* play) {
    if (GET_EVENTCHKINF(EVENTCHKINF_37) && LINK_IS_CHILD) {
        EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
        this->actor.flags &= ~ACTOR_FLAG_4;
        this->action = RUTO_ACTION_44;
        this->drawConfig = RUTO_DRAW_OPA;
    } else {
        Actor_Kill(&this->actor);
    }
}

s32 func_80AEFDC0(EnRu1* this, PlayState* play) {
    if (!Actor_ProcessTalkRequest(&this->actor, play)) {
        this->actor.flags |= ACTOR_FLAG_0 | ACTOR_FLAG_3;
        this->actor.textId = Text_GetFaceReaction(play, 0x1F);
        if (this->actor.textId == 0) {
            this->actor.textId = 0x402C;
        }
        func_8002F2F4(&this->actor, play);
        return false;
    }
    return true;
}

s32 func_80AEFE38(EnRu1* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING) {
        this->actor.flags &= ~(ACTOR_FLAG_0 | ACTOR_FLAG_3);
        return true;
    }
    return false;
}

void func_80AEFE84(EnRu1* this, PlayState* play, s32 cond) {
    if (cond) {
        this->action = RUTO_ACTION_45;
    }
}

void func_80AEFE9C(EnRu1* this, PlayState* play) {
    if (func_80AEFE38(this, play)) {
        this->action = RUTO_ACTION_44;
    }
}

void func_80AEFECC(EnRu1* this, PlayState* play) {
    func_80AEEF68(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAC10(this, play);
    func_80AEAECC(this, play);
    func_80AEFE84(this, play, func_80AEFDC0(this, play));
}

void func_80AEFF40(EnRu1* this, PlayState* play) {
    func_80AEEFEC(this, play);
    EnRu1_UpdateSkelAnime(this);
    EnRu1_UpdateEyes(this);
    func_80AEAECC(this, play);
    func_80AEFE9C(this, play);
}

void func_80AEFF94(EnRu1* this, PlayState* play) {
    s8 actorRoom;

    if (GET_INFTABLE(INFTABLE_RUTO_FIRST_MEET) && GET_INFTABLE(INFTABLE_RUTO_HOLDING_SWITCH_38) && !GET_INFTABLE(INFTABLE_RUTO_AFTER_RUTO_HAS_SAPPHIRE) &&
        (!(func_80AEB020(this, play)))) {
        EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
        actorRoom = this->actor.room;
        this->action = RUTO_ACTION_22;
        this->actor.room = -1;
        this->drawConfig = RUTO_DRAW_NOTHING;
        this->roomNum1 = actorRoom;
        this->roomNum3 = actorRoom;
        this->roomNum2 = actorRoom;
        // "Ruto switch set"
        osSyncPrintf("スイッチルトセット!!!!!!!!!!!!!!!!!!!!!!\n");
    } else {
        // "Ruto switch not set"
        osSyncPrintf("スイッチルトセットしない!!!!!!!!!!!!!!!!!!!!!!\n");
        Actor_Kill(&this->actor);
    }
}

void func_80AF0050(EnRu1* this, PlayState* play) {
    EnRu1_ChangeAnimation(this, &gRutoChildWait2Anim, 0, 0, 0);
    this->action = RUTO_ACTION_36;
    this->roomNum1 = this->actor.room;
    this->bgBdanObjectsActor = EnRu1_FindBigOctoPlatformActor(play);
    this->actor.room = -1;
}

void EnRu1_Update(Actor* thisx, PlayState* play) {
    EnRu1* this = (EnRu1*)thisx;

    if (this->action < RUTO_ACTION_00 || this->action >= ARRAY_COUNT(sActionFuncs) || sActionFuncs[this->action] == NULL) {
        // "Main mode is improper!"
        osSyncPrintf(VT_FGCOL(RED) "メインモードがおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
        return;
    }

    sActionFuncs[this->action](this, play);
}

void EnRu1_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnRu1* this = (EnRu1*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gRutoChildSkel, NULL, this->jointTable, this->morphTable, 17);
    func_80AEAD20(&this->actor, play);
    switch (EnRu1_GetParameters(this)) {
        case RUTO_TYPE_WARP:
            EnRu1_SetupBlueWarp(this, play);
            break;
        case RUTO_TYPE_SAPPHIRE_CS:
            EnRu1_SetupSapphireCS(this, play);
            break;
        case RUTO_TYPE_FIRST_TIME_MEET:
            func_80AEC320(this, play); // EnRu1_SetupFirstMeeting
            break;
        case RUTO_TYPE_CARRY:
            EnRu1_SetupCarry(this, play);
            break;
        case RUTO_TYPE_BIG_OCTO_CS:
            EnRu1_SetupIdleBeforeBigOctoFight(this, play);
            break;
        case RUTO_TYPE_UNK5:
            func_80AEFD38(this, play);
            break;
        case RUTO_TYPE_UNK6:
            func_80AEFF94(this, play);
            break;
        case RUTO_TYPE_UNKA:
            func_80AF0050(this, play);
            break;
        default:
            Actor_Kill(&this->actor);
            // "Relevant arge_data = %d unacceptable"
            osSyncPrintf("該当 arge_data = %d 無し\n", EnRu1_GetParameters(this));
            break;
    }
}

void func_80AF0278(EnRu1* this, PlayState* play, s32 limbIndex, Vec3s* rot) {
    Vec3s* vec1 = &this->unk_374.unk_0E;
    Vec3s* vec2 = &this->unk_374.unk_08;

    switch (limbIndex) {
        case RUTO_CHILD_LEFT_UPPER_ARM:
            rot->x += vec1->y;
            rot->y -= vec1->x;
            break;
        case RUTO_CHILD_TORSO:
            rot->x += vec2->y;
            rot->z += vec2->x;
            break;
    }
}

s32 EnRu1_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, void* thisx,
                           Gfx** gfx) {
    EnRu1* this = (EnRu1*)thisx;

    if ((this->preLimbDrawConfig < 0) || (this->preLimbDrawConfig > 0) || (*sPreLimbDrawFuncs[this->preLimbDrawConfig] == NULL)) {
        // "Neck rotation mode is improper!"
        osSyncPrintf(VT_FGCOL(RED) "首回しモードがおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
    } else {
        sPreLimbDrawFuncs[this->preLimbDrawConfig](this, play, limbIndex, rot);
    }
    return false;
}

void EnRu1_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, void* thisx, Gfx** gfx) {
    EnRu1* this = (EnRu1*)thisx;
    Vec3f vec1;
    Vec3f vec2;

    if (limbIndex == RUTO_CHILD_TORSO) {
        vec1 = sMultVec;
        Matrix_MultVec3f(&vec1, &vec2);
        this->actor.focus.pos.x = vec2.x;
        this->actor.focus.pos.y = vec2.y;
        this->actor.focus.pos.z = vec2.z;
        this->actor.focus.rot.x = this->actor.world.rot.x;
        this->actor.focus.rot.y = this->actor.world.rot.y;
        this->actor.focus.rot.z = this->actor.world.rot.z;
    }
}

void EnRu1_DrawNothing(EnRu1* this, PlayState* play) {
}

void EnRu1_DrawOpa(EnRu1* this, PlayState* play) {
    s32 pad[2];
    s16 eyeIndex = this->eyeIndex;
    void* eyeTex = sEyeTextures[eyeIndex];
    s16 mouthIndex = this->mouthIndex;
    SkelAnime* skelAnime = &this->skelAnime;
    void* mouthTex = sMouthTextures[mouthIndex];
    s32 pad1;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_ru1.c", 1282);

    Gfx_SetupDL_25Opa(play->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_OPA_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(mouthTex));
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPSegment(POLY_OPA_DISP++, 0x0C, &D_80116280[2]);

    POLY_OPA_DISP = SkelAnime_DrawFlex(play, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                       EnRu1_OverrideLimbDraw, EnRu1_PostLimbDraw, this, POLY_OPA_DISP);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_ru1.c", 1309);
}

void EnRu1_DrawXlu(EnRu1* this, PlayState* play) {
    s32 pad[2];
    s16 eyeIndex = this->eyeIndex;
    void* eyeTex = sEyeTextures[eyeIndex];
    s16 mouthIndex = this->mouthIndex;
    SkelAnime* skelAnime = &this->skelAnime;
    void* mouthTex = sMouthTextures[mouthIndex];
    s32 pad1;

    OPEN_DISPS(play->state.gfxCtx, "../z_en_ru1.c", 1324);

    Gfx_SetupDL_25Xlu(play->state.gfxCtx);

    gSPSegment(POLY_XLU_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_XLU_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(eyeTex));
    gSPSegment(POLY_XLU_DISP++, 0x09, SEGMENTED_TO_VIRTUAL(mouthTex));
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, this->alpha);
    gSPSegment(POLY_XLU_DISP++, 0x0C, &D_80116280[0]);

    POLY_XLU_DISP = SkelAnime_DrawFlex(play, skelAnime->skeleton, skelAnime->jointTable, skelAnime->dListCount,
                                       EnRu1_OverrideLimbDraw, NULL, this, POLY_XLU_DISP);

    CLOSE_DISPS(play->state.gfxCtx, "../z_en_ru1.c", 1353);
}

void EnRu1_Draw(Actor* thisx, PlayState* play) {
    EnRu1* this = (EnRu1*)thisx;

    if (this->drawConfig < 0 || this->drawConfig >= ARRAY_COUNT(sDrawFuncs) || sDrawFuncs[this->drawConfig] == 0) {
        // "Draw mode is improper!"
        osSyncPrintf(VT_FGCOL(RED) "描画モードがおかしい!!!!!!!!!!!!!!!!!!!!!!!!!\n" VT_RST);
        return;
    }
    sDrawFuncs[this->drawConfig](this, play);
}
