#pragma once
#include <fea/config.hpp>
#include <fea/audio/audiofilter.hpp>

namespace fea
{
    class FEA_API LowPassFilter : public AudioFilter
    {
        public:
            LowPassFilter();
            void setGain(float gain);
            float getGain() const;
            void setGainHF(float gainHF);
            float getGainHF() const;
        private:
            void update();
            float mGain;
            float mGainHF;
    };
    /** @addtogroup Audio
     *@{
     *  @class LowPassFilter
     *@}
     ***
     *  @class LowPassFilter
     *  @brief LowPassFilter muffles the sound by diminishing higher frequencies.
     *
     *  This filter is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the filter does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the filter.
     ***/
}
