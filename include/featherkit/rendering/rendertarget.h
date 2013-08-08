#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
#include <featherkit/rendering/texture.h>

namespace fea
{
    class Renderer2DBackend;

    class RenderTarget
    {
        public:
            RenderTarget();
            RenderTarget(Renderer2DBackend& backend, int32_t i, uint32_t w, uint32_t h, Texture&& tex);
            RenderTarget(RenderTarget&& other);
            RenderTarget(const RenderTarget& other) = delete;
            RenderTarget& operator=(RenderTarget&& other);
            int32_t getId() const;
            glm::uvec2 getSize() const;
            const Texture& getTexture() const;
            ~RenderTarget();
        private:
            Renderer2DBackend* creator;
            int32_t id;
            uint32_t width;
            uint32_t height;
            Texture texture;
    };
}
