#pragma once
#include <chrono>

namespace fea
{
    class AudioBase
    {
        public:
            AudioBase();
            void setLooping(bool loop);
            bool getLooping() const;
            void setPlayOffset(std::chrono::milliseconds timePoint);
            std::chrono::milliseconds getPlayOffset() const;
        protected:
            bool mLooping;
            std::chrono::milliseconds mOffset;
    };
}
