#include <framework/rendering/animationmanager.h>

namespace windbreeze
{
    void AnimationManager::addAnimation(std::string name, Animation animation)
    {
        animations.emplace(hasher(name), std::make_shared<Animation>(animation));
    }
    
    std::weak_ptr<Animation> AnimationManager::getByName(std::string name)
    {
        return animations.at(hasher(name));
    }

    std::weak_ptr<Animation> AnimationManager::getById(AnimationId id)
    {
        return animations.at(id);
    }
    
    AnimationId AnimationManager::getId(std::string name)
    {
        return hasher(name);
    }
}
