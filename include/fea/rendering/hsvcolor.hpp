#pragma once
#include <fea/config.hpp>
#include <stdint.h>
#include <fea/rendering/color.hpp>

namespace fea
{
    class FEA_API HSVColor
    {
        public:
            HSVColor();
            HSVColor(const Color& rgb);
            HSVColor(float hue, float saturation, float value, float alpha = 1.0f);
            HSVColor(int32_t hue, int32_t saturation, int32_t value, int32_t alpha = 255);

            HSVColor operator+(const HSVColor& other) const;
            HSVColor& operator+=(const HSVColor& other);
            HSVColor operator-(const HSVColor& other) const;
            HSVColor& operator-=(const HSVColor& other);
            HSVColor operator*(const HSVColor& other) const;
            HSVColor& operator*=(const HSVColor& other);
            HSVColor operator/(const HSVColor& other) const;
            HSVColor& operator/=(const HSVColor& other);
            bool operator==(const HSVColor& other) const;
            bool operator!=(const HSVColor& other) const;

            uint16_t h() const;
            uint8_t s() const;
            uint8_t v() const;
            uint8_t a() const;

            float hAsFloat() const;
            float sAsFloat() const;
            float vAsFloat() const;
            float aAsFloat() const;

            void setH(int32_t hue);
            void setS(int32_t saturation);
            void setV(int32_t value);
            void setA(int32_t alpha);

            void setHAsFloat(float hue);
            void setSAsFloat(float saturation);
            void setVAsFloat(float value);
            void setAAsFloat(float alpha);

            fea::Color toRGB() const;
            void fromRGB(const fea::Color& rgb);
        private:
            uint16_t mHue;
            uint8_t mSaturation;
            uint8_t mValue;
            uint8_t mAlpha;
    };
    /** @addtogroup Render2D
     *@{
     *  @class HSVColor
     *@}
     ***
     *  @class HSVColor
     *  @brief A class for storing color information in HSV form.
     *
     *  H: 0-360 - this represents the hue of the color.
     *  S: 0-100 - this represents the saturation of the color.
     *  V: 0-100 - this represents the value, or brightness of the color.
     ***
     *  @fn HSVColor::HSVColor()
     *  @brief Construct a HSVColor.
     *
     *  The color will by default be black with full opacity.
     ***
     *  @fn HSVColor::HSVColor(const Color& rgb)
     *  @brief Construct a HSVColor from an rgb color
     *
     *  The given rgb color will be converted to hsv.
     *
     *  @param rgb Color to convert.
     ***
     *  @fn HSVColor::HSVColor(float hue, float saturation, float value, float alpha = 1.0f)
     *  @brief Construct a color with the given color values in floats with a range from 0.0f to 1.0f. Values higher than 1.0f will be capped.
     *  @param hue Hue value from 0.0f to 1.0f.
     *  @param saturation Saturation value from 0.0f to 1.0f.
     *  @param value Brightness value from 0.0f to 1.0f.
     *  @param alpha Alpha channel value from 0.0f to 1.0f.
     ***
     *  @fn HSVColor::HSVColor(int32_t hue, int32_t saturation, int32_t value, int32_t alpha = 255);
     *  @brief Construct a color with the given. Faulty values will be capped.
     *  @param hue Hue value from 0 to 360.
     *  @param saturation Saturation value from 0 to 100.
     *  @param value Brightness value from 0 to 100.
     *  @param alpha Alpha channel value from 0 to 255.
     ***
     *  @fn HSVColor HSVColor::operator+(const HSVColor& other) const
     *  @brief Add two color instances together.
     *
     *  The final color will be capped at the highest possible color value.
     *  @param other The second color to add together.
     *  @return The final color result of the summed colors.
     ***
     *  @fn HSVColor& HSVColor::operator+=(const HSVColor& other)
     *  @brief Add a color to this color.
     *
     *  The final color will be capped at the highest possible color value.
     *  @param other The color to add to this color.
     *  @return The final result of this color.
     ***
     *  @fn HSVColor HSVColor::operator-(const HSVColor& other) const
     *  @brief Subtract one color instance from another color instance.
     *
     *  The final color will be capped at zero.
     *  @param other The color to be subtracted.
     *  @return The final color result of the difference of the colors.
     ***
     *  @fn HSVColor& HSVColor::operator-=(const HSVColor& other)
     *  @brief Subtract a color from this color.
     *
     *  The final color will be capped at zero.
     *  @param other The color to subtract from this color.
     *  @return The final result of this color.
     ***
     *  @fn HSVColor HSVColor::operator*(const HSVColor& other) const
     *  @brief Multiply two color instances together.
     * 
     *  The multiplication works on the colors stored as floats.
     *  @param other The second color to multiply together.
     *  @return The final color result of the multiplied colors.
     ***
     *  @fn HSVColor& HSVColor::operator*=(const HSVColor& other)
     *  @brief Multiply a color with this color.
     * 
     *  The multiplication works on the colors stored as floats.
     *  @param other The color to multiply with.
     *  @return The final result of this color.
     ***
     *  @fn HSVColor HSVColor::operator/(const HSVColor& other) const
     *  @brief Divide one color instance by another color instance.
     * 
     *  The division works on the colors stored as floats.
     *  @param other The color instance to divide by.
     *  @return The final color result of the two colors.
     ***
     *  @fn HSVColor& HSVColor::operator/=(const HSVColor& other)
     *  @brief Divide this color by another color.
     * 
     *  The division works on the colors stored as floats.
     *  @param other The color to divide this color by.
     *  @return The final result of this color.
     ***
     *  @fn bool HSVColor::operator==(const HSVColor& other) const
     *  @brief Compare two color instances.
     *  @param other The color instance to compare to.
     *  @return True if the instances have similar color channel values.
     ***
     *  @fn bool HSVColor::operator!=(const HSVColor& other) const
     *  @brief Compare two color instances.
     *  @param other The color instance to compare to.
     *  @return True if the instances differ in the color channel values.
     ***
     *  @fn uint8_t HSVColor::h() const
     *  @brief Get the hue value.
     *  @return The hue value from 0 to 360.
     ***
     *  @fn uint8_t HSVColor::s() const
     *  @brief Get the saturation value.
     *  @return The saturation value from 0 to 100.
     ***
     *  @fn uint8_t HSVColor::v() const
     *  @brief Get the brightness value.
     *  @return The brightness value from 0 to 100.
     ***
     *  @fn uint8_t HSVColor::a() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0 to 255.
     ***
     *  @fn float HSVColor::hAsFloat() const
     *  @brief Get the hue value.
     *  @return The hue value from 0.0f to 1.0f.
     ***
     *  @fn float HSVColor::sAsFloat() const
     *  @brief Get the saturation value.
     *  @return The saturation value from 0.0f to 1.0f.
     ***
     *  @fn float HSVColor::vAsFloat() const
     *  @brief Get the brightness value.
     *  @return The brightness value from 0.0f to 1.0f.
     ***
     *  @fn float HSVColor::aAsFloat() const
     *  @brief Get the value of the alpha channel.
     *  @return The value of the alpha channel from 0.0f to 1.0f.
     ***
     *  @fn void HSVColor::setH(int32_t hue)
     *  @brief Set the value of the color's hue. Values higher than 360 will be capped.
     *  @param hue The hue value to set from 0 to 360.
     ***
     *  @fn void HSVColor::setS(int32_t hue)
     *  @brief Set the value of the color's saturation. Values higher than 100 will be capped.
     *  @param hue The saturation value to set from 0 to 100.
     ***
     *  @fn void HSVColor::setV(int32_t hue)
     *  @brief Set the value of the color's brightness. Values higher than 100 will be capped.
     *  @param hue The brightness value to set from 0 to 100.
     ***
     *  @fn void HSVColor::setA(int32_t alpha)
     *  @brief Set the value of the color's alpha channel. Values higher than 255 will be capped.
     *  @param alpha The value of the alpha channel to set from 0 to 255.
     ***
     *  @fn void HSVColor::setHAsFloat(float hue)
     *  @brief Set the value of the color's hue. Values higher than 1.0f will be capped.
     *  @param hue The hue value to set from 0.0f to 1.0f.
     ***
     *  @fn void HSVColor::setSAsFloat(float saturation)
     *  @brief Set the value of the color's saturation. Values higher than 1.0f will be capped.
     *  @param saturation The saturation value to set from 0.0f to 1.0f.
     ***
     *  @fn void HSVColor::setVAsFloat(float value)
     *  @brief Set the value of the color's brightness. Values higher than 1.0f will be capped.
     *  @param brightness The brightness value to set from 0.0f to 1.0f.
     ***
     *  @fn void HSVColor::setAAsFloat(float alpha)
     *  @brief Set the value of the color's alpha channel. Values higher than 1.0f will be capped.
     *  @param alpha The value of the alpha channel to set from 0.0f to 1.0f.
     ***
     *  @fn Color HSVColor::toRGB() const
     *  @brief Convert to the rgb color format.
     *
     *  @return The RGB color representation of this color.
     ***
     *  @fn void HSVColor::fromRGB(const fea::Color& rgb)
     *  @brief Convert from the rgb color format.
     *
     *  This sets the HSV color instance to the same color as the rgb instance.
     */
}
