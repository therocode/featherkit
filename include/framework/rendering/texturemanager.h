#pragma once
#include <unordered_map>

namespace windbreeze
{
    template<class Texture>
    class TextureManager
    {
        public:
            void addTexture(std::string name, Texture texture);
            const Texture& getTexture(const std::string& name) const;
        private:
            std::unordered_map<std::string, Texture> textures;
    };
    
    template<class Texture>
    void TextureManager<Texture>::addTexture(std::string name, Texture texture)
    {
        textures.emplace(name, texture);
    }

    template<class Texture>
    const Texture& TextureManager<Texture>::getTexture(const std::string& name) const
    {
        return textures.at(name);
    }
}
