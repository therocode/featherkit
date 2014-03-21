#include <featherkit/audio/effectslot.hpp>
#define AL_ALEXT_PROTOTYPES
#include <efx.h>
#include <utility>

namespace fea
{
    EffectSlot::EffectSlot() :
        mFilter(nullptr)
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

    EffectSlot::~EffectSlot()
    {
        if(mSlotId != 0)
            alDeleteAuxiliaryEffectSlots(1, &mSlotId);
    }
    
    ALuint EffectSlot::getSlotId() const
    {
        return mSlotId;
    }

    void EffectSlot::setFilter(const AudioFilter& filter)
    {
        mFilter = &filter;
    }

    const AudioFilter& EffectSlot::getFilter() const
    {
        return *mFilter;
    }
    
    bool EffectSlot::hasFilter() const
    {
        return mFilter != nullptr;
    }

    void EffectSlot::clearFilter()
    {
        mFilter = nullptr;
    }
}
