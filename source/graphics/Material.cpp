#include "ndrpch.h"
#include "Material.h"

namespace NDR
{
    Material::Material(const SharedPtr<Shader>& shader, int32_t flags):
        _shader(shader),
        _flags(flags)
    {
    }

    Material::~Material()
    {
    }

    void Material::SetTexture(const std::string& textureName, const SharedPtr<Texture>& texture) const
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
