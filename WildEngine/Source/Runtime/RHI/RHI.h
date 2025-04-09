#pragma once

#include "Core.h"
#include "PixelFormat.h"

//
// Common RHI definitions.
//

enum ESamplerFilter
{
	SF_Point,
	SF_Bilinear,
	SF_Trilinear,
	SF_AnisotropicPoint,
	SF_AnisotropicLinear,
};

enum ESamplerAddressMode
{
	AM_Wrap,
	AM_Clamp,
	AM_Mirror,
	/** Not supported on all platforms */
	AM_Border
};

enum ESamplerCompareFunction
{
	SCF_Never,
	SCF_Less
};

enum ERasterizerFillMode
{
	FM_Point,
	FM_Wireframe,
	FM_Solid
};

enum ERasterizerCullMode
{
	CM_None,
	CM_CW,
	CM_CCW
};

enum EColorWriteMask
{
	CW_RED   = 0x01,
	CW_GREEN = 0x02,
	CW_BLUE  = 0x04,
	CW_ALPHA = 0x08,

	CW_NONE  = 0,
	CW_RGB   = CW_RED | CW_GREEN | CW_BLUE,
	CW_RGBA  = CW_RED | CW_GREEN | CW_BLUE | CW_ALPHA,
	CW_RG    = CW_RED | CW_GREEN,
	CW_BA    = CW_BLUE | CW_ALPHA,
};

enum ECompareFunction
{
	CF_Less,
	CF_LessEqual,
	CF_Greater,
	CF_GreaterEqual,
	CF_Equal,
	CF_NotEqual,
	CF_Never,
	CF_Always
};

enum EStencilOp
{
	SO_Keep,
	SO_Zero,
	SO_Replace,
	SO_SaturatedIncrement,
	SO_SaturatedDecrement,
	SO_Invert,
	SO_Increment,
	SO_Decrement
};

enum EBlendOperation
{
	BO_Add,
	BO_Subtract,
	BO_Min,
	BO_Max,
    BO_ReverseSubtract,
};

enum EBlendFactor
{
	BF_Zero,
	BF_One,
	BF_SourceColor,
	BF_InverseSourceColor,
	BF_SourceAlpha,
	BF_InverseSourceAlpha,
	BF_DestAlpha,
	BF_InverseDestAlpha,
	BF_DestColor,
	BF_InverseDestColor,
	BF_ConstantBlendFactor,
	BF_InverseConstantBlendFactor
};

enum EVertexElementType
{
	VET_None,
	VET_Float1,
	VET_Float2,
	VET_Float3,
	VET_Float4,
	VET_PackedNormal,	// FPackedNormal
	VET_UByte4,
	VET_UByte4N,
	VET_Color,
	VET_Short2,
	VET_Short4,
	VET_Short2N,		// 16 bit word normalized to (value/32767.0,value/32767.0,0,0,1)
	VET_Half2,			// 16 bit float using 1 bit sign, 5 bit exponent, 10 bit mantissa 
	VET_MAX
};

enum ECubeFace
{
	CubeFace_PosX=0,
	CubeFace_NegX,
	CubeFace_PosY,
	CubeFace_NegY,
	CubeFace_PosZ,
	CubeFace_NegZ,
	CubeFace_MAX
};

enum EUniformBufferUsage
{
	// the uniform buffer is temporary, used for a single draw call then discarded
	UniformBuffer_SingleUse = 0,
	// the uniform buffer is used for multiple draw calls, possibly across multiple frames
	UniformBuffer_MultiUse,
};

enum EResourceLockMode
{
	RLM_ReadOnly,
	RLM_WriteOnly,
	RLM_Num
};


enum EPrimitiveType
{
	PT_TriangleList,
	PT_TriangleStrip,
	PT_LineList,
	PT_QuadList,
	PT_PointList,
	PT_Num,
	PT_NumBits = 6
};

#define ENUM_RHI_RESOURCE_TYPES(EnumerationMacro) \
	EnumerationMacro(SamplerState,None) \
	EnumerationMacro(RasterizerState,None) \
	EnumerationMacro(DepthStencilState,None) \
	EnumerationMacro(BlendState,None) \
	EnumerationMacro(VertexShader,None) \
	EnumerationMacro(PixelShader,None) \
	EnumerationMacro(IndexBuffer,None) \
	EnumerationMacro(VertexBuffer,None) \
	EnumerationMacro(StructuredBuffer,None) \
	EnumerationMacro(Texture,None) \
	EnumerationMacro(Texture2D,Texture) \
	EnumerationMacro(Texture2DArray,Texture) \
	EnumerationMacro(Texture3D,Texture) \
	EnumerationMacro(TextureCube,Texture) \
	EnumerationMacro(Viewport,None) \
	EnumerationMacro(ShaderResourceView,None)

/** An enumeration of the different RHI reference types. */
enum ERHIResourceType
{
	RRT_None,

#define DECLARE_RESOURCE_TYPE_ENUM(Type,ParentType) RRT_##Type,
	ENUM_RHI_RESOURCE_TYPES(DECLARE_RESOURCE_TYPE_ENUM)
#undef DECLARE_RESOURCE_TYPE_ENUM

	RRT_Num
};


#include "RHIResources.h"