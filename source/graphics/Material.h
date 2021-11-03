#pragma once
#include "Shader.h"

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
        Material(Shader&& shader, int32_t flags);
        ~Material();

        Material(const Material&) = delete;
        Material& operator=(const Material&) = delete;

        Material(Material&& other) noexcept;
        Material& operator=(Material&& other) noexcept;

        bool operator==(const Material& other) const;
        bool operator!=(const Material& other) const;

        void Use() const;
        bool HasFlags(int32_t flags) const;
        void EnableFlags(int32_t flags);
        void DisableFlags(int32_t flags);
        const Shader& GetShader() const;
    private:
        Shader _shader;
        int32_t _flags;
    };
}
