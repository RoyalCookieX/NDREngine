#include "ndrpch.h"
#include "Material.h"

namespace NDR
{
    Material::Material():
        _flags(0)
    {
    }

    Material::Material(Shader&& shader, int32_t flags):
        _shader(std::move(shader)),
        _flags(flags)
    {
    }

    Material::~Material()
    {
    }

    Material::Material(Material&& other) noexcept:
        _shader(std::move(other._shader)),
        _flags(other._flags)
    {
        other._flags = NOFLAGS;
    }

    Material& Material::operator=(Material&& other) noexcept
    {
        if(*this != other)
        {
            _shader = std::move(other._shader);
            _flags = other._flags;

            other._flags = NOFLAGS;
        }
        return *this;
    }

    bool Material::operator==(const Material& other) const
    {
        return
        _shader == other._shader &&
        _flags == other._flags;
    }
    bool Material::operator!=(const Material& other) const { return !(*this == other); }

    bool Material::HasFlags(int32_t flags) const { return _flags & flags; }

    void Material::EnableFlags(int32_t flags)
    {
        _flags = _flags | flags;
    }

    void Material::DisableFlags(int32_t flags)
    {
        _flags = _flags & ~flags;
    }

    Shader& Material::GetShader() { return _shader; }
    const Shader& Material::GetShader() const { return _shader; }

    void Material::Use() const
    {
        // set material flags
        // cull face
        if(HasFlags(ENABLECULLING))
        {
            glEnable(GL_CULL_FACE);
            if(HasFlags(CULLBACK))
                glCullFace(GL_BACK);
            else if(HasFlags(CULLFRONT))
                glCullFace(GL_FRONT);
        }
        else glDisable(GL_CULL_FACE);

        // blending
        if(HasFlags(ENABLEBLENDING))
        {
            glEnable(GL_BLEND);
            if(HasFlags(OPAQUE))
                glDisable(GL_BLEND);
            else if(HasFlags(TRANSPARENT))
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }
        else glDisable(GL_BLEND);

        _shader.Use();
    }
}
