#pragma once
#include <NDREngine.h>

class ExampleApplication : public NDR::Engine
{
public:
    virtual void Initialize() override;
    virtual void Tick(float deltaTime) override;
    virtual void Shutdown() override;
};