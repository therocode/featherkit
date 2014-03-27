#include <featherkit/audio/efx/ringmodulator.hpp>
#include <featherkit/assert.hpp>

namespace fea
{
    RingModulator::RingModulator() : 
        mFrequency(440.0f),
        mHighPassCutoff(800.0f),
        mWaveform(SINE)
    {
        update();
    }

    void RingModulator::setFrequency(float frequency)
    {
        FEA_ASSERT(frequency >= 0.0f && frequency <= 8000.0f, "RingModulator frequency must be between 0.0f and 8000.0f!");
        mFrequency = frequency;
        update();
    }

    float RingModulator::getFrequency() const
    {
        return mFrequency;
    }

    void RingModulator::setHighPassCutoff(float highPassCutoff)
    {
        FEA_ASSERT(highPassCutoff >= 0.0f && highPassCutoff <= 24000.0f, "RingModulator highPassCutoff must be between 0.0f and 24000.0f!");
        mHighPassCutoff = highPassCutoff;
        update();
    }

    float RingModulator::getHighPassCutoff() const
    {
        return mHighPassCutoff;
    }

    void RingModulator::setWaveform(Waveform waveform)
    {
        mWaveform = waveform;
        update();
    }

    RingModulator::Waveform RingModulator::getWaveform() const
    {
        return mWaveform;
    }

    void RingModulator::update()
    {
        alEffecti(getEffectId(), AL_EFFECT_TYPE, AL_EFFECT_RING_MODULATOR);
        alEffectf(getEffectId(), AL_RING_MODULATOR_FREQUENCY, mFrequency);
        alEffectf(getEffectId(), AL_RING_MODULATOR_HIGHPASS_CUTOFF, mHighPassCutoff);
        alEffecti(getEffectId(), AL_RING_MODULATOR_WAVEFORM, mWaveform);
    }
}
