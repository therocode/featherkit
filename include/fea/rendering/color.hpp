#pragma once
#include <fea/config.hpp>
#include <stdint.h>

namespace fea
{
    class FEA_API Color
    {
        public:
            Color();
            Color(float red, float green, float blue, float alpha = 1.0f);
            Color(int32_t red, int32_t green, int32_t blue, int32_t alpha = 255);
            explicit Color(int32_t hexValue, float alpha);
            explicit Color(int32_t hexValue, int32_t alpha = 255);

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

            float rAsFloat() const;
            float gAsFloat() const;
            float bAsFloat() const;
            float aAsFloat() const;

            void setRAsFloat(float red);
            void setGAsFloat(float green);
            void setBAsFloat(float blue);
            void setAAsFloat(float alpha);

            static const Color Black;
            static const Color Gray;
            static const Color White;
            static const Color Transparent;
            static const Color Red;
            static const Color Green;
            static const Color Blue;
            static const Color Cyan;
            static const Color Magenta;
            static const Color Yellow;
            static const Color Pink;
            static const Color Brown;
            static const Color Tan;
            static const Color Orange;
            static const Color Teal;
            static const Color Purple;

            uint8_t r;
            uint8_t g;
            uint8_t b;
            uint8_t a;
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
     *  @var Color::r
     *  @brief Red channel value. 0 is none and 255 is full.
     ***
     *  @var Color::g
     *  @brief Green channel value. 0 is none and 255 is full.
     ***
     *  @var Color::b
     *  @brief Blue channel value. 0 is none and 255 is full.
     ***
     *  @var Color::a
     *  @brief Alpha channel value. 0 is none and 255 is full.
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
     *  @fn float Color::rAsFloat() const
     *  @brief Get the value of the red channel.
     *  @return The value of the red channel from 0.0f to 1.0f.
     ***
     *  @fn float Color::gAsFloat() const
     *  @brief Get the value of the green channel.
     *  @return The value of the green channel from 0.0f to 1.0f.
     ***
     *  @fn float Color::bAsFloat() const
     *  @brief Get the value of the blue channel.
     *  @return The value of the blue channel from 0.0f to 1.0f.
     ***
     *  @fn float Color::aAsFloat() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0.0f to 1.0f.
     ***
     *  @fn void Color::setRAsFloat(float red)
     *  @brief Set the value of the color's red channel. Values higher than 1.0f will be capped.
     *  @param red The value of the red channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setGAsFloat(float green)
     *  @brief Set the value of the color's green channel. Values higher than 1.0f will be capped.
     *  @param green The value of the green channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setBAsFloat(float blue)
     *  @brief Set the value of the color's blue channel. Values higher than 1.0f will be capped.
     *  @param blue The value of the blue channel to set from 0.0f to 1.0f.
     ***
     *  @fn void Color::setAAsFloat(float alpha)
     *  @brief Set the value of the color's alpha channel. Values higher than 1.0f will be capped.
     *  @param alpha The value of the alpha channel to set from 0.0f to 1.0f.
     ***
     *  @var const Color::Black
     *  @brief Black predefined color.
     ***
     *  @var const Color::Gray
     *  @brief Gray predefined color.
     ***
     *  @var const Color::White
     *  @brief White predefined color.
     ***
     *  @var const Color::Transparent
     *  @brief Transparent predefined color.
     ***
     *  @var const Color::Red
     *  @brief Red predefined color.
     ***
     *  @var const Color::Green
     *  @brief Green predefined color.
     ***
     *  @var const Color::Blue
     *  @brief Blue predefined color.
     ***
     *  @var const Color::Cyan
     *  @brief Cyan predefined color.
     ***
     *  @var const Color::Magenta
     *  @brief Magenta predefined color.
     ***
     *  @var const Color::Yellow
     *  @brief Yellow predefined color.
     ***
     *  @var const Color::Pink
     *  @brief Pink predefined color.
     ***
     *  @var const Color::Brown
     *  @brief Brown predefined color.
     ***
     *  @var const Color::Tan
     *  @brief Tan predefined color.
     ***
     *  @var const Color::Orange
     *  @brief Orange predefined color.
     ***
     *  @var const Color::Teal
     *  @brief Teal predefined color.
     ***
     *  @var const Color::Purple
     *  @brief Purple predefined color.
     */
}
