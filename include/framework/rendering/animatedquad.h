#pragma once
#include <framework/rendering/quad.h>
#include <framework/rendering/animation.h>
#include <unordered_map>
#include <memory>

namespace windbreeze
{
    class AnimatedQuad : public Quad
    {
        public:
            AnimatedQuad() : Quad() {}
            AnimatedQuad(float w, float h) : Quad(w, h) {}
            void addAnimation(AnimationId id, std::weak_ptr<Animation> animation);
            void setAnimation(AnimationId id);
            virtual void getRenderData(RenderData& renderData, uint32_t time) const override;
            void tick();
            void playAnimation(uint32_t startFrame = 0);
        protected:
            std::weak_ptr<Animation> currentAnimation;
            std::unordered_map<AnimationId, std::weak_ptr<Animation> > animations;

            uint32_t clock = 0;
            uint32_t currentFrame = 0;
            bool animate = true;
    };
}
