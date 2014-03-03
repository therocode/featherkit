#pragma once
#include <stdint.h>
#include <algorithm>

namespace fea
{
    class Color
    {
        public:
            Color();
            Color(float red, float green, float blue, float alpha = 1.0f);
            Color(int32_t red, int32_t green, int32_t blue, int32_t alpha = 255);
            Color(int32_t hexValue, float alpha);
            Color(int32_t hexValue, int32_t alpha = 255);

            Color operator+(const Color& other) const;
            Color& operator+=(const Color& other);
            Color operator-(const Color& other) const;
            Color& operator-=(const Color& other);
            Color operator*(const Color& other) const;
            Color& operator*=(const Color& other);
            Color operator/(const Color& other) const;
            Color& operator/=(const Color& other);
            bool operator==(const Color& other) const;
            bool operator!=(const Color& other) const;

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
     *  @class Color
     *@}
     ***
     *  @class Color
     *  @brief A class for storing color information.
     *
     *  The Color class allows the user to set, get and store 24-bit color and 8-bit alpha channel information. The class supports basic color arithmetic.
     ***
     *  @fn Color::Color()
     *  @brief Construct a Color.
     *
     *  The color will by default be black with full opacity.
     ***
     *  @fn Color::Color(float red, float green, float blue, float alpha = 1.0f)
     *  @brief Construct a color with the given color values in floats with a range from 0.0f to 1.0f. Values higher than 1.0f will be capped.
     *  @param red Red channel value from 0.0f to 1.0f.
     *  @param green Green channel value from 0.0f to 1.0f.
     *  @param blue Blue channel value from 0.0f to 1.0f.
     *  @param alpha Alpha channel value from 0.0f to 1.0f.
     ***
     *  @fn Color::Color(int32_t red, int32_t green, int32_t blue, int32_t alpha = 255);
     *  @brief Construct a color with the given color values in ints with a range from 0 to 255. Values higher than 255 will be capped.
     *  @param red Red channel value from 0 to 255.
     *  @param green Green channel value from 0 to 255.
     *  @param blue Blue channel value from 0 to 255.
     *  @param alpha Alpha channel value from 0 to 255.
     ***
     *  @fn Color::Color(int32_t hexValue, int32_t alpha = 255);
     *  @brief Construct a color from a hexadecimal value and its alpha channel from a float.
     *  @param hexValue The color value from 0x000000 to 0xFFFFFF.
     *  @param alpha Alpha channel value from 0 to 255. Values higher than 255 will be capped.
     ***
     *  @fn Color::Color(int32_t hexValue, float alpha);
     *  @brief Construct a color from a hexadecimal value and its alpha channel from a float.
     *  @param hexValue The color value from 0x000000 to 0xFFFFFF.
     *  @param alpha Alpha channel value from 0.0f to 1.0f. Values higher than 1.0f will be capped.
     ***
     *  @fn Color Color::operator+(const Color& other) const
     *  @brief Add two color instances together.
     *
     *  The final color will be capped at the highest possible color value.
     *  @param other The second color to add together.
     *  @return The final color result of the summed colors.
     ***
     *  @fn Color& Color::operator+=(const Color& other)
     *  @brief Add a color to this color.
     *
     *  The final color will be capped at the highest possible color value.
     *  @param other The color to add to this color.
     *  @return The final result of this color.
     ***
     *  @fn Color Color::operator-(const Color& other) const
     *  @brief Subtract one color instance from another color instance.
     *
     *  The final color will be capped at zero.
     *  @param other The color to be subtracted.
     *  @return The final color result of the difference of the colors.
     ***
     *  @fn Color& Color::operator-=(const Color& other)
     *  @brief Subtract a color from this color.
     *
     *  The final color will be capped at zero.
     *  @param other The color to subtract from this color.
     *  @return The final result of this color.
     ***
     *  @fn Color Color::operator*(const Color& other) const
     *  @brief Multiply two color instances together.
     * 
     *  The multiplication works on the colors stored as floats.
     *  @param other The second color to multiply together.
     *  @return The final color result of the multiplied colors.
     ***
     *  @fn Color& Color::operator*=(const Color& other)
     *  @brief Multiply a color with this color.
     * 
     *  The multiplication works on the colors stored as floats.
     *  @param other The color to multiply with.
     *  @return The final result of this color.
     ***
     *  @fn Color Color::operator/(const Color& other) const
     *  @brief Divide one color instance by another color instance.
     * 
     *  The division works on the colors stored as floats.
     *  @param other The color instance to divide by.
     *  @return The final color result of the two colors.
     ***
     *  @fn Color& Color::operator/=(const Color& other)
     *  @brief Divide this color by another color.
     * 
     *  The division works on the colors stored as floats.
     *  @param other The color to divide this color by.
     *  @return The final result of this color.
     ***
     *  @fn bool Color::operator==(const Color& other) const
     *  @brief Compare two color instances.
     *  @param other The color instance to compare to.
     *  @return True if the instances have similar color channel values.
     ***
     *  @fn bool Color::operator!=(const Color& other) const
     *  @brief Compare two color instances.
     *  @param other The color instance to compare to.
     *  @return True if the instances differ in the color channel values.
     ***
     *  @fn float Color::r() const
     *  @brief Get the value of the red channel.
     *  @return The value of the red channel from 0.0f to 1.0f.
     ***
     *  @fn float Color::g() const
     *  @brief Get the value of the green channel.
     *  @return The value of the green channel from 0.0f to 1.0f.
     ***
     *  @fn float Color::b() const
     *  @brief Get the value of the blue channel.
     *  @return The value of the blue channel from 0.0f to 1.0f.
     ***
     *  @fn float Color::a() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0.0f to 1.0f.
     ***
     *  @fn uint8_t Color::rAsByte() const
     *  @brief Get the value of the red channel.
     *  @return The value of the red channel from 0 to 255.
     ***
     *  @fn uint8_t Color::gAsByte() const
     *  @brief Get the value of the green channel.
     *  @return The value of the green channel from 0 to 255.
     ***
     *  @fn uint8_t Color::bAsByte() const
     *  @brief Get the value of the blue channel.
     *  @return The value of the blue channel from 0 to 255.
     ***
     *  @fn uint8_t Color::aAsByte() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0 to 255.
     ***
     *  @fn void Color::setR(float red)
     *  @brief Set the value of the color's red channel. Values higher than 1.0f will be capped.
     *  @param red The value of the red channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setG(float green)
     *  @brief Set the value of the color's green channel. Values higher than 1.0f will be capped.
     *  @param green The value of the green channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setB(float blue)
     *  @brief Set the value of the color's blue channel. Values higher than 1.0f will be capped.
     *  @param blue The value of the blue channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setA(float alpha)
     *  @brief Set the value of the color's alpha channel. Values higher than 1.0f will be capped.
     *  @param alpha The value of the alpha channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setRAsByte(int32_t red)
     *  @brief Set the value of the color's red channel. Values higher than 255 will be capped.
     *  @param red The value of the red channel to set from 0 to 255.
     ***
     *  @fn void Color::setGAsByte(int32_t green)
     *  @brief Set the value of the color's green channel. Values higher than 255 will be capped.
     *  @param green The value of the green channel to set from 0 to 255.
     ***
     *  @fn void Color::setBAsByte(int32_t blue)
     *  @brief Set the value of the color's blue channel. Values higher than 255 will be capped.
     *  @param blue The value of the blue channel to set from 0 to 255.
     ***
     *  @fn void Color::setAAsByte(int32_t alpha)
     *  @brief Set the value of the color's alpha channel. Values higher than 255 will be capped.
     *  @param alpha The value of the alpha channel to set from 0 to 255.
     */
}
