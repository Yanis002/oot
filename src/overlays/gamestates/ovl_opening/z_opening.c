/*
 * File: z_opening.c
 * Overlay: ovl_opening
 * Description: Initializes the game into the title screen
 */

#include "global.h"

void Opening_SetupTitleScreen(OpeningContext* this) {
    // gSaveContext.gameMode = 1;
    // this->state.running = false;
    // gSaveContext.linkAge = LINK_AGE_ADULT;
    // Sram_InitDebugSave();
    // gSaveContext.cutsceneIndex = 0xFFF3;
    // gSaveContext.sceneSetupIndex = 7;
    // SET_NEXT_GAMESTATE(&this->state, Gameplay_Init, GlobalContext);

    Sram_InitDebugSave();
    gSaveContext.gameMode = 0;

    gSaveContext.unk_13F6 = gSaveContext.magic;
    gSaveContext.magic = 0;
    gSaveContext.unk_13F4 = 0;
    gSaveContext.magicLevel = gSaveContext.magic;

    gSaveContext.linkAge = LINK_AGE_CHILD;
    gSaveContext.dayTime = 0x8000;
    gSaveContext.buttonStatus[4] = BTN_ENABLED;
    gSaveContext.buttonStatus[3] = BTN_ENABLED;
    gSaveContext.buttonStatus[2] = BTN_ENABLED;
    gSaveContext.buttonStatus[1] = BTN_ENABLED;
    gSaveContext.buttonStatus[0] = BTN_ENABLED;
    gSaveContext.unk_13E7 = gSaveContext.unk_13E8 = gSaveContext.unk_13EA = gSaveContext.unk_13EC = 0;
    Audio_QueueSeqCmd(NA_BGM_STOP);
    gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = gSaveContext.entranceIndex = ENTR_DETAILED_PANEL_0_CD;
    gSaveContext.respawnFlag = 0;
    gSaveContext.showTitleCard = false;
    gWeatherMode = 0;
    this->state.running = false;
    SET_NEXT_GAMESTATE(&this->state, Gameplay_Init, GlobalContext);
}

void func_80803C5C(OpeningContext* this) {
}

void Opening_Main(GameState* thisx) {
    OpeningContext* this = (OpeningContext*)thisx;

    func_80095248(this->state.gfxCtx, 0, 0, 0);
    Opening_SetupTitleScreen(this);
    func_80803C5C(this);
}

void Opening_Destroy(GameState* thisx) {
}

void Opening_Init(GameState* thisx) {
    OpeningContext* this = (OpeningContext*)thisx;

    R_UPDATE_RATE = 1;
    Matrix_Init(&this->state);
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = Opening_Main;
    this->state.destroy = Opening_Destroy;
}
