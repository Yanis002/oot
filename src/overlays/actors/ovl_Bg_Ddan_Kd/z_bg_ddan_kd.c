/*
 * File: z_bg_ddan_kd.c
 * Overlay: ovl_Bg_Ddan_Kd
 * Description: Falling stairs in Dodongo's Cavern
 */

#include "z_bg_ddan_kd.h"
#include "objects/object_ddan_objects/object_ddan_objects.h"

#define FLAGS ACTOR_FLAG_4

void BgDdanKd_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDdanKd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDdanKd_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDdanKd_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgDdanKd_CheckForExplosions(BgDdanKd* this, GlobalContext* globalCtx);
void BgDdanKd_LowerStairs(BgDdanKd* this, GlobalContext* globalCtx);
void BgDdanKd_DoNothing(BgDdanKd* this, GlobalContext* globalCtx);

const ActorInit Bg_Ddan_Kd_InitVars = {
    ACTOR_BG_DDAN_KD,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_DDAN_OBJECTS,
    sizeof(BgDdanKd),
    (ActorFunc)BgDdanKd_Init,
    (ActorFunc)BgDdanKd_Destroy,
    (ActorFunc)BgDdanKd_Update,
    (ActorFunc)BgDdanKd_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ALL,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0xFFCFFFFF, 0x00, 0x00 },
        TOUCH_NONE,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 245, 180, -400, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 32767, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 32767, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 32767, ICHAIN_STOP),
};

void BgDdanKd_SetupAction(BgDdanKd* this, BgDdanKdActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void BgDdanKd_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgDdanKd* this = (BgDdanKd*)thisx;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    this->prevExplosive = NULL;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, DPM_PLAYER);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);
    CollisionHeader_GetVirtual(&gDodongoFallingStairsCol, &colHeader);

    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, colHeader);

    if (!Flags_GetSwitch(globalCtx, this->dyna.actor.params)) {
        BgDdanKd_SetupAction(this, BgDdanKd_CheckForExplosions);
    } else {
        this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y - 200.0f - 20.0f;
        BgDdanKd_SetupAction(this, BgDdanKd_DoNothing);
    }
}

void BgDdanKd_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgDdanKd* this = (BgDdanKd*)thisx;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void BgDdanKd_CheckForExplosions(BgDdanKd* this, GlobalContext* globalCtx) {
    Actor* explosive;

    explosive = Actor_GetCollidedExplosive(globalCtx, &this->collider.base);
    if (explosive != NULL) {
        osSyncPrintf("dam    %d\n", this->dyna.actor.colChkInfo.damage);
        explosive->params = 2;
    }

    if ((explosive != NULL) && (this->prevExplosive != NULL) && (explosive != this->prevExplosive) &&
        (Math_Vec3f_DistXZ(&this->prevExplosivePos, &explosive->world.pos) > 80.0f)) {
        BgDdanKd_SetupAction(this, BgDdanKd_LowerStairs);
        OnePointCutscene_Init(globalCtx, 3050, 999, &this->dyna.actor, CAM_ID_MAIN);
    } else {
        if (this->timer != 0) {
            this->timer--;
        } else {
            this->prevExplosive = explosive;
            if (explosive != NULL) {
                this->timer = 13;
                this->prevExplosivePos = explosive->world.pos;
            }
        }
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void BgDdanKd_LowerStairs(BgDdanKd* this, GlobalContext* globalCtx) {
    static Vec3f velocity = { 0.0f, 5.0f, 0.0f };
    static Vec3f accel = { 0.0f, -0.45f, 0.0f };
    Vec3f pos1;
    Vec3f pos2;
    f32 effectStrength;

    Math_SmoothStepToF(&this->dyna.actor.speedXZ, 4.0f, 0.5f, 0.025f, 0.0f);
    func_800AA000(500.0f, 0x78, 0x14, 0xA);

    if (Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y - 200.0f - 20.0f, 0.075f,
                           this->dyna.actor.speedXZ, 0.0075f) == 0.0f) {
        Flags_SetSwitch(globalCtx, this->dyna.actor.params);
        BgDdanKd_SetupAction(this, BgDdanKd_DoNothing);
    } else {
        effectStrength =
            (this->dyna.actor.prevPos.y - this->dyna.actor.world.pos.y) + (this->dyna.actor.speedXZ * 0.25f);

        if (globalCtx->state.frames & 1) {
            pos1 = pos2 = this->dyna.actor.world.pos;

            if (globalCtx->state.frames & 2) {
                pos1.z += 210.0f + Rand_ZeroOne() * 230.0f;
                pos2.z += 210.0f + Rand_ZeroOne() * 230.0f;
            } else {
                pos1.z += 330.0f + Rand_ZeroOne() * 240.0f;
                pos2.z += 330.0f + Rand_ZeroOne() * 240.0f;
            }
            pos1.x += 80.0f + Rand_ZeroOne() * 10.0f;
            pos2.x -= 80.0f + Rand_ZeroOne() * 10.0f;
            pos1.y = this->dyna.actor.floorHeight + 20.0f + Rand_ZeroOne();
            pos2.y = this->dyna.actor.floorHeight + 20.0f + Rand_ZeroOne();

            func_80033480(globalCtx, &pos1, 20.0f, 1, effectStrength * 135.0f, 60, 1);
            func_80033480(globalCtx, &pos2, 20.0f, 1, effectStrength * 135.0f, 60, 1);

            velocity.x = Rand_CenteredFloat(3.0f);
            velocity.z = Rand_CenteredFloat(3.0f);

            func_8003555C(globalCtx, &pos1, &velocity, &accel);
            func_8003555C(globalCtx, &pos2, &velocity, &accel);

            pos1 = this->dyna.actor.world.pos;
            pos1.z += 560.0f + Rand_ZeroOne() * 5.0f;
            pos1.x += (Rand_ZeroOne() - 0.5f) * 160.0f;
            pos1.y = Rand_ZeroOne() * 3.0f + (this->dyna.actor.floorHeight + 20.0f);

            func_80033480(globalCtx, &pos1, 20.0f, 1, effectStrength * 135.0f, 60, 1);
            func_8003555C(globalCtx, &pos1, &velocity, &accel);
        }
        Camera_AddQuake(&globalCtx->mainCamera, 0, effectStrength * 0.6f, 3);
        Audio_PlaySoundGeneral(NA_SE_EV_PILLAR_SINK - SFX_FLAG, &this->dyna.actor.projectedPos, 4,
                               &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
    }
}

void BgDdanKd_DoNothing(BgDdanKd* this, GlobalContext* globalCtx) {
}

void BgDdanKd_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgDdanKd* this = (BgDdanKd*)thisx;

    this->actionFunc(this, globalCtx);
}

void BgDdanKd_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, gDodongoFallingStairsDL);
}
