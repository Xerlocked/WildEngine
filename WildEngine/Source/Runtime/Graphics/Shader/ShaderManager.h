#pragma once

enum EShaderType;
class FD3D11VertexShader;
class FD3D11PixelShader;
class FD3D11Shader;
class UGraphics;

class FShaderManager
{
public:
    FShaderManager(UGraphics* InGraphic);
    ~FShaderManager();
    
    friend class UBaseShader;
    
    void Initialize();
    void Release() const;

    static FD3D11Shader* LoadShaderFromFile(EShaderType ShaderType, const char* FileName, const char* EntryPoint, const char* ShaderName);

    /** Return Type Operator
     * 
     *  Usage: FD3D11VertexShader* MyShader = ShaderManager.GetShader("MyVertexShader");
     */
    UBaseShader GetShader(const FString& ShaderName);

private:
    FD3D11VertexShader* GetVertexShader(const FString& ShaderName);
    FD3D11PixelShader* GetPixelShader(const FString& ShaderName);
    
    TMap<FString, FD3D11Shader*> Shaders;
    UGraphics* Graphic;
};
