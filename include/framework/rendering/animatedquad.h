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
        protected:
            Animation currentAnimation;
    };
}
