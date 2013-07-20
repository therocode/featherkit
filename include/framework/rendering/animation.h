#pragma once
#include <framework/glm/glm.hpp>
#include <stdint.h>

namespace windbreeze
{
    enum AnimationBehaviour { FORWARDS, BACKWARDS };

    using AnimationId = size_t;

    class Animation
    {
        public:
            Animation();
            Animation(glm::vec2 fStart, glm::vec2 fSize, uint32_t fAmount = 1, uint32_t d = 1, bool l = true, AnimationBehaviour ab = FORWARDS);
            void getConstraints(glm::vec2& constraintX, glm::vec2& constraintY, uint32_t frame) const;
            uint32_t getFrameAmount() const;
            uint32_t getDelay() const;
            bool getLoop() const;
            AnimationBehaviour getAnimationBehaviour() const;
        private:
            glm::vec2 start;
            glm::vec2 frameSize;
            uint32_t frameAmount;
            uint32_t delay;
            bool loop;
            AnimationBehaviour animBehaviour;
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
     *  @fn Animation::Animation(glm::vec2 fStart, glm::vec2 fSize, uint32_t fAmount = 1, uint32_t d = 1, bool l = true, AnimationBehaviour ab = FORWARDS)
     *  @brief Construct an animation.
     *  @param fStart Starting point. The top left corner of the first animation frame.
     *  @param fSize Width and height of one animation frame.
     *  @param fAmount Total amount of frames in the animation.
     *  @param d Amount of ticks between every animation frame.
     *  @param l Describes if the animation is looping or not.
     *  @param ab Can currently be FORWARDS or BACKWARDS, and defines if the frame is animated backwards or not.
     ***
     *  @fn void Animation::getConstraints(glm::vec2& constraintX, glm::vec2& constraintY, uint32_t frame) const
     *  @brief Get constraints.
     *
     *  The constraints are used by the Renderer2D to display the correct subrectangle of the sprite sheet. They define a rectangle which the current frame lies in. This function is called automatically in the rendering process and is seldom used manually.
     *  @param constraintX Vector in which to put the X constraints.
     *  @param constraintY Vector in which to put the Y constraints.
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
