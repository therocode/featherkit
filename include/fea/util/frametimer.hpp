#pragma once
#include <chrono>
#include <deque>
#include <fea/assert.hpp>

namespace fea
{
    class FEA_API FrameTimer
    {
        public:
            FrameTimer(int32_t pastFrames = 300);
            void sample();
            float fps() const;
            float avgFrameTime() const;
            float lastFrameTime() const;
            float deviationFactor() const;
            int64_t frameCount() const;
        private:
            std::chrono::high_resolution_clock mClock;
            std::chrono::high_resolution_clock::time_point mLastTime;
            std::deque<float> mLastFrameTimes;
            int32_t mMaxPastFrames;
            bool mHasAtLeastOneTimePoint;
            int64_t mFrameCount;
    };
}
