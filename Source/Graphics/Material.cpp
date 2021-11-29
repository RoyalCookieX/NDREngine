#include "ndrpch.h"
#include "Material.h"

namespace NDR
{
    Material::Material(const SPointer<Shader>& shader, Int32 flags):
        _shader(shader),
        _flags(flags)
    {
    }

    Material::~Material()
    {
    }

    void Material::SetTexture(const std::string& textureName, const SPointer<Texture>& texture) const
    {
        auto it = _boundTextures.find(textureName);
        if(it != _boundTextures.end())
        {
            it->second = texture;
        }
        else
        {
            _boundTextures.emplace(std::make_pair(textureName, texture));
        }
    }
}
