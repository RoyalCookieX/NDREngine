#pragma once
#include "core/Engine.h"

namespace Test
{
    class Test_3D : public NDR::Engine
    {
    public:
        virtual void Initialize() override;
        virtual void Tick(float deltaTime) override;
        virtual void Shutdown() override;
    private:
        NDR::VertexArray _va;
        NDR::VertexLayout _layout;
        NDR::IndexBuffer _ib;
        NDR::Shader _shader;
        NDR::Texture2D _texture;
    };
}
