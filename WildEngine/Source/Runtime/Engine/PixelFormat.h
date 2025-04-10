﻿// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.


#ifndef __PixelFormat_h__
#define __PixelFormat_h__

enum EPixelFormat
{
	PF_Unknown              =0,
	PF_A32B32G32R32F        =1,
	PF_B8G8R8A8             =2,
	PF_G8                   =3,
	PF_G16                  =4,
	PF_DXT1                 =5,
	PF_DXT3                 =6,
	PF_DXT5                 =7,
	PF_UYVY                 =8,
	PF_FloatRGB             =9,
	PF_FloatRGBA            =10,
	PF_DepthStencil         =11,
	PF_ShadowDepth          =12,
	PF_R32_FLOAT            =13,
	PF_G16R16               =14,
	PF_G16R16F              =15,
	PF_G16R16F_FILTER       =16,
	PF_G32R32F              =17,
	PF_A2B10G10R10          =18,
	PF_A16B16G16R16         =19,
	PF_D24                  =20,
	PF_R16F                 =21,
	PF_R16F_FILTER          =22,
	PF_BC5                  =23,
	PF_V8U8                 =24,
	PF_A1                   =25,
	PF_FloatR11G11B10       =26,
	PF_A8                   =27,
	PF_R32_UINT             =28,
	PF_R32_SINT             =29,
	PF_PVRTC2               =30,
	PF_PVRTC4               =31,
	PF_R16_UINT             =32,
	PF_R16_SINT             =33,
	PF_R16G16B16A16_UINT    =34,
	PF_R16G16B16A16_SINT    =35,
	PF_R5G6B5_UNORM         =36,
	PF_R8G8B8A8             =37,
	PF_A8R8G8B8				=38,			// Only used for legacy loading; do NOT use!
	PF_BC4					=39,
	PF_R8G8                 =40,
	PF_ATC_RGB				=41,
	PF_ATC_RGBA_E			=42,
	PF_ATC_RGBA_I			=43,
	PF_X24_G8				=44,			// Used for creating SRVs to alias a DepthStencil buffer to read Stencil. Don't use for creating textures.
	PF_ETC1					=45,
	PF_ETC2_RGB				=46,
	PF_ETC2_RGBA			=47,
	PF_MAX                  =48,
};
#define FOREACH_ENUM_EPIXELFORMAT(op) \
	op(PF_Unknown) \
	op(PF_A32B32G32R32F) \
	op(PF_B8G8R8A8) \
	op(PF_G8) \
	op(PF_G16) \
	op(PF_DXT1) \
	op(PF_DXT3) \
	op(PF_DXT5) \
	op(PF_UYVY) \
	op(PF_FloatRGB) \
	op(PF_FloatRGBA) \
	op(PF_DepthStencil) \
	op(PF_ShadowDepth) \
	op(PF_R32_FLOAT) \
	op(PF_G16R16) \
	op(PF_G16R16F) \
	op(PF_G16R16F_FILTER) \
	op(PF_G32R32F) \
	op(PF_A2B10G10R10) \
	op(PF_A16B16G16R16) \
	op(PF_D24) \
	op(PF_R16F) \
	op(PF_R16F_FILTER) \
	op(PF_BC5) \
	op(PF_V8U8) \
	op(PF_A1) \
	op(PF_FloatR11G11B10) \
	op(PF_A8) \
	op(PF_R32_UINT) \
	op(PF_R32_SINT) \
	op(PF_PVRTC2) \
	op(PF_PVRTC4) \
	op(PF_R16_UINT) \
	op(PF_R16_SINT) \
	op(PF_R16G16B16A16_UINT) \
	op(PF_R16G16B16A16_SINT) \
	op(PF_R5G6B5_UNORM) \
	op(PF_R8G8B8A8) \
	op(PF_A8R8G8B8) \
	op(PF_BC4) \
	op(PF_R8G8) \
	op(PF_ATC_RGB) \
	op(PF_ATC_RGBA_E) \
	op(PF_ATC_RGBA_I) \
	op(PF_X24_G8) \
	op(PF_ETC1) \
	op(PF_ETC2_RGB) \
	op(PF_ETC2_RGBA)


#endif		// __PixelFormat_h__