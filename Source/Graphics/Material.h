#pragma once
#include "Defines.h"

namespace NDR
{
    class Texture;
    class Shader;
    
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
        using BoundTextureMap = std::map<std::string, SPointer<Texture>>;
        
        Material(const SPointer<Shader>& shader, Int32 flags = 0);
        ~Material();

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        BoundTextureMap& GetBoundTextures() { return _boundTextures; }
        const BoundTextureMap& GetBoundTextures() const { return _boundTextures; }
        SPointer<Shader>& GetShader() { return _shader; }
        const SPointer<Shader>& GetShader() const { return _shader; }
        
        bool HasFlags(Int32 flags) const { return _flags & flags; }
        void EnableFlags(Int32 flags) { _flags = _flags | flags; }
        void DisableFlags(Int32 flags) { _flags = _flags & ~flags; }
        void SetTexture(const std::string& textureName, const SPointer<Texture>& texture) const;
    private:
        SPointer<Shader> _shader;
        Int32 _flags;
        mutable BoundTextureMap _boundTextures;
    };
}
