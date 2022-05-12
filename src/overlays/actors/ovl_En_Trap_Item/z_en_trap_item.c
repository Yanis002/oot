/*
* File: z_en_trap_item.c
* Overlay: ovl_En_Trap_Item
* Description: Fake Items
*/

/* PARAMETERS:
    - Item Type: 0000 0000 0000 0111 - 0x03
    - Trap Type: 0000 0000 0011 1000 - 0x38
    0010 1110
*/

#include "z_en_trap_item.h"

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx);

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

void EnTrapItem_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTrapItem* this = (EnTrapItem*)thisx;
    osSyncPrintf("En_Trap_Item: Init started!\n");
    osSyncPrintf("Item Type: %X\nTrap Type: %X\n", GET_ITEM_TYPE(this->actor.params), GET_TRAP_TYPE(this->actor.params));
    osSyncPrintf("En_Trap_Item: Init completed!\n");
}

void EnTrapItem_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnTrapItem_Update(Actor* thisx, GlobalContext* globalCtx) {

}

void EnTrapItem_Draw(Actor* thisx, GlobalContext* globalCtx) {

}
