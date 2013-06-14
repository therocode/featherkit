#pragma once
#include <unordered_map>
#include <iostream>

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
        std::cout << "adding texture called " << name << "\n";
        textures.emplace(name, texture);
        std::cout << "now there are " << textures.size() << " textures in it\n";
    }

    template<class Texture>
    const Texture& TextureManager<Texture>::getTexture(const std::string& name) const
    {
        std::cout << "getting texture called " << name << " out of all " << textures.size() << " textures\n";
        return textures.at(name);
    }
}
