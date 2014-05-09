#include <featherkit/audio/effectslot.hpp>
#if !defined(__EMSCRIPTEN__)
#define AL_ALEXT_PROTOTYPES
#include <AL/efx.h>
#endif
#include <utility>

namespace fea
{
    EffectSlot::EffectSlot() :
        mFilter(nullptr)
    {
#if !defined(__EMSCRIPTEN__)
        alGenAuxiliaryEffectSlots(1, &mSlotId);
#endif
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
#if !defined(__EMSCRIPTEN__)
        if(mSlotId != 0)
            alDeleteAuxiliaryEffectSlots(1, &mSlotId);
#endif
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
