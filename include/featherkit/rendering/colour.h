#pragma once
#include <stdint.h>
#include <algorithm>

namespace fea
{
    class Colour
    {
        public:
            Colour();
            Colour(float r, float g, float b, float a = 1.0f);
            Colour(int32_t r, int32_t g, int32_t b, int32_t a = 255);
            Colour(int32_t hexValue, float a);
            Colour(int32_t hexValue, int32_t a = 255);

            Colour operator+(const Colour& other) const;
            Colour& operator+=(const Colour& other);
            Colour operator-(const Colour& other) const;
            Colour& operator-=(const Colour& other);
            Colour operator*(const Colour& other) const;
            Colour& operator*=(const Colour& other);
            Colour operator/(const Colour& other) const;
            Colour& operator/=(const Colour& other);
            bool operator==(const Colour& other) const;
            bool operator!=(const Colour& other) const;

            float r() const;
            float g() const;
            float b() const;
            float a() const;

            uint8_t rAsByte() const;
            uint8_t gAsByte() const;
            uint8_t bAsByte() const;
            uint8_t aAsByte() const;

            void setR(float r);
            void setG(float g);
            void setB(float b);
            void setA(float a);

            void setRAsByte(int32_t r);
            void setGAsByte(int32_t g);
            void setBAsByte(int32_t b);
            void setAAsByte(int32_t a);

        private:
            float mRed;
            float mGreen;
            float mBlue;
            float mAlpha;
    };
    /** @addtogroup Render2D
     *@{
     *  @class Colour
     *@}
     ***
     *  @class Colour
     *  @brief A class for storing colour information.
     *
     *  The Colour class allows the user to set, get and store 24-bit colour and 8-bit alpha channel information. The class supports basic colour arithmetic.
     ***
     *  @fn Colour::Colour()
     *  @brief Construct a Colour.
     *
     *  The colour will by default be black with full opacity.
     ***
     *  @fn Colour::Colour(float r, float g, float b, float a = 1.0f)
     *  @brief Construct a colour with the given colour values in floats with a range from 0.0f to 1.0f.
     *  @param r Red channel value from 0.0f to 1.0f.
     *  @param g Green channel value from 0.0f to 1.0f.
     *  @param b Blue channel value from 0.0f to 1.0f.
     *  @param a Alpha channel value from 0.0f to 1.0f.
     ***
     *  @fn Colour::Colour(int32_t r, int32_t g, int32_t b, int32_t a = 255);
     *  @brief Construct a colour with the given colour values in ints with a range from 0 to 255.
     *  @param r Red channel value from 0 to 255.
     *  @param g Green channel value from 0 to 255.
     *  @param b Blue channel value from 0 to 255.
     *  @param a Alpha channel value from 0 to 255.
     ***
     *  @fn Colour::Colour(int32_t hexValue, int32_t a = 255);
     *  @brief Construct a colour from a hexadecimal value and its alpha channel from a float.
     *  @param hexValue The colour value from 0x000000 to 0xFFFFFF.
     *  @param a Alpha channel value from 0 to 255.
     ***
     *  @fn Colour::Colour(int32_t hexValue, float a);
     *  @brief Construct a colour from a hexadecimal value and its alpha channel from a float.
     *  @param hexValue The colour value from 0x000000 to 0xFFFFFF.
     *  @param a Alpha channel value from 0.0f to 1.0f.
     ***
     *  @fn Colour Colour::operator+(const Colour& other) const
     *  @brief Add two colour instances together.
     *  @param other The second colour to add together.
     *  @return The final colour result of the summed colours.
     ***
     *  @fn Colour& Colour::operator+=(const Colour& other)
     *  @brief Add a colour to this colour.
     *  @param other The colour to add to this colour.
     *  @return The final result of this colour.
     ***
     *  @fn Colour Colour::operator-(const Colour& other) const
     *  @brief Subtract one colour instance from another colour instance.
     *  @param other The colour to be subtracted.
     *  @return The final colour result of the difference of the colours.
     ***
     *  @fn Colour& Colour::operator-=(const Colour& other)
     *  @brief Subtract a colour from this colour.
     *  @param other The colour to subtract from this colour.
     *  @return The final result of this colour.
     ***
     *  @fn Colour Colour::operator*(const Colour& other) const
     *  @brief Multiply two colour instances together.
     *  @param other The second colour to multiply together.
     *  @return The final colour result of the multiplied colours.
     ***
     *  @fn Colour& Colour::operator*=(const Colour& other)
     *  @brief Multiply a colour with this colour.
     *  @param other The colour to multiply with.
     *  @return The final result of this colour.
     ***
     *  @fn Colour Colour::operator/(const Colour& other) const
     *  @brief Divide one colour instance by another colour instance.
     *  @param other The colour instance to divide by.
     *  @return The final colour result of the two colours.
     ***
     *  @fn Colour& Colour::operator/=(const Colour& other)
     *  @brief Divide this colour by another colour.
     *  @param other The colour to divide this colour by.
     *  @return The final result of this colour.
     ***
     *  @fn bool Colour::operator==(const Colour& other) const
     *  @brief Compare two colour instances.
     *  @param other The colour instance to compare to.
     *  @return True if the instances have similar colour channel values.
     ***
     *  @fn bool Colour::operator!=(const Colour& other) const
     *  @brief Compare two colour instances.
     *  @param other The colour instance to compare to.
     *  @return True if the instances differ in the colour channel values.
     ***
     *  @fn float Colour::r() const
     *  @brief Get the value of the red channel.
     *  @return The value of the red channel from 0.0f to 1.0f.
     ***
     *  @fn float Colour::g() const
     *  @brief Get the value of the green channel.
     *  @return The value of the green channel from 0.0f to 1.0f.
     ***
     *  @fn float Colour::b() const
     *  @brief Get the value of the blue channel.
     *  @return The value of the blue channel from 0.0f to 1.0f.
     ***
     *  @fn float Colour::a() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0.0f to 1.0f.
     ***
     *  @fn uint8_t Colour::rAsByte() const
     *  @brief Get the value of the red channel.
     *  @return The value of the red channel from 0 to 255.
     ***
     *  @fn uint8_t Colour::gAsByte() const
     *  @brief Get the value of the green channel.
     *  @return The value of the green channel from 0 to 255.
     ***
     *  @fn uint8_t Colour::bAsByte() const
     *  @brief Get the value of the blue channel.
     *  @return The value of the blue channel from 0 to 255.
     ***
     *  @fn uint8_t Colour::aAsByte() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0 to 255.
     ***
     *  @fn void Colour::setR(float r)
     *  @brief Set the value of the colour's red channel.
     *  @param r The value of the red channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setG(float g)
     *  @brief Set the value of the colour's green channel.
     *  @param g The value of the green channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setB(float b)
     *  @brief Set the value of the colour's blue channel.
     *  @param b The value of the blue channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setA(float a)
     *  @brief Set the value of the colour's alpha channel.
     *  @param a The value of the alpha channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setRAsByte(int32_t r)
     *  @brief Set the value of the colour's red channel.
     *  @param r The value of the red channel to set from 0 to 255.
     ***
     *  @fn void Colour::setGAsByte(int32_t g)
     *  @brief Set the value of the colour's green channel.
     *  @param g The value of the green channel to set from 0 to 255.
     ***
     *  @fn void Colour::setBAsByte(int32_t b)
     *  @brief Set the value of the colour's blue channel.
     *  @param b The value of the blue channel to set from 0 to 255.
     ***
     *  @fn void Colour::setAAsByte(int32_t a)
     *  @brief Set the value of the colour's alpha channel.
     *  @param a The value of the alpha channel to set from 0 to 255.
     ***
     */
}
