/*
 * File: z_obj_mure4.c
 * Overlay: ovl_Obj_Mure4
 * Description: Tree + bush/rock spawner
 */

// Actor parameters:
// 0x000F: type/which type come first
// 0x00F0: 1 for both types
// 0x0F00: for variant number
// 0xF000: for repetition number

//TODO: add custom distance and direction parameters

#include "z_obj_mure4.h"

#define THIS ((ObjMure4*)thisx)

void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx, Vec3f pos, Vec3f pos2, Vec3s rot);
void ObjMure4_SpawnTree(GlobalContext *globalCtx, Vec3f pos, Vec3s rot);
void ObjMure4_SpawnVariant(GlobalContext *globalCtx, Vec3f pos);
void ObjMure4_SetVariantParams(ObjMure4* this, Vec3s rot, s16 params);
void ObjMure4_SpawnBoth(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, Vec3s rot, s16 params);
s16 ObjMure4_GetWood02Vars(Vec3s rot);
s16 ObjMure4_GetVariantVars(ObjMure4* this, Vec3s rot);

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
static s16 type = 0xFFFE, spawnParams = 0xFFFE;

void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx){
    ObjMure4* this = THIS;

    type = this->actor.params & 0xF;
    ObjMure4_ActorSpawn(this, globalCtx, this->actor.world.pos, this->actor.world.pos, this->actor.world.rot);
}

//main function that spawns the actors, still WIP
void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx, Vec3f pos, Vec3f pos2, Vec3s rot){
    s16 i, j, params, variantNb, bitBoth, howMany;

    params = this->actor.params;
    variantNb = (params >> 8) & 0xF;
    bitBoth = (params & 0xFF) >> 4;
    howMany = params >> 12;
    ObjMure4_SetVariantParams(this, rot, params);
    pos2.x = this->actor.world.pos.x + 100;
    
    ObjMure4_SpawnTree(globalCtx, pos, rot);
    //place the first tree

    for(j = 0; j < howMany; j++){
        for(i = 0; i < variantNb; i++){
            if(!bitBoth) ObjMure4_SpawnVariant(globalCtx, pos2);
            else ObjMure4_SpawnBoth(this, globalCtx, pos2, rot, params);
            pos2.x += 100;
            //place the variants and increment pos2.x by the custom distance from the mure4 params/rotation
        }
        
        pos.x = pos2.x;
        pos2.x += 100;
        ObjMure4_SpawnTree(globalCtx, pos, rot);

        if(bitBoth){
            if(type == 1) type = 2;
            else type = 1;
        }
        //place the last tree of the current iteration and switch type if needed
    }
}

//used to spawn both variants, alternating
void ObjMure4_SpawnBoth(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, Vec3s rot, s16 params){
    ObjMure4_SetVariantParams(this, rot, params);
    ObjMure4_SpawnVariant(globalCtx, pos);
    
    if(type == 1) type = 2;
    else type = 1;
}

//get En_Wood02 parameters from the Mure4 X rot
s16 ObjMure4_GetWood02Vars(Vec3s rot){
    return rot.x;
}

//get the variant's parameters from the Mure4 Y or Z rot
s16 ObjMure4_GetVariantVars(ObjMure4* this, Vec3s rot){
    switch(type){
        case 1: //bush
            return rot.y;
            
        case 2: //rock
            return rot.z;
    } 
}

//spawn a single tree
void ObjMure4_SpawnTree(GlobalContext *globalCtx, Vec3f pos, Vec3s rot){
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, sActorSpawnIDs[0], pos.x, pos.y, pos.z, 0, 0, 0, ObjMure4_GetWood02Vars(rot));
}

//spawn a single variant
void ObjMure4_SpawnVariant(GlobalContext *globalCtx, Vec3f pos){
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, sActorSpawnIDs[type], pos.x, pos.y, pos.z, 0, 0, 0, spawnParams);
}

//set variant's parameters
void ObjMure4_SetVariantParams(ObjMure4* this, Vec3s rot, s16 params){
    if(!((params & 0xFF) >> 4)){
        if(params & 0xF) type = 1;
        else type = 2;
    } 

    spawnParams = ObjMure4_GetVariantVars(this, rot);
}

void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx){
}

void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx){
}
