#pragma once

enum EShaderType : int;

class FD3D11Shader
{
protected:
    ~FD3D11Shader() = default;

public:
    virtual void Release() const = 0;
    virtual EShaderType GetType() const = 0;
};
