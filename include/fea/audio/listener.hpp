#pragma once
#include <fea/audio/vec3f.hpp>

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
    /** @addtogroup Audio
     *@{
     *  @class Listener
     *@}
     ***
     *  @class Listener
     *  @brief This class represents the "ear" of the audio scene.
     *
     *  The listerer is equivalent to a camera when talking about graphics. For instance, if an audio is positioned to the left of the listener, the audio will be heard through the left speaker. The AudioPlayer keeps a listener internally and other listeners can be set using the AudioPlayer::setListener function.
     ***
     *  @fn Listener::Listener()
     *  @brief Construct a Listener. 
     ***
     *  @fn void Listener::setGain(float gain)
     *  @brief Set the gain.
     *
     *  Setting the gain of the listener acts like a global volume control. 1.0f is default and normal volume. The total gain will be capped at 1.0f.
     *  Assert/undefined behavior when input is less than zero.
     *  @param gain Gain.
     ***
     *  @fn float Listener::getGain() const
     *  @brief Get the gain.
     *  @return Gain.
     ***
     *  @fn void Listener::setPosition(const Vec3F& position)
     *  @brief Set the 3D position in the scene.
     *  @param position The 3D position.
     ***
     *  @fn const Vec3F& Listener::getPosition() const
     *  @brief Get the 3D position.
     *  @return The position.
     ***
     *  @fn void Listener::setVelocity(const Vec3F& velocity)
     *  @brief Set the velocity.
     *
     *  The velocity is used to calculate doppler effects.
     *  @param velocity The velocity.
     ***
     *  @fn const Vec3F& Listener::getVelocity() const
     *  @brief Get current velocity.
     *  @return Velocity.
     ***
     *  @fn void Listener::setOrientation(const Vec3F& at, const Vec3F& up)
     *  @brief Set the orientation of the listener.
     *
     *  The orientation can be thought of as how the listener's head is turned. The at-vector points to where the listener should look (imagine it pointing out straight from the nose) and the up-vector is which way is up (imagine it pointing up from the top of the head). By turning these vectors, any 3D orientation can be achieved. 
     *  Keep in mind that to set up a proper listener space where audio behaves correctly, the two vectors has to be perpendicular to each other.
     *  Undefined behavior when the two vectors are linearly dependent.
     ***
     *  @fn const Vec3F& Listener::getOrientationAt() const
     *  @brief Get the at-vector of the orientation.
     *  @return The at-vector.
     ***
     *  @fn const Vec3F& Listener::getOrientationUp() const
     *  @brief Get the up-vector of the orientation.
     *  @return The up-vector.
     ***/
}
