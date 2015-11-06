#include <fea/util/frametimer.hpp>
#include <algorithm>

namespace fea
{
    FrameTimer::FrameTimer(int32_t pastFrames):
        mMaxPastFrames(pastFrames),
        mHasAtLeastOneTimePoint(false),
        mFrameCount(0)
    {
    }

    void FrameTimer::sample()
    {
        if(mHasAtLeastOneTimePoint)
        {
            auto newTime = mClock.now();

            auto elapsedMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(newTime - mLastTime).count();
            float elapsedMilliseconds = elapsedMicroseconds / 1000.0f;

            mLastFrameTimes.push_back(elapsedMilliseconds);
            if(mLastFrameTimes.size() > mMaxPastFrames)
                mLastFrameTimes.pop_front();

            mLastTime = newTime;
        }
        else
        {
            mLastTime = mClock.now();
            mHasAtLeastOneTimePoint = true;
        }

        mFrameCount++;
    }

    float FrameTimer::fps() const
    {
        float average = avgFrameTime();

        if(average > 0.0f)
            return 1000.0f / average;
        else
            return 0.0f;
    }

    float FrameTimer::avgFrameTime() const
    {
        if(!mLastFrameTimes.empty())
        {
            float totalTime = std::accumulate(mLastFrameTimes.begin(), mLastFrameTimes.end(), 0.0f);

            return totalTime / mLastFrameTimes.size();
        }
        else
            return 0.0f;
    }

    float FrameTimer::lastFrameTime() const
    {
        if(!mLastFrameTimes.empty())
            return mLastFrameTimes.back();
        else
            return 0.0f;
    }

    float FrameTimer::deviationFactor() const
    {
        std::deque<float> frameTimes(mMaxPastFrames, 0.0f);
        std::copy(mLastFrameTimes.begin(), mLastFrameTimes.end(), frameTimes.begin());
        float averageFrameTime = avgFrameTime();

        float deviationAccumulator = 0.0f;

        for(float frameTime : frameTimes)
            deviationAccumulator += std::abs(frameTime - averageFrameTime);

        return deviationAccumulator / mMaxPastFrames;
    }

    int64_t FrameTimer::frameCount() const
    {
        return mFrameCount;
    }
}
