#pragma once
#include <fea/config.hpp>
#include <fea/audio/audioeffect.hpp>

namespace fea
{
    class FEA_API Compressor : public AudioEffect
    {
        public:
            Compressor();
            void setOn(bool on);
            bool isOn() const;
        private:
            void update();
            bool mOn;
    };
    /** @addtogroup Audio
     *@{
     *  @class Compressor
     *@}
     ***
     *  @class Compressor
     *  @brief Compressor diminishes the dynamics of a sound by flattening out the audio curve.
     *
     *  This effect is based directly on the <a href="https://docs.google.com/viewer?url=http%3A%2F%2Fzhang.su%2Fseal%2FEffectsExtensionGuide.pdf">EFX specification</a> and the parameters are hence not documented here. So have a look there to find out all about what the effect does, and what default values they have and which values they expect.
     *
     *  Assert/undefined behavior if an illegal value is given to any of the properties of the effect.
     ***/
}
