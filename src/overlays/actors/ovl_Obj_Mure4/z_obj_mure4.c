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

//TODO: use starting type 0 for spawning trees

#include "z_obj_mure4.h"

#define THIS ((ObjMure4*)thisx)

void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx);

u16 ObjMure4_GetWood02Vars(Vec3s rot);
u16 ObjMure4_GetVariantVars(ObjMure4* this, Vec3s rot);
void ObjMure4_SetVariantParams(ObjMure4* this, Vec3s rot);

void ObjMure4_SpawnTree(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, Vec3s rot, u16 i);
void ObjMure4_SpawnVariant(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, u16 i);
void ObjMure4_SpawnBothVariants(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, Vec3s rot, u16 i);

void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx, Vec3f pos, Vec3f pos2, Vec3s rot);
void ObjMure4_Kill(ObjMure4* this, GlobalContext* globalCtx);

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

//array used to choose the type of actor that should spawn
static u16 sActorSpawnIDs[] = { ACTOR_EN_WOOD02, ACTOR_EN_KUSA, ACTOR_EN_ISHI };
static u16 type = 0x0, spawnParams = 0x0, params = 0x0;

//constructor
void ObjMure4_Init(Actor* thisx, GlobalContext* globalCtx){
    ObjMure4* this = THIS;
    u16 i;

    //initialize global and Mure4 struct vars
    params = this->actor.params;
    type = (params & 0xF);
    this->treeCount = 0;
    this->ptrNb = 0;

    //filling the array with NULLs just in case something is weird with memory
    for(i = 0; i < 256; i++){
        this->actorPtrList[i] = NULL;
    }

    //when the vars are initialized, call the main function
    ObjMure4_ActorSpawn(this, globalCtx, this->actor.world.pos, this->actor.world.pos, this->actor.world.rot);
}

//destructor
void ObjMure4_Destroy(Actor* thisx, GlobalContext* globalCtx){
    ObjMure4* this = THIS;

    ObjMure4_Kill(this, globalCtx);
    Actor_Kill(&this->actor);
}

void ObjMure4_Update(Actor* thisx, GlobalContext* globalCtx){
}

//returns En_Wood02 parameters from the Mure4 X rot
u16 ObjMure4_GetWood02Vars(Vec3s rot){
    return rot.x;
}

//returns the variant's parameters from the Mure4 Y or Z rot
u16 ObjMure4_GetVariantVars(ObjMure4* this, Vec3s rot){
    switch(type){
        case 1: //en_kusa
            return (((rot.y >> 12) << 8) + (((rot.y >> 8) & 0xF) << 4) + ((rot.y & 0xFF) >> 4));
            
        case 2: //en_ishi
            return (0xF000 + ((rot.y >> 12) << 8) + ((rot.y & 0xF) << 4) + (rot.z >> 12));
    } 
}

//set variant's parameters
void ObjMure4_SetVariantParams(ObjMure4* this, Vec3s rot){
    if(!((params & 0xFF) >> 4)){
        if((params & 0xF) == 1) type = 1;
        else if((params & 0xF) == 2) type = 2;
    } 

    spawnParams = ObjMure4_GetVariantVars(this, rot);
}

//spawn a single tree and store the returned value of Actor_Spawn() in the pointer list
void ObjMure4_SpawnTree(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, Vec3s rot, u16 i){
    this->actorPtrList[i] = Actor_Spawn(&globalCtx->actorCtx, globalCtx, sActorSpawnIDs[0], pos.x, pos.y, pos.z, 0, 0, 0, ObjMure4_GetWood02Vars(rot));
    this->treeCount++;
}

//spawn a single variant and store the returned value of Actor_Spawn() in the pointer list
void ObjMure4_SpawnVariant(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, u16 i){
    this->actorPtrList[i] = Actor_Spawn(&globalCtx->actorCtx, globalCtx, sActorSpawnIDs[type], pos.x, pos.y, pos.z, 0, 0, 0, spawnParams);
}

//used to spawn both variants, alternating
void ObjMure4_SpawnBothVariants(ObjMure4* this, GlobalContext *globalCtx, Vec3f pos, Vec3s rot, u16 i){
    ObjMure4_SetVariantParams(this, rot);
    ObjMure4_SpawnVariant(this, globalCtx, pos, i);
    
    if(type == 1) type = 2;
    else type = 1;
}

//main function that spawns the actors
void ObjMure4_ActorSpawn(ObjMure4* this, GlobalContext* globalCtx, Vec3f pos, Vec3f pos2, Vec3s rot){
    u16 i, j, variantNb, iterationNb, boolAlt, dir, dist;

    variantNb = (params >> 8) & 0xF;
    boolAlt = (params & 0xFF) >> 4;
    iterationNb = params >> 12; 
    dist = (rot.z & 0xFF) * 10;
    dir = (rot.z >> 8) & 0xF;
    ObjMure4_SetVariantParams(this, rot);

    if(!dir) pos2.x = this->actor.world.pos.x + dist;
    else pos2.z = this->actor.world.pos.z + dist;

    //place the first tree
    ObjMure4_SpawnTree(this, globalCtx, pos, rot, this->ptrNb);

    for(j = 0; j < iterationNb; j++){
        //place the variants and increment pos2 by the custom distance from the mure4 params/rotation
        for(i = 0; i < variantNb; i++){
            this->ptrNb++;

            if(!boolAlt) ObjMure4_SpawnVariant(this, globalCtx, pos2, this->ptrNb);
            else ObjMure4_SpawnBothVariants(this, globalCtx, pos2, rot, this->ptrNb);

            if(!dir) pos2.x += dist;
            else pos2.z += dist;

            //incrementing ptrNb when a tree comes after the last variant
            if((i + 1) == variantNb) this->ptrNb++;
        }
        
        //direction stuff; 0 for X, 1 for Z
        switch(dir){
            case 0:
                pos.x = pos2.x;
                pos2.x += dist;
                break;

            case 1:
                pos.z = pos2.z;
                pos2.z += dist;
                break;
        }

        //place the last tree of the current iteration
        ObjMure4_SpawnTree(this, globalCtx, pos, rot, this->ptrNb);

        //if you want both variants, switch the type
        if(boolAlt){
            if(type == 1) type = 2; else type = 1;
        }
    }
}

//uses the pointers from the actorPtrList[] array to kill every spawned actor
void ObjMure4_Kill(ObjMure4* this, GlobalContext* globalCtx){
    u16 i;

    //for i < total of spawned actors, total = (repetition * variant number) + number of trees
    for(i = 0; i < (((params >> 12) * ((params >> 8) & 0xF)) + this->treeCount); i++){
        if(this->actorPtrList[i] != NULL){
            if(!Actor_HasParent(this->actorPtrList[i], globalCtx)){
                Actor_Kill(this->actorPtrList[i]);
            }

            this->actorPtrList[i] = NULL;
        }
    }
}
