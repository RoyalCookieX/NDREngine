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

    void Material::SetTexture(const std::string& textureName, const Texture& texture) const
    {
        auto it = _boundTextures.find(textureName);
        if(it != _boundTextures.end())
        {
            it->second = &texture;
        }
        else
        {
            _boundTextures.emplace(std::make_pair(textureName, &texture));
        }
    }
}
