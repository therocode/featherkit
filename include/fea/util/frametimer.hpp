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
            float avgDeviation() const;
            int64_t frameCount() const;
        private:
            std::chrono::high_resolution_clock mClock;
            std::chrono::high_resolution_clock::time_point mLastTime;
            std::deque<float> mLastFrameTimes;
            int32_t mMaxPastFrames;
            bool mHasAtLeastOneTimePoint;
            int64_t mFrameCount;
    };

    /** @addtogroup Util
     *@{
     *  @class FrameTimer
     *@}
     ***
     *  @class FrameTimer
     *  @brief Utility class to get various metrics on how fast frames are progressing.
     *
     *  The most common usage of this class would be to get the frames per second (FPS) of the application. Other metrics than can be retrieved are average frame time, last frame time, and average deviation. To use this class, call the sample() method every time you want to sample a time point (for example at the end of every frame).
     ***
     *  @fn FrameTimer::FrameTimer(int32_t pastFrames = 300)
     *  @brief Construct a FrameTimer and decide how many frames to take into account.
     *
     *  Assert/undefined behavior if the pastFrames amount is less than 2.
     *  @param pastFrames The amount of past frames that the timer uses internally to calculate averages. The bigger the number, the more accurate readings but also more overhead. Given a value of N, it will take N frames before the timer is the most accurate.
     ***
     *  @fn void FrameTimer::sample()
     *  @brief Tell the timer to sample frame time.
     *  
     *  This method is meant to be called at fixed intervals in your code which represents what you want to measure. If you want to measure frame times in an application for example, then put this at the end of the main loop.
     ***
     *  @fn float FrameTimer::fps() const
     *  @brief Get the current FPS value.
     *  
     *  The FPS is a measure of the average amount of frames passed per second.
     *  @return The FPS in seconds.
     ***
     *  @fn float FrameTimer::avgFrameTime() const
     *  @brief Get the average frame time in milliseconds.
     *  
     *  @return The average amount of milliseconds that a frame takes to process.
     ***
     *  @fn float FrameTimer::lastFrameTime() const
     *  @brief Get the time that the last frame took in milliseconds.
     *  
     *  @return Last frame time in milliseconds.
     ***
     *  @fn float FrameTimer::avgDeviation() const
     *  @brief Get the average deviation from the average frame time.
     *  
     *  This method returns the average deviation from the average frame time of all the rememebered sample points. The result is given in milliseconds. A higher deviation value means that the frame time is unstable and fluctuates a lot.
     *  @return The average deviation in milliseconds.
     ***
     *  @fn int64_t FrameTimer::frameCount() const
     *  @brief Get the amount of total frames that passed.
     *  
     *  @return The total amount of passed frames
     ***/
}
