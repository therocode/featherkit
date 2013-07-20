#pragma once
#include <unordered_map>
#include <memory>
#include <framework/rendering/animation.h>
#include <stdexcept>

using namespace fk;

namespace fku
{
    class InvalidAnimationException : public std::runtime_error 
    {
        public:
            InvalidAnimationException(const std::string& message);
    };

    class AnimationManager
    {
        public:
            void addAnimation(std::string name, Animation animation);
            std::weak_ptr<Animation> getByName(std::string name) const;
            std::weak_ptr<Animation> getById(AnimationId id) const;
            AnimationId getId(std::string name) const;
        private:
            std::hash<std::string> hasher;
            std::unordered_map<AnimationId, std::shared_ptr<Animation> > animations;
    };
    /** @addtogroup Render2D
     *@{
     *  @class InvalidAnimationException
     *  @class AnimationManager
     *@}
     ***
     *  @class InvalidAnimationException
     *  @brief Exception used by the AnimationManager when something goes wrong.
     ***
     *  @fn InvalidAnimationException::InvalidAnimationException(const std::string& message)
     *  @brief Construct an exception to throw containing a message.
     *  @param message Message further describing the error.
     ***
     *  @class AnimationManager
     *  @brief Utility class for keeping track of animations.
     ***
     *  @fn void AnimationManager::addAnimation(std::string name, Animation animation)
     *  @brief Add an animation with a name.
     *  @param name Name of the animation.
     *  @param animation Animation.
     ***
     *  @fn std::weak_ptr<Animation> AnimationManager::getByName(std::string name) const
     *  @brief Get an animation.
     *  @param name Name of the animation.
     *  @return A pointer to the animation.
     ***
     *  @fn std::weak_ptr<Animation> AnimationManager::getById(AnimationId id) const
     *  @brief Get an animation.
     *  @param id of the animation.
     *  @return A pointer to the animation.
     ***
     *  @fn AnimationId AnimationManager::getId(std::string name) const
     *  @brief Get the ID of an animation.
     *  @param name Name of the animation.
     *  @return ID.
     ***/
}
