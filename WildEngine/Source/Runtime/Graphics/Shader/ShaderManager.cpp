#include "Templates/UnrealTypes.h"
#include "GraphicType.h"
#include "ShaderManager.h"

#include "BaseShader.h"
#include "D3D11RHI/D3D11Resources.h"

FShaderManager::FShaderManager(UGraphics* InGraphic)
{
    this->Graphic = InGraphic;
}

FShaderManager::~FShaderManager()
{
    Release();
}

void FShaderManager::Initialize()
{
    
}

void FShaderManager::Release() const
{
    for (const auto& Shader : Shaders)
    {
        Shader.second->Release();
    }
}

FD3D11Shader* FShaderManager::LoadShaderFromFile(EShaderType ShaderType, const char* FileName, const char* EntryPoint,
    const char* ShaderName)
{
    
}

UBaseShader FShaderManager::GetShader(const FString& ShaderName)
{
    return {this, ShaderName};
}

FD3D11VertexShader* FShaderManager::GetVertexShader(const FString& ShaderName)
{
    TMap<FString, FD3D11Shader*>::iterator Shader = Shaders.find(ShaderName);

    if (Shader == Shaders.end())
    {
        return nullptr;
    }

    switch (Shader->second->GetType())
    {
        case ST_VertexShader:
            return dynamic_cast<FD3D11VertexShader*>(Shader->second);
        default:
            return nullptr;
    }
}

FD3D11PixelShader* FShaderManager::GetPixelShader(const FString& ShaderName)
{
    TMap<FString, FD3D11Shader*>::iterator Shader = Shaders.find(ShaderName);

    if (Shader == Shaders.end())
    {
        return nullptr;
    }

    switch (Shader->second->GetType())
    {
    case ST_PixelShader:
        return dynamic_cast<FD3D11PixelShader*>(Shader->second);
    default:
        return nullptr;
    }
}
