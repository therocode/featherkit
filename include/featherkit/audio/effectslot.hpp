#pragma once
#include <al.h>

namespace fea
{
    class AudioFilter;

    class EffectSlot
    {
        public:
            EffectSlot();
            EffectSlot(const EffectSlot& other) = delete;
            EffectSlot(EffectSlot&& other);
            EffectSlot& operator=(const EffectSlot& other) = delete; 
            EffectSlot& operator=(EffectSlot&& other); 
            ~EffectSlot();
            ALuint getSlotId() const;
            void setFilter(const AudioFilter& filter);
            const AudioFilter& getFilter() const;
            bool hasFilter() const;
            void clearFilter();
        private:
            ALuint mSlotId;
            const AudioFilter* mFilter;
    };
}
