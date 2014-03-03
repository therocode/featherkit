#include <featherkit/audio/listener.hpp>
#include <featherkit/assert.hpp>
#include <string>

namespace fea
{
    Listener::Listener() :
        mGain(1.0f),
        mPosition({0.0f, 0.0f, 0.0f}),
        mVelocity({0.0f, 0.0f, 0.0f}),
        mAt({0.0f, 0.0f, -1.0f}),
        mUp({0.0f, 1.0f, 0.0f})
    {
    }

    void Listener::setGain(float gain)
    {
        FEA_ASSERT(gain > 0.0f, "Trying to set gain to zero or below! Given " + std::to_string(gain));
        mGain = gain;
    }

    float Listener::getGain() const
    {
        return mGain;
    }

    void Listener::setPosition(const Vec3F& position)
    {
        mPosition = position;
    }

    const Vec3F& Listener::getPosition() const
    {
        return mPosition;
    }

    void Listener::setVelocity(const Vec3F& velocity)
    {
        mVelocity = velocity;
    }

    const Vec3F& Listener::getVelocity() const
    {
        return mVelocity;
    }

    void Listener::setOrientation(const Vec3F& at, const Vec3F& up)
    {
        mAt = at;
        mUp = up;
    }

    const Vec3F& Listener::getOrientationAt() const
    {
        return mAt;
    }

    const Vec3F& Listener::getOrientationUp() const
    {
        return mUp;
    }
}
