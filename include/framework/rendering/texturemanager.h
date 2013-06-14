#pragma once
#include <unordered_map>

namespace windbreeze
{
    template<class Texture, class TextureID>
    class TextureManager
    {
        public:
            const Texture& getTexture(const TextureID& id) const;
        private:
            std::unordered_map<TextureID, Texture> textures;
    };

    template<class Texture, class TextureID>
    const Texture& TextureManager<Texture, TextureID>::getTexture(const TextureID& id) const
    {
        return textures.at(id);
    }
}
