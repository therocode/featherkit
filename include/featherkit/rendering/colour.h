#pragma once
#include <stdint.h>
#include <algorithm>

namespace fea
{
    class Colour
    {
        public:
            Colour();
            Colour(float red, float green, float blue, float alpha = 1.0f);
            Colour(int32_t red, int32_t green, int32_t blue, int32_t alpha = 255);
            Colour(int32_t hexValue, float alpha);
            Colour(int32_t hexValue, int32_t alpha = 255);

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

            void setR(float red);
            void setG(float green);
            void setB(float blue);
            void setA(float alpha);

            void setRAsByte(int32_t red);
            void setGAsByte(int32_t green);
            void setBAsByte(int32_t blue);
            void setAAsByte(int32_t alpha);

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
     *  @fn Colour::Colour(float red, float green, float blue, float alpha = 1.0f)
     *  @brief Construct a colour with the given colour values in floats with a range from 0.0f to 1.0f. Values higher than 1.0f will be capped.
     *  @param red Red channel value from 0.0f to 1.0f.
     *  @param green Green channel value from 0.0f to 1.0f.
     *  @param blue Blue channel value from 0.0f to 1.0f.
     *  @param alpha Alpha channel value from 0.0f to 1.0f.
     ***
     *  @fn Colour::Colour(int32_t red, int32_t green, int32_t blue, int32_t alpha = 255);
     *  @brief Construct a colour with the given colour values in ints with a range from 0 to 255. Values higher than 255 will be capped.
     *  @param red Red channel value from 0 to 255.
     *  @param green Green channel value from 0 to 255.
     *  @param blue Blue channel value from 0 to 255.
     *  @param alpha Alpha channel value from 0 to 255.
     ***
     *  @fn Colour::Colour(int32_t hexValue, int32_t alpha = 255);
     *  @brief Construct a colour from a hexadecimal value and its alpha channel from a float.
     *  @param hexValue The colour value from 0x000000 to 0xFFFFFF.
     *  @param alpha Alpha channel value from 0 to 255. Values higher than 255 will be capped.
     ***
     *  @fn Colour::Colour(int32_t hexValue, float alpha);
     *  @brief Construct a colour from a hexadecimal value and its alpha channel from a float.
     *  @param hexValue The colour value from 0x000000 to 0xFFFFFF.
     *  @param alpha Alpha channel value from 0.0f to 1.0f. Values higher than 1.0f will be capped.
     ***
     *  @fn Colour Colour::operator+(const Colour& other) const
     *  @brief Add two colour instances together.
     *
     *  The final colour will be capped at the highest possible colour value.
     *  @param other The second colour to add together.
     *  @return The final colour result of the summed colours.
     ***
     *  @fn Colour& Colour::operator+=(const Colour& other)
     *  @brief Add a colour to this colour.
     *
     *  The final colour will be capped at the highest possible colour value.
     *  @param other The colour to add to this colour.
     *  @return The final result of this colour.
     ***
     *  @fn Colour Colour::operator-(const Colour& other) const
     *  @brief Subtract one colour instance from another colour instance.
     *
     *  The final colour will be capped at zero.
     *  @param other The colour to be subtracted.
     *  @return The final colour result of the difference of the colours.
     ***
     *  @fn Colour& Colour::operator-=(const Colour& other)
     *  @brief Subtract a colour from this colour.
     *
     *  The final colour will be capped at zero.
     *  @param other The colour to subtract from this colour.
     *  @return The final result of this colour.
     ***
     *  @fn Colour Colour::operator*(const Colour& other) const
     *  @brief Multiply two colour instances together.
     * 
     *  The multiplication works on the colours stored as floats.
     *  @param other The second colour to multiply together.
     *  @return The final colour result of the multiplied colours.
     ***
     *  @fn Colour& Colour::operator*=(const Colour& other)
     *  @brief Multiply a colour with this colour.
     * 
     *  The multiplication works on the colours stored as floats.
     *  @param other The colour to multiply with.
     *  @return The final result of this colour.
     ***
     *  @fn Colour Colour::operator/(const Colour& other) const
     *  @brief Divide one colour instance by another colour instance.
     * 
     *  The division works on the colours stored as floats.
     *  @param other The colour instance to divide by.
     *  @return The final colour result of the two colours.
     ***
     *  @fn Colour& Colour::operator/=(const Colour& other)
     *  @brief Divide this colour by another colour.
     * 
     *  The division works on the colours stored as floats.
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
     *  @fn void Colour::setR(float red)
     *  @brief Set the value of the colour's red channel. Values higher than 1.0f will be capped.
     *  @param red The value of the red channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setG(float green)
     *  @brief Set the value of the colour's green channel. Values higher than 1.0f will be capped.
     *  @param green The value of the green channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setB(float blue)
     *  @brief Set the value of the colour's blue channel. Values higher than 1.0f will be capped.
     *  @param blue The value of the blue channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setA(float alpha)
     *  @brief Set the value of the colour's alpha channel. Values higher than 1.0f will be capped.
     *  @param alpha The value of the alpha channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Colour::setRAsByte(int32_t red)
     *  @brief Set the value of the colour's red channel. Values higher than 255 will be capped.
     *  @param red The value of the red channel to set from 0 to 255.
     ***
     *  @fn void Colour::setGAsByte(int32_t green)
     *  @brief Set the value of the colour's green channel. Values higher than 255 will be capped.
     *  @param green The value of the green channel to set from 0 to 255.
     ***
     *  @fn void Colour::setBAsByte(int32_t blue)
     *  @brief Set the value of the colour's blue channel. Values higher than 255 will be capped.
     *  @param blue The value of the blue channel to set from 0 to 255.
     ***
     *  @fn void Colour::setAAsByte(int32_t alpha)
     *  @brief Set the value of the colour's alpha channel. Values higher than 255 will be capped.
     *  @param alpha The value of the alpha channel to set from 0 to 255.
     */
}
