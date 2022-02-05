#include "ultra64.h"
#include "global.h"
#include "object_poisoned_water.h"

u64 gPoisonedWaterDL_poisoned_water_base_texture_rgba16[] = {
	0x9ce79ce7ad6bad6b, 0xad6ba529a529ad6b, 0xb5adad6bbdefc631, 0xad6ba529a529a529, 0x9ce7a529ad6bb5ad, 0xdef7c631a529a529, 0xa529ad6bad6ba529, 0xbdefad6b9ce79ce7, 
	0x9ce79ce7a529b5ad, 0xad6bad6bad6bad6b, 0xb5adb5adce73ad6b, 0xa529a5299ce7a529, 0x9ce79ce79ce79ce7, 0xc631def7ad6ba529, 0xa529a529a529b5ad, 0xce73a529a529a529, 
	0xa529a529a529b5ad, 0xad6bad6bad6ba529, 0xad6bc631bdefa529, 0xa529a529a5299ce7, 0x9ce7a5299ce79ce7, 0xad6bbdefb5adb5ad, 0xad6bad6ba529ad6b, 0xb5adad6ba529a529, 
	0xad6bad6ba529b5ad, 0xad6bb5adc631d6b5, 0xdef7d6b5a529a529, 0xa529a529a529a529, 0xa529a529a529a529, 0xbdefad6bad6bbdef, 0xc631bdefb5adb5ad, 0xa529ad6bad6ba529, 
	0xad6bb5adb5adbdef, 0xce73def7d6b5ef7b, 0xf7bddef7b5ada529, 0xa529a529a529a529, 0xa529a529a529b5ad, 0xc631ad6bad6bad6b, 0xbdefc631bdefce73, 0xe739e739bdefb5ad, 
	0xa529a529b5ade739, 0xf7bdbdefa529a529, 0x9ce7ad6bd6b5c631, 0xa529ad6ba529a529, 0xa529a529a529b5ad, 0xc631ad6bad6bad6b, 0xb5adad6bad6bc631, 0xd6b5def7def7c631, 
	0xa529a529b5ade739, 0xb5ad9ce7a529a529, 0xa529a529ad6bdef7, 0xce73a529a529a529, 0xa529a529ad6bb5ad, 0xbdefb5adad6bb5ad, 0xb5adad6bb5adb5ad, 0xad6b9ce7ad6bce73, 
	0xa529a529bdefc631, 0xa529a529a529a529, 0xa529a529a529b5ad, 0xd6b5c631ad6bad6b, 0xad6bad6bad6bbdef, 0xb5adb5adb5adb5ad, 0xb5adb5adb5adb5ad, 0xa529a529a529a529, 
	0xa529ad6bce73c631, 0xa529a529ad6ba529, 0xa529a529a529a529, 0xad6bc631c631c631, 0xc631b5adb5adb5ad, 0xad6bbdefd6b5ce73, 0xc631c631c631b5ad, 0xa529a529a529a529, 
	0xad6bb5adce73def7, 0xb5adad6ba529a529, 0xa529a529a529ad6b, 0xb5adad6bad6bb5ad, 0xd6b5ce73bdefbdef, 0xbdefd6b5ce73bdef, 0xbdefc631c631b5ad, 0xad6ba529a529a529, 
	0xbdefad6bce73ef7b, 0xef7bb5ada529a529, 0xa529a529ad6bb5ad, 0xad6ba529a529a529, 0xad6bb5addef7f7bd, 0xef7bce73bdefad6b, 0xad6bb5adbdefb5ad, 0xad6ba529a529a529, 
	0xad6ba529def7ef7b, 0xef7bb5ada529ad6b, 0xad6bad6bb5adb5ad, 0xad6bad6bad6bad6b, 0xad6bc631ce73c631, 0xbdefbdefb5adb5ad, 0xb5adbdefb5adad6b, 0xad6bad6ba529a529, 
	0xad6ba529ce73ef7b, 0xe739bdefad6bad6b, 0xb5adbdefc631b5ad, 0xb5adad6ba529c631, 0xe739c631ad6ba529, 0xa529ad6bb5adb5ad, 0xb5adb5adad6bad6b, 0xad6bad6ba529ad6b, 
	0xad6bad6ba529c631, 0xef7bce73ad6bb5ad, 0xb5adc631ce73c631, 0xbdefb5adce73ef7b, 0xd6b5a529ad6ba529, 0xa529ad6bb5adb5ad, 0xb5adc631b5adad6b, 0xad6bb5adb5adad6b, 
	0xa529a529ad6ba529, 0xb5ade739bdefb5ad, 0xb5adbdefc631d6b5, 0xc631def7f7bdd6b5, 0xad6bad6bad6bad6b, 0xad6bb5adbdefbdef, 0xbdefc631ce73bdef, 0xb5adb5adce73e739, 
	0xa529a529a529a529, 0xb5adce73d6b5bdef, 0xad6bad6bb5adc631, 0xe739f7bdef7bce73, 0xb5adad6bb5adc631, 0xd6b5c631b5adb5ad, 0xad6bb5adbdefce73, 0xc631b5adb5ade739, 
	0xad6bad6bad6bbdef, 0xce73ad6bb5add6b5, 0xce73c631ad6bbdef, 0xf7bdf7bdbdefce73, 0xd6b5ce73ce73c631, 0xbdefbdefb5adad6b, 0xad6bad6bb5adc631, 0xb5adad6bad6bce73, 
	0xb5adb5adc631c631, 0xb5adb5adb5adb5ad, 0xce73def7def7f7bd, 0xf7bdbdefad6bbdef, 0xe739e739c631b5ad, 0xb5adb5adb5adad6b, 0xb5adb5adb5adbdef, 0xc631b5adad6bdef7, 
	0xb5adbdefce73bdef, 0xb5adb5adad6ba529, 0x9ce7a529bdeff7bd, 0xdef7a529ad6bad6b, 0xbdefbdefb5adb5ad, 0xb5adb5adbdefc631, 0xc631ad6ba529a529, 0xb5adc631c631d6b5, 
	0xce73ce73bdefb5ad, 0xad6bad6bad6ba529, 0xa529a529a529ce73, 0xdef7ad6bad6bb5ad, 0xb5adb5adad6bb5ad, 0xb5adbdefce73ce73, 0xb5adad6ba529a529, 0xa529bdefce73c631, 
	0xc631ad6ba529a529, 0xa529ad6bad6ba529, 0xad6bad6bad6bb5ad, 0xe739c631ad6bb5ad, 0xb5adb5adad6bb5ad, 0xb5adc631def7c631, 0xad6ba529a529a529, 0xa529b5ade739ce73, 
	0xad6ba529a529a529, 0xa529a529a529ad6b, 0xad6bad6bad6ba529, 0xc631ef7bbdefad6b, 0xad6bad6bad6bad6b, 0xbdefd6b5e739b5ad, 0xad6bad6ba529ad6b, 0xa529bdefef7bbdef, 
	0xad6ba529a529a529, 0xa529a529a529ad6b, 0xad6bad6bad6bad6b, 0xc631d6b5d6b5ce73, 0xbdefb5adad6bad6b, 0xbdefef7be739ad6b, 0xad6bad6bad6bad6b, 0xad6be739ef7bd6b5, 
	0xad6ba529a529a529, 0xa529a529ad6bad6b, 0xad6ba529ad6bad6b, 0xce73c631b5adce73, 0xdef7def7e739def7, 0xdef7f7bde739ad6b, 0xad6bad6bad6bad6b, 0xd6b5def7ad6bb5ad, 
	0xad6ba529a529a529, 0xa529ad6bad6bad6b, 0xa529a529ad6bb5ad, 0xce73c631b5adb5ad, 0xb5adbdefdef7f7bd, 0xce73ce73f7bdce73, 0xad6bad6bad6bce73, 0xef7bb5adad6bad6b, 
	0xad6bad6bad6bad6b, 0xad6bad6bad6ba529, 0xa529a529b5adc631, 0xc631bdefb5adad6b, 0xa529a529ad6bc631, 0xdef7bdefce73e739, 0xd6b5bdefce73ef7b, 0xbdefad6bad6bad6b, 
	0xb5adad6bad6bad6b, 0xad6bad6ba529a529, 0xa529ad6bbdefbdef, 0xbdefbdefb5adad6b, 0xa529a529a529ad6b, 0xd6b5ce73ad6bb5ad, 0xce73ef7bf7bdd6b5, 0xad6bad6bad6bad6b, 
	0xbdefd6b5ce73b5ad, 0xad6ba529a529a529, 0xa529b5adb5adad6b, 0xad6bb5adb5ada529, 0xa529a529a529a529, 0xad6bce73b5adb5ad, 0xbdefd6b5ef7bbdef, 0xad6bad6bad6bad6b, 
	0xdef7ce73ce73ce73, 0xd6b5ce73b5adad6b, 0xbdefbdefad6bad6b, 0xad6bad6bad6bad6b, 0xa529a529a529a529, 0xa529bdefc631bdef, 0xbdefb5addef7b5ad, 0xad6bad6bad6bad6b, 
	0xad6b9ce79ce7a529, 0xb5adce73d6b5def7, 0xd6b5b5adad6bad6b, 0xad6bad6bad6bad6b, 0xad6ba529a529a529, 0xa529b5add6b5bdef, 0xad6bb5add6b5ad6b, 0xad6bad6bad6bad6b, 
	0xa5299ce79ce79ce7, 0x9ce79ce7b5adc631, 0xb5adb5adad6bad6b, 0xad6ba529ad6bb5ad, 0xad6ba529a529a529, 0xa529bdefd6b5b5ad, 0xad6bb5adce73ad6b, 0xad6bad6bad6bad6b, 
	0xa5299ce79ce79ce7, 0x9ce7a529ad6bad6b, 0xad6bad6bad6bad6b, 0xad6ba529ad6bb5ad, 0xad6ba529a529a529, 0xa529ce73c631b5ad, 0xad6bb5adc631b5ad, 0xad6bad6bad6ba529, 
	
};

Vtx gPoisonedWaterDL_actualwater_mesh_layer_Transparent_vtx_cull[8] = {
	{{{-1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx gPoisonedWaterDL_actualwater_mesh_layer_Transparent_vtx_0[4] = {
	{{{-1000, 0, 1000},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1000, 0, 1000},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1000, 0, -1000},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1000, 0, -1000},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx gPoisonedWaterDL_actualwater_mesh_layer_Transparent_tri_0[] = {
	gsSPVertex(gPoisonedWaterDL_actualwater_mesh_layer_Transparent_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gPoisonedWaterDL_f3d_material_layerTransparent[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL1, TEXEL0, ENV_ALPHA, TEXEL0, 0, 0, 0, 1, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIMITIVE, 0),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, gPoisonedWaterDL_poisoned_water_base_texture_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 14, G_TX_WRAP | G_TX_NOMIRROR, 5, 14),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 1023, 256),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 14, G_TX_WRAP | G_TX_NOMIRROR, 5, 14),
	gsDPSetTileSize(0, 0, 0, 124, 124),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, gPoisonedWaterDL_poisoned_water_base_texture_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 256, 6, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 12, G_TX_WRAP | G_TX_NOMIRROR, 5, 12),
	gsDPLoadSync(),
	gsDPLoadBlock(6, 0, 0, 1023, 256),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 256, 1, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 12, G_TX_WRAP | G_TX_NOMIRROR, 5, 12),
	gsDPSetTileSize(1, 0, 0, 124, 124),
	gsDPSetPrimColor(0, 0, 254, 254, 254, 127),
	gsDPSetEnvColor(254, 254, 254, 127),
	gsSPDisplayList(0x9000000),
	gsSPEndDisplayList(),
};

Gfx gPoisonedWaterDL[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(gPoisonedWaterDL_actualwater_mesh_layer_Transparent_vtx_cull + 0, 8, 0),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_gPoisonedWaterDL_f3d_material_layerTransparent),
	gsSPDisplayList(gPoisonedWaterDL_actualwater_mesh_layer_Transparent_tri_0),
	gsSPEndDisplayList(),
};

