#pragma once
#include <d3d11.h>
#include "D3D11Shader.h"
#include "GraphicType.h"

class FD3D11VertexShader : public FD3D11Shader
{
public:
	virtual ~FD3D11VertexShader() = default;

	/** The vertex shader resource. */
    ID3D11VertexShader* Resource;

    /** The vertex shader's bytecode, with custom data in the last byte. */
    TArray<uint8> Code;

    bool bShaderNeedsGlobalConstantBuffer;

    /** Initialization constructor. */
    FD3D11VertexShader(ID3D11VertexShader* InResource,const TArray<uint8>& InCode):
        Resource(InResource),
        Code(InCode)
    {
        // bGlobalUniformBufferUsed is in the last byte, see CompileD3D11Shader
        bShaderNeedsGlobalConstantBuffer = InCode[InCode.size() - 1] != 0;
    }
	
	void Release() const override
    {
    	Resource->Release();
    }

	EShaderType GetType() const override
    {
	    return ST_VertexShader;
    }
};

class FD3D11PixelShader : public FD3D11Shader
{
public:
	virtual ~FD3D11PixelShader() = default;

	/** The shader resource. */
    ID3D11PixelShader* Resource;
	
	TArray<uint8> Code;

    bool bShaderNeedsGlobalConstantBuffer;

    /** Initialization constructor. */
    FD3D11PixelShader(ID3D11PixelShader* InResource,const TArray<uint8>& InCode):
        Resource(InResource),
		Code(InCode)
    {
        // bGlobalUniformBufferUsed is in the last byte, see CompileD3D11Shader
        bShaderNeedsGlobalConstantBuffer = InCode[InCode.size() - 1] != 0;
    }

	void Release() const override
    {
	    Resource->Release();
    }

	EShaderType GetType() const override
    {
    	return ST_PixelShader;
    }
};


/** Index buffer resource class that stores stride information. */
class FD3D11IndexBuffer
{
public:

	/** The index buffer resource */
	ID3D11Buffer* Resource;

	FD3D11IndexBuffer(ID3D11Buffer* InResource, uint32 InStride, uint32 InSize, uint32 InUsage)
	: Resource(InResource)
	, Stride(InStride)
	, Size(InSize)
	, Usage(InUsage)
	{}

	/** @return The stride in bytes of the index buffer; must be 2 or 4. */
	uint32 GetStride() const { return Stride; }

	/** @return The number of bytes in the index buffer. */
	uint32 GetSize() const { return Size; }

	/** @return The usage flags used to create the index buffer. */
	uint32 GetUsage() const { return Usage; }

	void Release() const
	{
		Resource->Release();
	}
	
private:
	uint32 Stride;
	uint32 Size;
	uint32 Usage;
};


/** Vertex buffer resource class. */
class FD3D11VertexBuffer
{
public:

	ID3D11Buffer* Resource;

	FD3D11VertexBuffer(ID3D11Buffer* InResource, uint32 InSize, uint32 InUsage)
	: Resource(InResource)
	, Size(InSize)
	, Usage(InUsage)
	{}
	
	/** @return The number of bytes in the index buffer. */
	uint32 GetSize() const { return Size; }

	/** @return The usage flags used to create the index buffer. */
	uint32 GetUsage() const { return Usage; }

	void Release() const
	{
		Resource->Release();
	}
	
private:
	uint32 Size;
	uint32 Usage;
};


/** Shader resource view class. */
class FD3D11ShaderResourceView
{
public:
	ID3D11ShaderResourceView* View;

	FD3D11ShaderResourceView(ID3D11ShaderResourceView* InView)
	: View(InView)
	{}
};