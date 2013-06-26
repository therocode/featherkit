#include <framework/util/rendering/animationmanager.h>
#include <sstream>

namespace windbreeze
{
    void AnimationManager::addAnimation(std::string name, Animation animation)
    {
        animations.emplace(hasher(name), std::make_shared<Animation>(animation));
    }
    
    std::weak_ptr<Animation> AnimationManager::getByName(std::string name) const
    {
        auto animation = animations.find(hasher(name));

        if(animation == animations.end())
        {
            std::stringstream ss;
            ss << "Error! Animation called '" << name << "' does not exist!\n";
            throw(InvalidAnimationException(ss.str()));
        }

        return animation->second;
    }

    std::weak_ptr<Animation> AnimationManager::getById(AnimationId id) const
    {
        return animations.at(id);
    }
    
    AnimationId AnimationManager::getId(std::string name) const
    {
        return hasher(name);
    }
}
