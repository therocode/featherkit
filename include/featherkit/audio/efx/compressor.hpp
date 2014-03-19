#pragma once
#include <featherkit/audio/audioeffect.hpp>

namespace fea
{
    class Compressor : public AudioEffect
    {
        public:
            Compressor();
            void setOn(bool on);
            bool isOn() const;
        private:
            void update();
            bool mOn;
    };
}
