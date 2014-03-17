#pragma once
#include <al.h>

namespace fea
{
    class EffectSlot
    {
            EffectSlot();
            EffectSlot(const EffectSlot& other) = delete;
            EffectSlot(EffectSlot&& other);
            EffectSlot& operator=(const EffectSlot& other) = delete; 
            EffectSlot& operator=(EffectSlot&& other); 
            ~EffectSlot();
            ALuint getSlotId() const;
        private:
            ALuint mSlotId;
    };
}
