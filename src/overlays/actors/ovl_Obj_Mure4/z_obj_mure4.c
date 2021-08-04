/*
 * File: z_obj_mure4.c
 * Overlay: ovl_Obj_Mure4
 * Description: Tree + bush/rock spawner
 */

#include "z_obj_mure4.h"

#define THIS ((ObjMure4*)thisx)

void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx);
s16 ObjMure4_SetWood02Vars(ObjMure4* this, Vec3f pos);
s16 ObjMure4_SetVariantVars(ObjMure4* this, Vec3f pos, Vec3s rot);

const ActorInit Obj_Mure4_InitVars = {
    ACTOR_OBJ_MURE4,
    ACTORCAT_MISC,
    0x00000030, // always run update and draw
    OBJECT_GAMEPLAY_KEEP,
    sizeof(ObjMure4),
    (ActorFunc)ObjMure4_Init,
    (ActorFunc)ObjMure4_Destroy,
    (ActorFunc)ObjMure4_Update,
    NULL,
};

static s16 sActorSpawnIDs[] = { ACTOR_EN_WOOD02, ACTOR_EN_KUSA, ACTOR_EN_ISHI };
static s16 type = 0xFFFF;

void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx){
    ObjMure4* this = THIS;

    ObjMure4_ActorSpawn(this, globalCtx);
}

void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx){
    Vec3f pos;
    Vec3s rot;
    s16 i, params;

    pos = this->actor.world.pos;
    rot.z = this->actor.world.rot.z;
    //0xF000 for switch flag, 0x0F00 for number of times, 0x00F0 for drops, 0x000F for bugs
    //params: 0xF000 for wood02 drops, 0x0F00 for wood02 type, 0x00F0 for type of type of actor, 0x000F type of actor

    for(i = 0; i < 5; i++){
        if(i == 0){
            params = ObjMure4_SetWood02Vars(this, pos);
        }
        else {
            params = ObjMure4_SetVariantVars(this, pos, rot);
        }

        Actor_Spawn(&globalCtx->actorCtx, globalCtx, sActorSpawnIDs[type],
                                                 (pos.x + (i * 100.f)), pos.y, pos.z,
                                                 0, 0, 0, params);
        
    }
}

s16 ObjMure4_SetWood02Vars(ObjMure4* this, Vec3f pos){
    s16 params = 0xFFFF;

    params = this->actor.params;
    type = 0;
    return ((((params >> 8) & 0xF0) << 4) + ((params >> 8) & 0xF));
    //item drop, type
}

s16 ObjMure4_SetVariantVars(ObjMure4* this, Vec3f pos, Vec3s rot){
    s16 params = 0xFFFF;

    params = this->actor.params;
    type = params & 0xF;

    switch(type){
        case 1: //bush
            return ((((rot.z & 0xFF) >> 4) << 8) + ((rot.z & 0xF) << 4) + ((params & 0xFF) >> 4));
            //drop table, bugs, type

        case 2: //rock
            return (((rot.z >> 12) << 12) + (((rot.z & 0xFF) >> 4) << 8) + ((rot.z & 0xF) << 4) + ((params & 0xFF) >> 4));
            //switch flag, drop table, bugs, type
    } 
}

void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx){
}

void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx){
}
