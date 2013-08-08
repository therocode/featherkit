#pragma once
#include <stdint.h>

namespace fea
{
    class Renderer2DBackend;

    class Texture
    {
        public:
            Texture();
            Texture(Renderer2DBackend& backend, int32_t i);
            Texture(Texture&& other);
            Texture(const Texture& other) = delete;
            Texture& operator=(Texture&& other);
            int32_t getId() const;
            ~Texture();
        private:
            Renderer2DBackend* creator;
            int32_t id;
    };
}
