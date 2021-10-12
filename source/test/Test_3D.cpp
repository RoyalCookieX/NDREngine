#include "ndrpch.h"
#include "Test_3D.h"

#include "utility/AssetManager.h"

void Test::Test_3D::Initialize()
{
    _layout.AddAttribute({3, false});
    _layout.AddAttribute({4, false});
    _layout.AddAttribute({2, false});
    _layout.AddAttribute({1, false});
    NDR::VertexBuffer vb(1 * 4 * _layout.GetStride());
    _va = NDR::VertexArray(std::move(vb), _layout);

    _ib = NDR::IndexBuffer({0, 1, 2, 0, 2, 3});

    _texture = NDR::LoadTexture2D("assets/textures/UVTest.png");
    GetRenderer()->BindTexture(_texture, 0);
    _shader = NDR::LoadShader("assets/shaders/Quad_d.shader");
    GetRenderer()->BindShader(_shader);
}

void Test::Test_3D::Tick(float deltaTime)
{
    _va.GetVertexBuffer().SetData(sizeof(float) *  0, {-0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f, /**/ 0.0f});
    _va.GetVertexBuffer().SetData(sizeof(float) * 10, { 0.5f, -0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f, /**/ 0.0f});
    _va.GetVertexBuffer().SetData(sizeof(float) * 20, { 0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f, /**/ 0.0f});
    _va.GetVertexBuffer().SetData(sizeof(float) * 30, {-0.5f,  0.5f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f, /**/ 0.0f});
    
    GetRenderer()->DrawBackground({0.9f, 0.7f, 0.8f, 1.0f});
    GetRenderer()->DrawElements(_ib.GetCount());
}

void Test::Test_3D::Shutdown()
{
    
}

