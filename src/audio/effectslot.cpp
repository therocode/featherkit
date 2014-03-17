#include <featherkit/audio/effectslot.hpp>
#define AL_ALEXT_PROTOTYPES
#include <efx.h>
#include <utility>

namespace fea
{
    EffectSlot::EffectSlot()
    {
        alGenAuxiliaryEffectSlots(1, &mSlotId);
    }
    
    EffectSlot::EffectSlot(EffectSlot&& other) :
        mSlotId(0)
    {
        std::swap(mSlotId, other.mSlotId);
    }

    EffectSlot& EffectSlot::operator=(EffectSlot&& other)
    {
        std::swap(mSlotId, other.mSlotId);
        
        return *this;
    }
    
    ALuint EffectSlot::getSlotId() const
    {
        return mSlotId;
    }

    EffectSlot::~EffectSlot()
    {
        if(mSlotId != 0)
            alDeleteAuxiliaryEffectSlots(1, &mSlotId);
    }
}
