/*
 * File: z_oceff_wipe.c
 * Overlay: ovl_Oceff_Wipe
 * Description: Zelda's Lullaby and Song of Time Ocarina Effect
 */

#include "z_oceff_wipe.h"
#include "vt.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe*)thisx)

void OceffWipe_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Oceff_Wipe_InitVars = {
    ACTOR_OCEFF_WIPE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_GAMEPLAY_KEEP,
    sizeof(OceffWipe),
    (ActorFunc)OceffWipe_Init,
    (ActorFunc)OceffWipe_Destroy,
    (ActorFunc)OceffWipe_Update,
    (ActorFunc)OceffWipe_Draw,
};

void OceffWipe_Init(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe* this = THIS;

    Actor_SetScale(&this->actor, 0.1f);
    this->timer = 0;
    this->actor.world.pos = GET_ACTIVE_CAM(globalCtx)->eye;
    osSyncPrintf(VT_FGCOL(CYAN) " WIPE arg_data = %d\n" VT_RST, this->actor.params);

    //Project-A
    this->counter2 = 0;
    this->boolWipe2 = 0;
}

void OceffWipe_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    func_800876C8(globalCtx);
    if (gSaveContext.nayrusLoveTimer != 0) {
        player->stateFlags3 |= 0x40;
    }
}

void OceffWipe_Update(Actor* thisx, GlobalContext* globalCtx) {
    OceffWipe* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    //Project-A
    u8 changedValue;

    if(this->actor.params == OCEFF_WIPE_SOT2) changedValue = 40;
    else changedValue = 100;

    this->actor.world.pos = GET_ACTIVE_CAM(globalCtx)->eye;

    if(this->actor.params == OCEFF_WIPE_SOT2){
        if(this->counter2 < 35) this->counter2++;
        else if(!(this->boolWipe2)){
            D_801614B0.a ^= 1;
            player->scrollChange = !player->scrollChange;
            this->boolWipe2 = 1;
        }

        if(this->counter2 == 5) Audio_PlayActorSound2(&this->actor, NA_SE_EV_RED_EYE);
    }

    if (this->counter < changedValue) this->counter++; 
    else Actor_Kill(&this->actor);
}

#include "overlays/ovl_Oceff_Wipe/ovl_Oceff_Wipe.c"

static u8 sAlphaIndices[] = {
    0x01, 0x10, 0x22, 0x01, 0x20, 0x12, 0x01, 0x20, 0x12, 0x01,
    0x10, 0x22, 0x01, 0x20, 0x12, 0x01, 0x12, 0x21, 0x01, 0x02,
};

void OceffWipe_Draw(Actor* thisx, GlobalContext* globalCtx) {
    u32 scroll = globalCtx->state.frames & 0xFF;
    OceffWipe* this = THIS;
    f32 z;
    s32 pad;
    u8 alphaTable[3];
    s32 i;
    Vec3f eye;
    Vtx* vtxPtr;
    Vec3f vec;

    /* Project-A */ 
    u16 multiplicateur = 0;
    s8 val1, val2, val3, val4;

    if(this->actor.params == OCEFF_WIPE_SOT2){
         multiplicateur = 1200;
         val1 = 30;
         val2 = 0x28;
         val3 = 16;
         val4 = 24;
    }
    else {
        multiplicateur = 1400;
        val1 = 80;
        val2 = 0x64;
        val3 = 8;
        val4 = 12;
    }
    /*-----------*/
    
    //position
    eye = GET_ACTIVE_CAM(globalCtx)->eye;
    Camera_GetSkyboxOffset(&vec, GET_ACTIVE_CAM(globalCtx));

    OPEN_DISPS(globalCtx->state.gfxCtx, "../z_oceff_wipe.c", 346);

    //wormhole interior circle size (sort of)
    if (this->counter < 32) {
        z = Math_SinS(this->counter << 9) * multiplicateur;
    } else {
        z = multiplicateur; //1400 both
    }

    //transparency stuff
    if (this->counter >= val1) { //80
        alphaTable[0] = 0;
        alphaTable[1] = (val2 - this->counter) * val3; //100, 8
        alphaTable[2] = (val2 - this->counter) * val4; //100, 12
    } else {
        alphaTable[0] = 0;
        alphaTable[1] = 0xA0;
        alphaTable[2] = 0xFF;
    }

    //fade out
    for (i = 0; i < 20; i++) {
        vtxPtr = sFrustumVtx;
        vtxPtr[i * 2 + 0].v.cn[3] = alphaTable[(sAlphaIndices[i] & 0xF0) >> 4];
        vtxPtr[i * 2 + 1].v.cn[3] = alphaTable[sAlphaIndices[i] & 0xF];
    }

    //???
    func_80093D84(globalCtx->state.gfxCtx);

    //position
    Matrix_Translate(eye.x + vec.x, eye.y + vec.y, eye.z + vec.z, MTXMODE_NEW);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    func_800D1FD4(&globalCtx->billboardMtxF);
    Matrix_Translate(0.0f, 0.0f, -z, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, "../z_oceff_wipe.c", 375),
              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    //set proper color
    if (this->actor.params != OCEFF_WIPE_ZL) {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 170, 255, 255, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 150, 255, 128);
    } else {
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, 255);
        gDPSetEnvColor(POLY_XLU_DISP++, 100, 0, 255, 128);
    }

    gSPDisplayList(POLY_XLU_DISP++, sMaterialDL);
    gSPDisplayList(POLY_XLU_DISP++, Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0 - scroll, scroll * (-2), 32, 32, 1,
                                                     0 - scroll, scroll * (-2), 32, 32));
    gSPDisplayList(POLY_XLU_DISP++, sFrustumDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, "../z_oceff_wipe.c", 398);
}
