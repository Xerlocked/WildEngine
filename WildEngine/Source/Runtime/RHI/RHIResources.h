#pragma once
/** The base type of RHI resources. */
class FRHIResource
{
public:
    virtual ~FRHIResource() = default;
};

/**
 *  State Block
 */
class FRHISamplerState : public FRHIResource {};
class FRHIRasterizerState : public FRHIResource {};
class FRHIDepthStencilState : public FRHIResource {};
class FRHIBlendState : public FRHIResource {};

/**
 * Shaders
 */
class FRHIVertexShader : public FRHIResource {};
class FRHIPixelShader : public FRHIResource {};


/**
 * Misc
 */
class FRHIViewport : public FRHIResource {};

/**
 * Views
 */
class FRHIShaderResourceView : public FRHIResource {};

/**
 * Buffers
 */

class FRHIIndexBuffer : public FRHIResource
{
public:

    /** Initialization constructor. */
    FRHIIndexBuffer(uint32 InStride,uint32 InSize,uint32 InUsage)
    : Stride(InStride)
    , Size(InSize)
    , Usage(InUsage)
    {}

    /** @return The stride in bytes of the index buffer; must be 2 or 4. */
    uint32 GetStride() const { return Stride; }

    /** @return The number of bytes in the index buffer. */
    uint32 GetSize() const { return Size; }

    /** @return The usage flags used to create the index buffer. */
    uint32 GetUsage() const { return Usage; }

private:
    uint32 Stride;
    uint32 Size;
    uint32 Usage;
};

class FRHIVertexBuffer : public FRHIResource
{
public:

    /** Initialization constructor. */
    FRHIVertexBuffer(uint32 InSize,uint32 InUsage)
    : Size(InSize)
    , Usage(InUsage)
    {}

    /** @return The number of bytes in the vertex buffer. */
    uint32 GetSize() const { return Size; }

    /** @return The usage flags used to create the vertex buffer. */
    uint32 GetUsage() const { return Usage; }

private:
    uint32 Size;
    uint32 Usage;
};

class FRHIStructuredBuffer : public FRHIResource
{
public:

    /** Initialization constructor. */
    FRHIStructuredBuffer(uint32 InStride,uint32 InSize,uint32 InUsage)
    : Stride(InStride)
    , Size(InSize)
    , Usage(InUsage)
    {}

    /** @return The stride in bytes of the structured buffer; must be 2 or 4. */
    uint32 GetStride() const { return Stride; }

    /** @return The number of bytes in the structured buffer. */
    uint32 GetSize() const { return Size; }

    /** @return The usage flags used to create the structured buffer. */
    uint32 GetUsage() const { return Usage; }

private:
    uint32 Stride;
    uint32 Size;
    uint32 Usage;
};


class FRHITexture : public FRHIResource
{
public:
	
	/** Initialization constructor. */
	FRHITexture(uint32 InNumMips,uint32 InNumSamples,EPixelFormat InFormat,uint32 InFlags)
	: NumMips(InNumMips)
	, NumSamples(InNumSamples)
	, Format(InFormat)
	, Flags(InFlags)
	{}

	// Dynamic cast methods.
	virtual class FRHITexture2D* GetTexture2D() { return nullptr; }
	virtual class FRHITexture2DArray* GetTexture2DArray() { return nullptr; }
	virtual class FRHITexture3D* GetTexture3D() { return nullptr; }
	virtual class FRHITextureCube* GetTextureCube() { return nullptr; }
	
	/** @return The number of mip-maps in the texture. */
	uint32 GetNumMips() const { return NumMips; }

	/** @return The format of the pixels in the texture. */
	EPixelFormat GetFormat() const { return Format; }

	/** @return The flags used to create the texture. */
	uint32 GetFlags() const { return Flags; }

	/* @return the number of samples for multi-sampling. */
	uint32 GetNumSamples() const { return NumSamples; }

	/** @return Whether the texture is multi sampled. */
	bool IsMultisampled() const { return NumSamples > 1; }		

private:
	uint32 NumMips;
	uint32 NumSamples;
	EPixelFormat Format;
	uint32 Flags;
};

class FRHITexture2D : public FRHITexture
{
public:
	
	/** Initialization constructor. */
	FRHITexture2D(uint32 InSizeX,uint32 InSizeY,uint32 InNumMips,uint32 InNumSamples,EPixelFormat InFormat,uint32 InFlags)
	: FRHITexture(InNumMips,InNumSamples,InFormat,InFlags)
	, SizeX(InSizeX)
	, SizeY(InSizeY)
	{}
	
	// Dynamic cast methods.
	FRHITexture2D* GetTexture2D() override { return this; }

	/** @return The width of the texture. */
	uint32 GetSizeX() const { return SizeX; }
	
	/** @return The height of the texture. */
	uint32 GetSizeY() const { return SizeY; }

private:

	uint32 SizeX;
	uint32 SizeY;
};

class FRHITexture2DArray : public FRHITexture
{
public:
	
	/** Initialization constructor. */
	FRHITexture2DArray(uint32 InSizeX,uint32 InSizeY,uint32 InSizeZ,uint32 InNumMips,EPixelFormat InFormat,uint32 InFlags)
	: FRHITexture(InNumMips,1,InFormat,InFlags)
	, SizeX(InSizeX)
	, SizeY(InSizeY)
	, SizeZ(InSizeZ)
	{}
	
	// Dynamic cast methods.
	FRHITexture2DArray* GetTexture2DArray() override { return this; }
	
	/** @return The width of the textures in the array. */
	uint32 GetSizeX() const { return SizeX; }
	
	/** @return The height of the texture in the array. */
	uint32 GetSizeY() const { return SizeY; }

	/** @return The number of textures in the array. */
	uint32 GetSizeZ() const { return SizeZ; }

private:

	uint32 SizeX;
	uint32 SizeY;
	uint32 SizeZ;
};

class FRHITexture3D : public FRHITexture
{
public:
	
	/** Initialization constructor. */
	FRHITexture3D(uint32 InSizeX,uint32 InSizeY,uint32 InSizeZ,uint32 InNumMips,EPixelFormat InFormat,uint32 InFlags)
	: FRHITexture(InNumMips,1,InFormat,InFlags)
	, SizeX(InSizeX)
	, SizeY(InSizeY)
	, SizeZ(InSizeZ)
	{}
	
	// Dynamic cast methods.
	FRHITexture3D* GetTexture3D() override { return this; }
	
	/** @return The width of the texture. */
	uint32 GetSizeX() const { return SizeX; }
	
	/** @return The height of the texture. */
	uint32 GetSizeY() const { return SizeY; }

	/** @return The depth of the texture. */
	uint32 GetSizeZ() const { return SizeZ; }

private:

	uint32 SizeX;
	uint32 SizeY;
	uint32 SizeZ;
};

class FRHITextureCube : public FRHITexture
{
public:
	
	/** Initialization constructor. */
	FRHITextureCube(uint32 InSize,uint32 InNumMips,EPixelFormat InFormat,uint32 InFlags)
	: FRHITexture(InNumMips,1,InFormat,InFlags)
	, Size(InSize)
	{}
	
	// Dynamic cast methods.
	FRHITextureCube* GetTextureCube() override { return this; }
	
	/** @return The width and height of each face of the cubemap. */
	uint32 GetSize() const { return Size; }

private:

	uint32 Size;
};


// Declare RHI resource reference types.
#define DEFINE_RHI_REFERENCE_TYPE(Type,ParentType) \
	typedef FRHI##Type*              F##Type##RHIParamRef;

ENUM_RHI_RESOURCE_TYPES(DEFINE_RHI_REFERENCE_TYPE);

class FRHIRenderTargetView
{
public:
	FTextureRHIParamRef Texture;
	uint32 MipIndex;

	/** Array slice or texture cube face.  Only valid if texture resource was created with TexCreate_TargetArraySlicesIndependently! */
	uint32 ArraySliceIndex;

	FRHIRenderTargetView() : 
		Texture(NULL),
		MipIndex(0),
		ArraySliceIndex(-1)
	{}

	FRHIRenderTargetView(FTextureRHIParamRef InTexture) :
		Texture(InTexture),
		MipIndex(0),
		ArraySliceIndex(-1)
	{}

	FRHIRenderTargetView(FTextureRHIParamRef InTexture, uint32 InMipIndex, uint32 InArraySliceIndex) :
		Texture(InTexture),
		MipIndex(InMipIndex),
		ArraySliceIndex(InArraySliceIndex)
	{}
};