#pragma once
#include "Shader.h"
#include "Texture.h"

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
        Material();
        Material(Shader&& shader, int32_t flags = 0);
        ~Material();

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        Material(Material&& other) noexcept;
        Material& operator=(Material&& other) noexcept;

        bool operator==(const Material& other) const;
        bool operator!=(const Material& other) const;

        std::map<std::string, const Texture*>& GetBoundTextures() { return _boundTextures; }
        const std::map<std::string, const Texture*>& GetBoundTextures() const { return _boundTextures; }
        Shader& GetShader() { return _shader; }
        const Shader& GetShader() const { return _shader; }
        
        bool HasFlags(int32_t flags) const { return _flags & flags; }
        void EnableFlags(int32_t flags) { _flags = _flags | flags; }
        void DisableFlags(int32_t flags) { _flags = _flags & ~flags; }
        void SetTexture(const std::string& textureName, const Texture& texture) const;
    private:
        Shader _shader;
        int32_t _flags;
        mutable std::map<std::string, const Texture*> _boundTextures;
    };
}
