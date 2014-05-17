#pragma once
#include <fea/audio/audiostream.hpp>

namespace fea
{
    class Oscillator : public AudioStream
    {
        public:
            Oscillator();
            virtual void fillBufferData(size_t sampleIndex, std::vector<int16_t>& toFill) override;
            void setFrequency(float frequency);
        private:
            float mFrequency;
            double mTheta;
    };
    /** @addtogroup Audio
     *@{
     *  @class Oscillator
     *@}
     ***
     *  @class Oscillator
     *  @brief A stream which generates pure sine waves procedurally.
     ***
     *  @fn Oscillator::Oscillator()
     *  @brief Construct an Oscillator. 
     ***
     *  @fn void Oscillator::setFrequency(float frequency)
     *  @brief Set the frequency of the generated sine wave.
     *
     *  The default frequency is 440hz.
     *  @param frequency Frequency to use.
     ***/
}
