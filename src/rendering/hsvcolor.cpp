#include <fea/rendering/hsvcolor.hpp>
#include <algorithm>

namespace fea
{
    HSVColor::HSVColor()
    {
        mHue = 0u;
        mSaturation = 0u;
        mValue = 0u;
        mAlpha = 255u;
    }

    HSVColor::HSVColor(const Color& rgb)
    {
        fromRGB(rgb);
    }

    HSVColor::HSVColor(float h, float s, float v, float a)
    {
        h = std::abs(h);
        h = h -(long)h;

        mHue   = (uint16_t)(h * 360.0f);
        mSaturation = (uint8_t)(std::max(0.0f, std::min(1.0f, s)) * 100.0f);
        mValue  = (uint8_t)(std::max(0.0f, std::min(1.0f, v)) * 100.0f);
        mAlpha = (uint8_t)(std::max(0.0f, std::min(1.0f, a)) * 255.0f);
    }

    HSVColor::HSVColor(int32_t h, int32_t s, int32_t v, int32_t a)
    {
        h = h < 0 ? h % 360 + 360 : h % 360;
        mHue   = h;
        mSaturation = std::max(0, std::min(100, s));
        mValue  = std::max(0, std::min(100, v));
        mAlpha = std::max(0, std::min(255, a));
    }

    HSVColor HSVColor::operator+(const HSVColor& other) const
    {
        return {toRGB() + other.toRGB()};
    }

    HSVColor& HSVColor::operator+=(const HSVColor& other)
    {
        fromRGB(toRGB() + other.toRGB());

        return *this;
    }

    HSVColor HSVColor::operator-(const HSVColor& other) const
    {
        return {toRGB() - other.toRGB()};
    }

    HSVColor& HSVColor::operator-=(const HSVColor& other)
    {
        fromRGB(toRGB() - other.toRGB());

        return *this;
    }

    HSVColor HSVColor::operator*(const HSVColor& other) const
    {
        return {toRGB() * other.toRGB()};
    }

    HSVColor& HSVColor::operator*=(const HSVColor& other)
    {
        fromRGB(toRGB() * other.toRGB());

        return *this;
    }

    HSVColor HSVColor::operator/(const HSVColor& other) const     
    {
        return {toRGB() / other.toRGB()};
    }

    HSVColor& HSVColor::operator/=(const HSVColor& other)
    {
        fromRGB(toRGB() / other.toRGB());

        return *this;
    }

    bool HSVColor::operator==(const HSVColor& other) const
    {
        return (mHue   == other.mHue  ) &&
               (mSaturation == other.mSaturation) &&
               (mValue  == other.mValue ) &&
               (mAlpha == other.mAlpha);
    }

    bool HSVColor::operator!=(const HSVColor& other) const
    {
        return !((mHue   == other.mHue  ) &&
                 (mSaturation == other.mSaturation) &&
                 (mValue  == other.mValue ) &&
                 (mAlpha == other.mAlpha));
    }


    uint16_t HSVColor::h() const
    {
        return mHue;
    }

    uint8_t HSVColor::s() const
    {
        return mSaturation;
    }

    uint8_t HSVColor::v() const
    {
        return mValue;
    }

    uint8_t HSVColor::a() const
    {
        return mAlpha;
    }

    float HSVColor::hAsFloat() const
    {
		return (float)mHue / 360.0f;
    }

    float HSVColor::sAsFloat() const
    {
		return (float)mSaturation / 100.0f;
    }

    float HSVColor::vAsFloat() const
    {
		return (float)mValue / 100.0f;
    }

    float HSVColor::aAsFloat() const
    {
		return (float)mAlpha / 255.0f;
    }

    void HSVColor::setH(int32_t h)
    {
        h = h < 0 ? h % 360 + 360 : h % 360;
        mHue = h;
    }

    void HSVColor::setS(int32_t s)
    {
        mSaturation = std::max(0, std::min(100, s));
    }

    void HSVColor::setV(int32_t v)
    {
        mValue = std::max(0, std::min(100, v));
    }

    void HSVColor::setA(int32_t a)
    {
        mAlpha = std::max(0, std::min(255, a));
    }

    void HSVColor::setHAsFloat(float h)
    {
        h = std::abs(h);
        h = h -(long)h;

        mHue = (uint16_t)(h * 360.0f);
    }

    void HSVColor::setSAsFloat(float s)
    {
        mSaturation = (uint8_t)(std::max(0.0f, std::min(1.0f, s)) * 100.0f);
    }

    void HSVColor::setVAsFloat(float v)
    {
        mValue = (uint8_t)(std::max(0.0f, std::min(1.0f, v)) * 100.0f);
    }

    void HSVColor::setAAsFloat(float a)
    {
        mAlpha = (uint8_t)(std::max(0.0f, std::min(1.0f, a)) * 255.0f);
    }

    fea::Color HSVColor::toRGB() const
    {
        float h = hAsFloat() * 360.0f;
        float s = sAsFloat();
        float v = vAsFloat();

        float r;
        float g;
        float b;

        if(s == 0.0f)
            r = g = b = v;
        else
        {
            h /= 60.0f + 0.0001f;

            int32_t i = std::floor(h);
            float f = h - i;
            float p = v * (1.0f - s);
            float q = v * (1.0f - s * f);
            float t = v * (1.0f - s * (1.0f - f));

            if(i == 0)
            {
                r = v;
                g = t;
                b = p;
            }
            else if(i == 1)
            {
                r = q;
                g = v;
                b = p;
            }
            else if(i == 2)
            {
                r = p;
                g = v;
                b = t;
            }
            else if(i == 3)
            {
                r = p;
                g = q;
                b = v;
            }
            else if(i == 4)
            {
                r = t;
                g = p;
                b = v;
            }
            else
            {
                r = v;
                g = p;
                b = q;
            }
        }

        Color rgb;
        rgb.setRAsFloat(r);
        rgb.setGAsFloat(g);
        rgb.setBAsFloat(b);
        rgb.setAAsFloat(aAsFloat());

        return rgb;
    }

    void HSVColor::fromRGB(const Color& rgb)
    {
        float r = rgb.rAsFloat();
        float g = rgb.gAsFloat();
        float b = rgb.bAsFloat();

        float min = std::min({r, g, b});
        float max = std::max({r, g, b});

        float value = max;

        float delta = max - min;
        float saturation;
        float hue;

        if(max != 0.0f)
            saturation = delta / max;
        else
        {
            saturation = 0.0f;
            hue = 0.0f;
        }

        if(r == max)
            hue = (g - b) / delta;
        else if(g == max)
            hue = 2.0f + (b - r) / delta;
        else
            hue = 4.0f + (r - g) / delta;

        hue *= 60.0f;
        if(hue < 0.0f)
            hue += 360.0f;

        setHAsFloat(hue / 360.0f);
        setSAsFloat(saturation);
        setVAsFloat(value);
        setAAsFloat(rgb.aAsFloat());
    }
}
