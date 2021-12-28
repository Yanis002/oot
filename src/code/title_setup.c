#include "global.h"

void TitleSetup_InitImpl(GameState* gameState) {
    SaveContext_Init();
    gameState->running = false;
    gSaveContext.gameMode = 0;
    gSaveContext.linkAge = 1;
    Sram_InitDebugSave();
    gSaveContext.dayTime = 0x5000;
    gSaveContext.entranceIndex = 0x27E;
    gSaveContext.respawnFlag = 0;
    gSaveContext.respawn[RESPAWN_MODE_DOWN].entranceIndex = -1;
    gSaveContext.equips.buttonItems[2] = ITEM_HOOKSHOT;
    gSaveContext.equips.cButtonSlots[1] = SLOT_HOOKSHOT;
    SET_NEXT_GAMESTATE(gameState, Gameplay_Init, GlobalContext);
}

void TitleSetup_Destroy(GameState* gameState) {
}

void TitleSetup_Init(GameState* gameState) {
    gameState->destroy = TitleSetup_Destroy;
    TitleSetup_InitImpl(gameState);
}
