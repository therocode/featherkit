#pragma once
#include <unordered_map>
#include <memory>
#include <framework/rendering/animation.h>
#include <stdexcept>

namespace windbreeze
{
    class InvalidAnimationException : public std::runtime_error 
    {
        public:
            InvalidAnimationException(const std::string& message) 
                : std::runtime_error(message) { };
    };

    class AnimationManager
    {
        public:
            void addAnimation(std::string name, Animation animation);
            std::weak_ptr<Animation> getByName(std::string name);
            std::weak_ptr<Animation> getById(AnimationId id);
            AnimationId getId(std::string name);
        private:
            std::hash<std::string> hasher;
            std::unordered_map<AnimationId, std::shared_ptr<Animation> > animations;
    };
}
