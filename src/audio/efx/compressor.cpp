#include <fea/audio/efx/compressor.hpp>
#if !defined(FEA_NO_EFX)
#include "efx.h"
#endif

namespace fea
{
    Compressor::Compressor() : 
        mOn(true)
    {
        update();
    }


    void Compressor::setOn(bool on)
    {
        mOn = on;
        update();
    }

    bool Compressor::isOn() const
    {
        return mOn;
    }

    void Compressor::update()
    {
#if !defined(FEA_NO_EFX)
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
        alEffecti(getEffectId(), AL_COMPRESSOR_ONOFF, mOn ? AL_TRUE : AL_FALSE);
#endif
    }
}
