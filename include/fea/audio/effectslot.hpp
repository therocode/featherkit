#pragma once
#include <fea/config.hpp>
#include <fea/audio/openal.hpp>

namespace fea
{
    class AudioFilter;

    class FEA_API EffectSlot
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
    /** @addtogroup Audio
     *@{
     *  @class EffectSlot
     *@}
     ***
     *  @class EffectSlot
     *  @brief Represents an effect slot.
     *
     *  This class manages the OpenAL effect slot resource. It is used by the AudioPlayer and should not need to be used manually.
     ***
     *  @fn EffectSlot::EffectSlot()
     *  @brief Construct an EffectSlot. 
     ***
     *  @fn EffectSlot::EffectSlot(const EffectSlot& other) = delete
     *  @brief Deleted copy constructor.
     ***
     *  @fn EffectSlot::EffectSlot(EffectSlot&& other)
     *  @brief Move an EffectSlot.
     ***
     *  @fn EffectSlot& EffectSlot::operator=(const EffectSlot& other) = delete
     *  @brief Deleted assignment operator.
     ***
     *  @fn EffectSlot& EffectSlot::operator=(EffectSlot&& other)
     *  @brief Move an EffectSlot.
     ***
     *  @fn EffectSlot::~EffectSlot()
     *  @brief Destroy an EffectSlot.
     ***
     *  @fn ALuint EffectSlot::getSlotId() const
     *  @brief Get the ID.
     *  @return ID of the slot.
     ***
     *  @fn void EffectSlot::setFilter(const AudioFilter& filter)
     *  @brief Set a filter to use for the slot.
     *  @param filter Filter to use.
     ***
     *  @fn const AudioFilter& EffectSlot::getFilter() const
     *  @brief Get the current filter.
     *
     *  Assert/undefined behavior if no filter is set. Check with hasFilter.
     *  @return Filter in use.
     ***
     *  @fn bool EffectSlot::hasFilter() const
     *  @brief Check if a filter is in use.
     *  @return True if a filter is in use.
     ***
     *  @fn void EffectSlot::clearFilter()
     *  @brief Clear any filter in use.
     *
     *  This makes the effect slot not use any filters.
     ***/
}
