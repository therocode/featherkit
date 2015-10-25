#pragma once
#include <fea/config.hpp>
#include <fea/rendering/quad.hpp>
#include <fea/rendering/animation.hpp>
#include <unordered_map>
#include <memory>

namespace fea
{
    class FEA_API AnimatedQuad : public Quad
    {
        public:
            AnimatedQuad();
            AnimatedQuad(const glm::vec2& size);
            void setAnimation(const Animation& animation, bool play = true);
            const Animation& getAnimation() const;
            virtual void setTexture(const Texture& texture) override;
            void tick();
            void playAnimation(uint32_t startFrame = 0);
            void stopAnimation();
            void setAnimationFrame(uint32_t frame);
            uint32_t getAnimationFrame() const;
            bool isPlaying() const;
            void onAnimationEnd(std::function<void(void)> callback = nullptr);
        private:
            void setConstraints();
            void animateForwards();
            void animateBackwards();
            void animateBounce();
            void animateInvBounce();
            const Animation* currentAnimation;

            uint32_t mClock;
            uint32_t mCurrentFrame;
            bool mAnimate;
            bool mBack;
            std::function<void(void)> mOnEnd;
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
     *  Uses the Quad::Quad() constructor.
     ***
     *  @fn AnimatedQuad::AnimatedQuad(const glm::vec2& size)
     *  @brief Construct an AnimatedQuad with the given size.
     *  
     *  Uses the Quad::Quad(const glm::vec2& size) constructor.
     *  Assert/undefined behavior when size is less than one in either of the dimensions.
     *  @param size Size.
     ***
     *  @fn void AnimatedQuad::setAnimation(const Animation& animation, bool play = true)
     *  @brief Change the current animation.
     *
     *  When an animation is set, it will start off at the first frame. It can start both as playing or as still and be played at a later time using the AnimatedQuad::playAnimation function.
     *  @param animation Animation to use.
     *  @param play Set this to false if the animation sequence should not be played after being set.
     ***
     *  @fn AnimationId AnimatedQuad::getAnimation() const
     *  @brief Get current animation.
     *
     *  Assert/undefined behavior if no animation is set.
     *  @return Current animation ID.
     ***
     *  @fn void AnimatedQuad::tick()
     *  @brief Advance the animation one tick.
     *  
     *  This function should always be called on all AnimatedQuad instances every frame as it acts as the clock which drives the animation logic. If it isn't called, no animations will animate.
     ***
     *  @fn void AnimatedQuad::playAnimation(uint32_t startFrame = 0)
     *  @brief Start the animation sequence for the current set animation.
     *
     *  assert/undefined behavior if no animation is set.
     *  @param startFrame Animation frame from which the sequence should start. Default is 0.
     ***
     *  @fn void AnimatedQuad::stopAnimation()
     *  @brief Stop the current animation.
     *
     *  This makes the AnimatedQuad constantly display the frame it was up to in the animation sequence when the animation was stopped.
     ***
     *  @fn void AnimatedQuad::setAnimationFrame(uint32_t frame)
     *
     *  assert/undefined behavior if no animation is set.
     *  @brief Set the animation frame.
     *  @param frame Frame to set it to.
     ***
     *  @fn uint32 AnimatedQuad::getAnimationFrame() const
     *  @brief Get the current frame.
     *  @return Numerical index of the frame.
     ***
     *  @fn bool AnimatedQuad::isPlaying() const
     *  @brief Check if the animation is playing or not
     *  @return True if it is playing.
     ***
     *  @fn void AnimatedQuad::onAnimationEnd(std::function<void(void)> callback)
     *  @brief Add a callback to be called when the animation stops.
     *  
     *  An animation will only stop if it is set to not loop. Changing the animation does not count as stopping. To remove the callback set a new one using this function or call it without arguments to have no callback at all.
     *  @param callback Function object to call.
     **/
}
