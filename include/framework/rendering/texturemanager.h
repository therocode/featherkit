#pragma once
#include <unordered_map>
#include <stdexcept>
#include <sstream>

namespace windbreeze
{
    class InvalidTextureException : public std::runtime_error 
    {
        public:
            InvalidTextureException(const std::string& message) 
                : std::runtime_error(message) { };
    };

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
        auto texture = textures.find(name);
        if(texture == textures.end())
        {
            std::stringstream ss;
            ss << "Error! Texture called '" << name << "' does not exist!\n";
            throw(InvalidTextureException(ss.str()));
        }
        else
        {
            return textures.at(name);
        }
    }
}
