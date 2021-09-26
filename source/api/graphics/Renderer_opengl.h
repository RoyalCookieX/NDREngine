#pragma once
#include "graphics/Renderer.h"

namespace NDR { namespace GraphicsAPI
{
   class Renderer_opengl : public Renderer
   {
   public:
      Renderer_opengl();
      virtual ~Renderer_opengl() override;
        
      virtual void Clear() const override;
      virtual void Draw(Mesh* mesh, Shader* shader) const override;
      virtual void DrawBackground(float r, float g, float b, float a) const override;
      virtual void SetBlendMode(const BlendMode& blendMode) const override;
   };
}
}
