/*
 * File: z_obj_mure4.c
 * Overlay: ovl_Obj_Mure4
 * Description: Tree + bush/rock spawner
 */

/*  Documentation:

    Obj_Mure4 rot.x:
    0xFFFF exact same parameters as en_wood02

    Obj_Mure4 rot.y:
    0xF000 drop table (usually 2)
    0x0F00 bugs for grass (1 for bugs, 0 for no bugs)
    0x00F0 type for grass (look https://wiki.cloudmodding.com/oot/Actor_List_(Variables)#En_Kusa for type)
    0x000F bugs for rock (1 for bugs, 0 for no bugs)

    Obj_Mure4 rot.z:
    0xF000 type for rock (look https://wiki.cloudmodding.com/oot/Actor_List_(Variables)#En_Ishi for type, switch flag is always 0xF000)
    0x0F00 direction (0 for horizontal (X), 1 for vertical (Z))
    0x00FF distance (this value will be multiplied by 10, 0x0A = 100 units)

    Obj_Mure4 params:
    0xF000 iteration (how many times you want it to repete)
    0x0F00 variant number (how many bushes or rocks you want before the next tree)
    0x00F0 both or single (1 if you want both rocks and bushes, 0 if you want only rocks or only bushes)
    0x000F starting type (1 for bushes, 2 for rocks)
*/

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
static s16 type = 0x0, spawnParams = 0x0;

void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx){
    ObjMure4* this = THIS;

    type = (this->actor.params & 0xF);
    ObjMure4_ActorSpawn(this, globalCtx, this->actor.world.pos, this->actor.world.pos, this->actor.world.rot);
}

//main function that spawns the actors, still WIP
void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx, Vec3f pos, Vec3f pos2, Vec3s rot){
    s16 i, j, params, variantNb, bitBoth, howMany, dist, dir;

    params = this->actor.params;
    variantNb = (params >> 8) & 0xF;
    bitBoth = (params & 0xFF) >> 4;
    howMany = params >> 12;
    dist = (rot.z & 0xFF) * 10;
    dir = (rot.z >> 8) & 0xF;
    ObjMure4_SetVariantParams(this, rot, params);

    if(dir == 0) pos2.x = this->actor.world.pos.x + dist;
    else pos2.z = this->actor.world.pos.z + dist;
    
    ObjMure4_SpawnTree(globalCtx, pos, rot);
    //place the first tree

    for(j = 0; j < howMany; j++){
        for(i = 0; i < variantNb; i++){
            if(!bitBoth) ObjMure4_SpawnVariant(globalCtx, pos2);
            else ObjMure4_SpawnBoth(this, globalCtx, pos2, rot, params);

            if(dir == 0) pos2.x += dist;
            else pos2.z += dist;
            //place the variants and increment pos2.x by the custom distance from the mure4 params/rotation
        }
        
        if(dir == 0){
            pos.x = pos2.x;
            pos2.x += dist;
        }
        else {
            pos.z = pos2.z;
            pos2.z += dist;
        }

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
        case 1: //en_kusa
            return (((rot.y >> 12) << 8) + (((rot.y >> 8) & 0xF) << 4) + ((rot.y & 0xFF) >> 4));
            
        case 2: //en_ishi
            return (0xF000 + ((rot.y >> 12) << 8) + ((rot.y & 0xF) << 4) + (rot.z >> 12));
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
        if((params & 0xF) == 1) type = 1;
        else if((params & 0xF) == 2) type = 2;
    } 

    spawnParams = ObjMure4_GetVariantVars(this, rot);
}

void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx){
}

void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx){
}
