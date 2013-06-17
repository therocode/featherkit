#pragma once
#include <framework/rendering/quad.h>
#include <framework/rendering/animation.h>

namespace windbreeze
{
    class AnimatedQuad : public Quad
    {
        public:
            AnimatedQuad() : Quad(), currentAnimation(Animation(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f))) {}
            AnimatedQuad(float w, float h) : Quad(w, h), currentAnimation(Animation(glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f))) {}
            void setAnimation(Animation a);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
            void tick();
            void playAnimation(uint32_t startFrame = 0);
        protected:
            Animation currentAnimation;
            uint32_t clock;
    };
}
