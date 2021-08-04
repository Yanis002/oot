/*
 * File: z_obj_mure4.c
 * Overlay: ovl_Obj_Mure4
 * Description: Tree + bush/rock spawner
 */

#include "z_obj_mure4.h"

#define THIS ((Obj_Mure4*)thisx)

void Obj_Mure4_Init(Actor* thisx, GlobalContext* globalCtx);
void Obj_Mure4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Obj_Mure4_Update(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Mure4_InitVars = {
    ACTOR_OBJ_MURE4,
    ACTORCAT_MISC,
    0x00000030, // always run update and draw
    OBJECT_GAMEPLAY_KEEP,
    sizeof(Obj_Mure4),
    (ActorFunc)Obj_Mure4_Init,
    (ActorFunc)Obj_Mure4_Destroy,
    (ActorFunc)Obj_Mure4_Update,
    NULL,
};

void Obj_Mure4_Init(Actor* thisx, GlobalContext* globalCtx){

}

void Obj_Mure4_Destroy(Actor* thisx, GlobalContext* globalCtx){

}

void Obj_Mure4_Update(Actor* thisx, GlobalContext* globalCtx){
    Printf_Print(globalCtx, 0xFEFEFEFE, 0x010100, "hello world");
}
