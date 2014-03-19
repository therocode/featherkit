#include <featherkit/audio/efx/compressor.hpp>

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
        alEffecti(mEffectId, AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
        alEffecti(mEffectId, AL_COMPRESSOR_ONOFF, mOn ? AL_TRUE : AL_FALSE);
    }
}
