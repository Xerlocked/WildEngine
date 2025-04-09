#include "BaseShader.h"
#include "ShaderManager.h"

UBaseShader::UBaseShader(FShaderManager* InShaderManager, const FString& InShaderName)
{
    ShaderManager = InShaderManager;
    ShaderName = InShaderName;
}

UBaseShader::operator FD3D11PixelShader*() const
{
    return ShaderManager->GetPixelShader(ShaderName);
}

UBaseShader::operator FD3D11VertexShader*() const
{
    return ShaderManager->GetVertexShader(ShaderName);
}
