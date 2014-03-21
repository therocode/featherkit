#pragma once
#include <chrono>
#include <set>
#include <featherkit/audio/vec3f.hpp>
#include <featherkit/audio/audiofilter.hpp>

namespace fea
{
    class AudioFilter;

    class AudioBase
    {
        public:
            AudioBase();
            void setPosition(const Vec3F& position);
            const Vec3F& getPosition() const;
            void setVelocity(const Vec3F& velocity);
            const Vec3F& getVelocity() const;
            void setPitch(float pitch);
            float getPitch() const;
            void setGain(float pitch);
            float getGain() const;
            void setAttenuationFactor(float attenuationFactor);
            float getAttenuationFactor() const;
            void setAttenuationDistance(float attenuationDistance);
            float getAttenuationDistance() const;
            void setLooping(bool loop);
            bool isLooping() const;
            void setRelative(bool relative);
            bool isRelative();
            void setPlayOffset(std::chrono::milliseconds timePoint);
            std::chrono::milliseconds getPlayOffset() const;
            void addEffectSend(size_t slot);
            const std::set<size_t> getEffectSends() const;
            void setFilter(const AudioFilter& filter);
            const AudioFilter& getFilter() const;
            bool hasFilter() const;
        protected:
            Vec3F mPosition;
            Vec3F mVelocity;
            float mPitch;
            float mGain;
            float mAttenuationFactor;
            float mAttenuationDistance;
            bool mLooping;
            bool mRelative;
            std::chrono::milliseconds mOffset;
            std::set<size_t> mEffectSends;
            const AudioFilter* mFilter;
    };
}
