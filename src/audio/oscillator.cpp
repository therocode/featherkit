#include <featherkit/audio/oscillator.hpp>
#include <limits>
#include <cmath>
#include <iostream>

const double pi = 3.14159;

namespace fea
{
    Oscillator::Oscillator() :
        mFrequency(440.0f),
        mTheta(0.0)
    {
        setStreamProperties(1, 48000);
        reset();
    }

    void Oscillator::fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill)
    {
        size_t desiredSampleAmount = toFill.size();

        double deltaTheta = 2.0 * pi * ((double)mFrequency / (double)getSampleRate());

        for(size_t i = 0; i < desiredSampleAmount; i++)
        {
            toFill[i] = (int16_t) (std::numeric_limits<int16_t>::max() * sin(mTheta));
            mTheta += deltaTheta;

            if(mTheta > 2.0 * pi) 
                mTheta = mTheta - 2.0 * pi;
        }
    }

    void Oscillator::setFrequency(float frequency)
    {
        mFrequency = frequency;
        reset();
    }
}
