#pragma once
#include <fea/config.hpp>
#include <fea/audio/audioeffect.hpp>

namespace fea
{
    class FEA_API RingModulator : public AudioEffect
    {
        public:
            enum Waveform {SINE = 0, SAW = 1, SQUARE = 2};

        public:
            RingModulator();
            void setFrequency(float frequency);
            float getFrequency() const;
            void setHighPassCutoff(float highPassCutoff);
            float getHighPassCutoff() const;
            void setWaveform(Waveform waveform);
            Waveform getWaveform() const;
        private:
            void update();
            float mFrequency;
            float mHighPassCutoff;
            Waveform mWaveform;
    };
    /** @addtogroup Audio
     *@{
     *  @class RingModulator
     *@}
     ***
     *  @class RingModulator
     *  @brief A ring modulator can be used to create tremolo or weird tonal effects.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
