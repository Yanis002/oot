/*
Z_BG_POISONED_WATER - VERSION 1.0

****** DOCUMENTATION ******
ACTOR ID: 0x1
OBJECT ID: 0x4

PARAMETERS:
0000 0000 0011 1111 - Switch Flag       - 0x003F, ``params & 0x3F``
0000 0001 1100 0000 - Default Color Array Index - 0x01C0, ``(params >> 6) & 0x7``
0000 1110 0000 0000 - Size              - 0x0E00, ``(params >> 9) & 0x3``
1111 0000 0000 0000 - Amount of Damages - 0xF000, ``(params >> 12) & 0xF`` - 1 for 1/4 hearts

Z-ROTATION:
0000 0000 0000 1111 - Frequency (base frequency) - 0x000F, ``rot.z & 0x000F`` - 1 for 1 second
0000 0000 1111 0000 - Divisor (increases speed)  - 0x00F0, ``rot.z & 0x00F0`` - 1 for 1 sec, 2 for 0.5 secs, ...
0000 0001 0000 0000 - Mode: Poison to Heal if Switch Flag's set - ``(rot.z >> 8) & 0x1`` - 0: disable heal mode, 1: enable heal mode
0000 1110 0000 0000 - Healing Water Color Index - ``(rot.z >> 9) & 0x7``

****** EXAMPLE OF USAGE ******
  { Actor ID,                 X,    Y,   Z,  rX,  rY,   rZ, Params },
``{ ACTOR_BG_POISONED_WATER, -3, -125, 137, 0x0, 0x0, 0x31, 0x1501 },``

--- Parameters: 0x1501 = 0001 0101 0000 0001 ---
Switch Flag: 1
Default Color Array Index: 4
Size: 2
Amount of Damages: 1 (corresponds to 1/4 hearts)

--- Z-Rotation: 0x0031 = 0000 0000 0011 0001 ---
Frequency (base frequency): 1 (corresponds to 1 second)
Divisor (increases speed): 1 (keep the current frequency of damage dealing)
Mode: Poison Only
Healing Water Color Index: 0

****** ADDITIONNAL INFORMATIONS ******
-> If you choose the poison only mode: Healing Water Color Index and Switch Flag not used
-> The divisor bits are only meant to increase the frequency, set it to 1 if you need to increase the frequency
-> In this context "Frequency" means how much time do you want between two damage dealt to the Player
-> If you deal a positive amount of damages it will heal Link
-> poisonColors[] & healColors[] are the same but that's intended to allow more customisation
-> Contact Yanis on the Hylian Modding Discord if you have any issues or questions
*/

#include "z_bg_poisoned_water.h"
#include "objects/object_poisoned_water/object_poisoned_water.h"

#define FLAGS (ACTOR_FLAG_4 | ACTOR_FLAG_5)

void BgPoisonedWater_Init(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_Update(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_Draw(Actor* thisx, GlobalContext* globalCtx);
void BgPoisonedWater_SetPrimColor(Actor* thisx, GlobalContext* globalCtx, Gfx* gfx);
void BgPoisonedWater_SetAlpha(Actor* thisx, GlobalContext* globalCtx, Color_RGB8 color, Color_RGB8 colorToSet);

const ActorInit Bg_Poisoned_Water_InitVars = {
    ACTOR_BG_POISONED_WATER,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_POISONED_WATER,
    sizeof(BgPoisonedWater),
    (ActorFunc)BgPoisonedWater_Init,
    (ActorFunc)BgPoisonedWater_Destroy,
    (ActorFunc)BgPoisonedWater_Update,
    (ActorFunc)BgPoisonedWater_Draw,
};

static Color_RGB8 poisonColors[] = {
    {128,   0,      0},       // red
    {0,     128,    255},     // blue
    {0,     128,    0},       // green
    {128,   128,    0},       // yellow
    {255,   128,    0},       // orange
    {128,    0,     255},     // purple
    {128,   64,     0},       // brown
};

static Color_RGB8 healColors[] = {
    {128,   0,      0},       // red
    {0,     128,    255},     // blue
    {0,     128,    0},       // green
    {128,   128,    0},       // yellow
    {255,   128,    0},       // orange
    {128,    0,     255},     // purple
    {128,   64,     0},       // brown
};

void BgPoisonedWater_Init(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    s16 params = this->actor.params;
    f32* ySurface = &this->actor.home.pos.y;
    f32 x1, z1, xLen, zLen;

    osSyncPrintf("---- BG_POISONED_WATER INIT: START! ----\n");

    this->size = ((params >> 9) & 0x7);
    this->damageAmount = -(((params >> 12) & 0xF) * 4);
    this->switchFlag = (params & 0x3F);
    this->poisonColorIndex = (((params >> 6) & 0x7) >= ARRAY_COUNT(poisonColors)) ? 0 : ((params >> 6) & 0x7);
    this->healColorIndex = (((this->actor.world.rot.z >> 9) & 0x7) >= ARRAY_COUNT(healColors)) ? 0 : ((this->actor.world.rot.z >> 9) & 0x7);
    this->rgb = GET_POISON_COLOR(this);
    this->timer = GET_TIMER(this);
    this->alpha = 32;
    this->actor.shape.rot.z = 0;

    WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, this->actor.home.pos.x, this->actor.home.pos.z,
                            ySurface, &this->waterBox);

    // Position of each corner of the WaterBox to poison
    // Y doesn't matter at all since we're checking if the Player interacts with a waterbox
    x1 = (f32)this->waterBox->xMin;
    z1 = (f32)this->waterBox->zMin;
    xLen = (f32)this->waterBox->xLength;
    zLen = (f32)this->waterBox->zLength;

    this->pos1.x = this->pos3.x = x1;
    this->pos1.z = this->pos2.z = z1;
    this->pos2.x = this->pos4.x = (x1 + xLen);
    this->pos3.z = this->pos4.z = (z1 + zLen);
    this->pos1.y = this->pos2.y = this->pos3.y = this->pos4.y = 0.0f;

    osSyncPrintf(VT_FGCOL(YELLOW) "Params: 0x%hX\nSize: %d\nDamage Amount: %d\nFlag: %d\nTimer: %d\nDivisor: %d\n",
        params, this->size, this->damageAmount, this->switchFlag, this->timer, GET_DIVISOR(this));

    osSyncPrintf("Colors: %d, %d, %d\n", poisonColors[this->poisonColorIndex].r, poisonColors[this->poisonColorIndex].g, poisonColors[this->poisonColorIndex].b);

    if (this->size != 0) {
        Actor_SetScale(&this->actor, (this->size * 0.25));
    }

    osSyncPrintf(VT_FGCOL(WHITE) "---- BG_POISONED_WATER INIT: END! ----\n");

    // if the actor is not in a waterbox bounds, kill it
    if (this->waterBox == NULL){
        osSyncPrintf(VT_FGCOL(RED) "ERROR: WaterBox not found!\n" VT_FGCOL(WHITE));
        Actor_Kill(&this->actor);
    }
}

void BgPoisonedWater_Destroy(Actor* thisx, GlobalContext* globalCtx){
}

void BgPoisonedWater_Update(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    Player* player = GET_PLAYER(globalCtx);

    // update the damage amount (negative: decreases health, positive: increases health)
    if (GET_SWITCH_FLAG(globalCtx, this)){
        if ((this->damageAmount < 0)) this->damageAmount = -this->damageAmount;

        // if the health is full stop code execution here
        if (gSaveContext.health == gSaveContext.healthCapacity) return;

        if (this->timer > 0) this->timer--;
    } else if ((this->damageAmount > 0)) this->damageAmount = -this->damageAmount;

    // if the Player is in the WaterBox bounds and the Player interacts with a waterbox and not under invincibility timer
    if (GET_POS(player->actor.world.pos.x, player->actor.world.pos.z, this) && INTERACTS_WITH_WATERBOX(player->actor) &&
        ((this->timer == 0) || ((player->invincibilityTimer == 0) && !GET_SWITCH_FLAG(globalCtx, this)))){
    
        // deals damages, if switch flag is set heals player
        globalCtx->damagePlayer(globalCtx, this->damageAmount);

        // play damage sound
        if (this->damageAmount < 0){
            // make link invincible and red flashing effect
            player->invincibilityTimer = this->timer;

            if (!LINK_IS_ADULT) func_8002F7DC(&player->actor, NA_SE_VO_LI_DAMAGE_S_KID);
            else func_8002F7DC(&player->actor, NA_SE_VO_LI_DAMAGE_S);
        }

        this->timer = GET_TIMER(this);
    }
}

void BgPoisonedWater_SetAlpha(Actor* thisx, GlobalContext* globalCtx, Color_RGB8 curColor, Color_RGB8 colorToSet){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;

    if (this->rgb.r == curColor.r &&
        this->rgb.g == curColor.g &&
        this->rgb.b == curColor.b){
            if (this->alpha > 0) {
                this->alpha--;
                func_8002F948(&this->actor, NA_SE_EV_WATER_LEVEL_DOWN);
            }
            else this->rgb = colorToSet;
    } else {
        if (this->alpha < 32) {
            this->alpha++;
            if ((((this->alpha + 1) * 4) == 128) && Audio_IsSfxPlaying(NA_SE_EV_WATER_LEVEL_DOWN)) {
                Audio_StopSfxById(NA_SE_EV_WATER_LEVEL_DOWN);
                func_8002F7DC(&GET_PLAYER(globalCtx)->actor, NA_SE_SY_TRE_BOX_APPEAR);
            }
        }
    }
}

void BgPoisonedWater_SetPrimColor(Actor* thisx, GlobalContext* globalCtx, Gfx* gfx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;

    if (MODE_HEAL(this)) {
        if (GET_SWITCH_FLAG(globalCtx, this)) BgPoisonedWater_SetAlpha(thisx, globalCtx, GET_POISON_COLOR(this), GET_HEAL_COLOR(this));
        else BgPoisonedWater_SetAlpha(thisx, globalCtx, GET_HEAL_COLOR(this), GET_POISON_COLOR(this));
    } else this->alpha = 32;

    gDPSetPrimColor(gfx, 0, 0, this->rgb.r, this->rgb.g, this->rgb.b, (this->alpha * 4));
}

void BgPoisonedWater_Draw(Actor* thisx, GlobalContext* globalCtx){
    BgPoisonedWater* this = (BgPoisonedWater*)thisx;
    s32 gameplayFrames;

    OPEN_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);

    gameplayFrames = globalCtx->gameplayFrames;
    gSPSegment(POLY_XLU_DISP++, 0x09,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 127 - (gameplayFrames % 128), (gameplayFrames * 1) % 128,
                                32, 32, 1, gameplayFrames % 128, (gameplayFrames * 1) % 128, 32, 32));
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx, __FILE__, __LINE__), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    BgPoisonedWater_SetPrimColor(thisx, globalCtx, POLY_XLU_DISP++);
    gSPDisplayList(POLY_XLU_DISP++, gColorFilterDL);
    gSPDisplayList(POLY_XLU_DISP++, gPoisonedWaterDL);

    CLOSE_DISPS(globalCtx->state.gfxCtx, __FILE__, __LINE__);
}