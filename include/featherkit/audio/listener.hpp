#pragma once
#include <featherkit/audio/vec3f.hpp>

namespace fea
{
    class Listener
    {
        public:
            Listener();
            void setGain(float gain);
            float getGain() const;
            void setPosition(const Vec3F& position);
            const Vec3F& getPosition() const;
            void setVelocity(const Vec3F& velocity);
            const Vec3F& getVelocity() const;
            void setOrientation(const Vec3F& at, const Vec3F& up);
            const Vec3F& getOrientationAt() const;
            const Vec3F& getOrientationUp() const;
        private:
            float mGain;
            Vec3F mPosition;
            Vec3F mVelocity;
            Vec3F mAt;
            Vec3F mUp;
    };
}
