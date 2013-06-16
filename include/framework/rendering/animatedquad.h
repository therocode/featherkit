#pragma once
#include <framework/rendering/quad.h>
#include <framework/rendering/animation.h>

namespace windbreeze
{
    class AnimatedQuad : public Quad
    {
        public:
            AnimatedQuad() : Quad() {}
            AnimatedQuad(float w, float h) : Quad(w, h) {}
            void setAnimation(Animation a);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
            void tick();
            void playAnimation(uint32_t startFrame = 0);
        protected:
            Animation currentAnimation;
            uint32_t clock;
    };
}
