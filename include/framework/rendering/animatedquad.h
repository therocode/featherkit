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
    /** @addtogroup Render2D
     *@{
     *  @class AnimatedQuad
     *@}
     ***
     *  @class AnimatedQuad
     *  @brief A Quad capable of manipulating its displayed texture by cycling through animation frames.
     ***
     *  @fn AnimatedQuad::AnimatedQuad()
     *  @brief Construct an AnimatedQuad.
     *  
     *  Uses the AnimatedQuad::Quad() constructor.
     ***
     *  @fn AnimatedQuad::AnimatedQuad(float w, float h)
     *  @brief Construct an AnimatedQuad with the given size.
     *  
     *  Uses the AnimatedQuad::Quad(float w, float h) constructor.
     *  @param w Width.
     *  @param h Height.
     ***
     *  @fn void AnimatedQuad::addAnimation(AnimationId id, std::weak_ptr<Animation> animation)
     *  @brief Add an animation.
     * 
     *  After an animation is added, the animation can be set and played using AnimatedQuad::setAnimation and AnimatedQuad::playAnimation.
     *  @param id Id to be used to refer to the animation.
     *  @param animation Pointer to the animation to add. Pointers to animations can be gotten from the AnimationManager.
     **/
}
