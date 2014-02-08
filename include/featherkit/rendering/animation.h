#pragma once
#include <glm/glm.hpp>
#include <stdint.h>

namespace fea
{
    enum AnimationBehaviour { FORWARDS, BACKWARDS, BOUNCE, INV_BOUNCE, RANDOM };

    using AnimationId = size_t;

    class Animation
    {
        public:
            Animation();
            Animation(const glm::vec2& frameStart, const glm::vec2& frameSize, uint32_t frameAmount = 1, uint32_t delay = 1, bool loop = true, AnimationBehaviour animationBehaviour = FORWARDS);
            void getConstraints(glm::vec4& constraints, uint32_t frame) const;
            uint32_t getFrameAmount() const;
            uint32_t getDelay() const;
            bool getLoop() const;
            AnimationBehaviour getAnimationBehaviour() const;
        private:
            glm::vec2 mStart;
            glm::vec2 mFrameSize;
            uint32_t mFrameAmount;
            uint32_t mDelay;
            bool mLoop;
            AnimationBehaviour mAnimBehaviour;
    };
    /** @addtogroup Render2D
     *@{
     *  @enum AnimationBehaviour
     *  @class Animation
     *@}
     ***
     *  @enum AnimationBehaviour
     *  @brief Describes different types of animation behaviours.
     ***
     *  @class Animation
     *  @brief Represents an animation for an AnimatedQuad.
     *
     *  Animations use animation frames from a single texture at a time. In other words a sprite sheet. An animation then defines a starting point in the sprite sheet, followed by the size of a frame and the amount of frames. There is also a setting to control the speed of the animation and if it should loop or not and if it should animate forwards or backwards. 
     *
     *  All values defining location on the sprite sheet is in percent of the total texture size.
     ***
     *  @fn Animation::Animation(const glm::vec2& frameStart, const glm::vec2& frameSize, uint32_t frameAmount = 1, uint32_t delay = 1, bool loop = true, AnimationBehaviour animationBehaviour = FORWARDS)
     *  @brief Construct an animation. All positioning values are in percent (between 0.0 and 1.0) of the total texture size.
     *  @param frameStart Starting point. The top left corner of the first animation frame.
     *  @param frameSize Width and height of one animation frame.
     *  @param frameAmount Total amount of frames in the animation.
     *  @param delay Amount of ticks between every animation frame.
     *  @param loop Describes if the animation is looping or not.
     *  @param animationBehaviour Can currently be FORWARDS or BACKWARDS, and defines if the frame is animated backwards or not.
     ***
     *  @fn void Animation::getConstraints(glm::vec4& constraints, uint32_t frame) const
     *  @brief Get constraints.
     *
     *  The constraints are used by the Renderer2D to display the correct subrectangle of the texture. They define a rectangle which the current frame lies in. This function is called automatically in the rendering process and is seldom used manually.
     *  @param constraints Vector in which to put the constraints.
     *  @param frame Frame to get the constraints of.
     ***
     *  @fn uint32_t Animation::getFrameAmount() const
     *  @brief Get amount of frames.
     *  @return Amount.
     ***
     *  @fn uint32_t Animation::getDelay() const
     *  @brief Get amount of ticks between every animation frame.
     *  @return Amount of ticks.
     ***
     *  @fn bool Animation::getLoop() const
     *  @brief Check if the animation will loop.
     *  @return True if loop is set.
     ***
     *  @fn AnimationBehaviour Animation::getAnimationBehaviour() const
     *  @brief Get the animation behaviour of the animation.
     *  @return Animation behaviour.
     ***/
}
