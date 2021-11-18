#pragma once
#include "Shader.h"
#include "Texture.h"
#include "utility/Memory.h"

namespace NDR
{
    enum MaterialFlags
    {
        NOFLAGS         = 0,
    
        // Culling
        ENABLECULLING   = 1 << 0,
        CULLBACK        = 1 << 1,
        CULLFRONT       = 1 << 2,
        
        //Blending
        ENABLEBLENDING  = 1 << 3,
        OPAQUE          = 1 << 4,
        TRANSPARENT     = 1 << 5,
    };

    class Material
    {
    public:
        using BoundTextureMap = std::map<std::string, SharedPtr<Texture>>;
        
        Material(const SharedPtr<Shader>& shader, int32_t flags = 0);
        ~Material();

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        BoundTextureMap& GetBoundTextures() { return _boundTextures; }
        const BoundTextureMap& GetBoundTextures() const { return _boundTextures; }
        SharedPtr<Shader>& GetShader() { return _shader; }
        const SharedPtr<Shader>& GetShader() const { return _shader; }
        
        bool HasFlags(int32_t flags) const { return _flags & flags; }
        void EnableFlags(int32_t flags) { _flags = _flags | flags; }
        void DisableFlags(int32_t flags) { _flags = _flags & ~flags; }
        void SetTexture(const std::string& textureName, const SharedPtr<Texture>& texture) const;
    private:
        SharedPtr<Shader> _shader;
        int32_t _flags;
        mutable BoundTextureMap _boundTextures;
    };
}
