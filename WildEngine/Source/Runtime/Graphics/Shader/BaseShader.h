#pragma once
#include "Templates/UnrealTypes.h"

class FShaderManager;
class FD3D11PixelShader;
class FD3D11VertexShader;

class UBaseShader
{
public:
    UBaseShader(FShaderManager* InShaderManager, const FString& InShaderName);
    
    FShaderManager* ShaderManager;
    FString ShaderName;

public:
    operator FD3D11PixelShader*() const;
    operator FD3D11VertexShader*() const;
};
