#include <featherkit/audio/efx/distortion.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    Distortion::Distortion() : 
        mEdge(0.2f),
        mDistortionGain(0.05f),
        mLowPassCutoff(8000.0f),
        mEQCenter(3600.0f),
        mEQBandwidth(3600.0f)
    {
        update();
    }


    void Distortion::setEdge(float edge)
    {
        FEA_ASSERT(edge >= 0.0f && edge <= 1.0f, "Distortion edge must be between 0.0f and 1.0f");
        mEdge = edge;
        update();
    }

    float Distortion::getEdge() const
    {
        return mEdge;
    }

    void Distortion::setDistortionGain(float distortionGain)
    {
        FEA_ASSERT(distortionGain >= 0.01f && distortionGain <= 1.0f, "Distortion gain must be between 0.01f and 1.0f!");
        mDistortionGain = distortionGain;
        update();
    }

    float Distortion::getDistortionGain() const
    {
        return mDistortionGain;
    }

    void Distortion::setLowPassCutoff(float lowPassCutoff)
    {
        FEA_ASSERT(lowPassCutoff >= 80.0f && lowPassCutoff <= 24000.0f, "Distortion lowPassCutoff must be between 80.0f and 24000.0f!");
        mLowPassCutoff = lowPassCutoff;
        update();
    }

    float Distortion::getLowPassCutoff() const
    {
        return mLowPassCutoff;
    }

    void Distortion::setEQCenter(float eqCenter)
    {
        FEA_ASSERT(eqCenter >= 80.0f && eqCenter <= 24000.0f, "Distortion eqCenter must be between 80.0f and 24000.0f!");
        mEQCenter = eqCenter;
        update();
    }

    float Distortion::getEQCenter() const
    {
        return mEQCenter;
    }

    void Distortion::setEQBandwidth(float eqBandwidth)
    {
        FEA_ASSERT(eqBandwidth >= 80.0f && eqBandwidth <= 24000.0f, "Distortion eqBandwidth must be between 80.0f and 24000.0f!");
        mEQBandwidth = eqBandwidth;
        update();
    }

    float Distortion::getEQBandwidth() const
    {
        return mEQBandwidth;
    }

    void Distortion::update()
    {
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);
        alEffectf(getEffectId(), AL_DISTORTION_EDGE, mEdge);
        alEffectf(getEffectId(), AL_DISTORTION_GAIN, mDistortionGain);
        alEffectf(getEffectId(), AL_DISTORTION_LOWPASS_CUTOFF, mLowPassCutoff);
        alEffectf(getEffectId(), AL_DISTORTION_EQCENTER, mEQCenter);
        alEffectf(getEffectId(), AL_DISTORTION_EQBANDWIDTH, mEQBandwidth);
    }
}
