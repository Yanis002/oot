#include "ultra64.h"
#include "global.h"
#include "object_poisoned_water.h"

Vtx gColorFilterDL_filter_mesh_layer_Transparent_vtx_cull[8] = {
	{{{-1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, 1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{1000, 0, -1000},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};

Vtx gColorFilterDL_filter_mesh_layer_Transparent_vtx_0[4] = {
	{{{-1000, 0, 1000},0, {-16, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1000, 0, 1000},0, {1008, 1008},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{1000, 0, -1000},0, {1008, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-1000, 0, -1000},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};

Gfx gColorFilterDL_filter_mesh_layer_Transparent_tri_0[] = {
	gsSPVertex(gColorFilterDL_filter_mesh_layer_Transparent_vtx_0 + 0, 4, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_gColorFilterDL_f3d_material_001_layerTransparent[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, COMBINED, 0, PRIMITIVE, 0, COMBINED, 0, PRIMITIVE, 0),
	gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
	gsSPClearGeometryMode(G_CULL_FRONT | G_CULL_BACK | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
	gsSPSetOtherMode(G_SETOTHERMODE_H, 4, 20, G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_2CYCLE | G_PM_NPRIMITIVE),
	gsSPSetOtherMode(G_SETOTHERMODE_L, 0, 32, G_AC_NONE | G_ZS_PIXEL | G_RM_FOG_SHADE_A | G_RM_AA_ZB_XLU_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx gColorFilterDL[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(gColorFilterDL_filter_mesh_layer_Transparent_vtx_cull + 0, 8, 0),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_gColorFilterDL_f3d_material_001_layerTransparent),
	gsSPDisplayList(gColorFilterDL_filter_mesh_layer_Transparent_tri_0),
	gsSPEndDisplayList(),
};

