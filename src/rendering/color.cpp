#include <fea/rendering/color.hpp>

namespace fea
{
    Color::Color()
    {
        mRed = 0.0f;
        mGreen = 0.0f;
        mBlue = 0.0f;
        mAlpha = 1.0f;
    }

    Color::Color(float r, float g, float b, float a)
    {
        mRed = std::max(0.0f, std::min(1.0f, r));
        mGreen = std::max(0.0f, std::min(1.0f, g));
        mBlue = std::max(0.0f, std::min(1.0f, b));
        mAlpha = std::max(0.0f, std::min(1.0f, a));
    }

    Color::Color(int32_t r, int32_t g, int32_t b, int32_t a)
    {
        mRed = float(std::max(0, std::min(255, r)))/255.0f;
        mGreen = float(std::max(0, std::min(255, g)))/255.0f;
        mBlue = float(std::max(0, std::min(255, b)))/255.0f;
        mAlpha = float(std::max(0, std::min(255, a)))/255.0f;
    }

    Color::Color(int32_t hexValue, float a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        mRed = float((hexValue >> 16) & 0xFF)/255.0f;
        mGreen = float((hexValue >> 8) & 0xFF)/255.0f;
        mBlue = float(hexValue & 0xFF)/255.0f;
        mAlpha = std::max(0.0f, std::min(1.0f, a));
    }

    Color::Color(int32_t hexValue, int32_t a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        mRed = float((hexValue >> 16) & 0xFF)/255.0f;
        mGreen = float((hexValue >> 8) & 0xFF)/255.0f;
        mBlue = float(hexValue & 0xFF)/255.0f;
        mAlpha = float(std::max(0, std::min(255, a)))/255.0f;
    }

    Color Color::operator+(const Color& other) const
    {
        Color result;

        result.mRed = mRed + other.mRed + 0.00196f;
        result.mGreen = mGreen + other.mGreen + 0.00196f;
        result.mBlue = mBlue + other.mBlue + 0.00196f;
        result.mAlpha = mAlpha + other.mAlpha + 0.00196f;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Color& Color::operator+=(const Color& other)
    {
        mRed = mRed + other.mRed;
        mGreen = mGreen + other.mGreen;
        mBlue = mBlue + other.mBlue;
        mAlpha = mAlpha + other.mAlpha;

        mRed = std::max(0.0f, std::min(1.0f, mRed));
        mGreen = std::max(0.0f, std::min(1.0f, mGreen));
        mBlue = std::max(0.0f, std::min(1.0f, mBlue));
        mAlpha = std::max(0.0f, std::min(1.0f, mAlpha));

        return *this;
    }

    Color Color::operator-(const Color& other) const
    {
        Color result;

        result.mRed = mRed - other.mRed + 0.00196f;
        result.mGreen = mGreen - other.mGreen + 0.00196f;
        result.mBlue = mBlue - other.mBlue + 0.00196f;
        result.mAlpha = mAlpha - other.mAlpha + 0.00196f;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Color& Color::operator-=(const Color& other)
    {
        mRed = mRed - other.mRed;
        mGreen = mGreen - other.mGreen;
        mBlue = mBlue - other.mBlue;
        mAlpha = mAlpha - other.mAlpha;

        mRed = std::max(0.0f, std::min(1.0f, mRed));
        mGreen = std::max(0.0f, std::min(1.0f, mGreen));
        mBlue = std::max(0.0f, std::min(1.0f, mBlue));
        mAlpha = std::max(0.0f, std::min(1.0f, mAlpha));

        return *this;
    }

    Color Color::operator*(const Color& other) const
    {
        Color result;

        result.mRed = mRed * other.mRed + 0.00196f;
        result.mGreen = mGreen * other.mGreen + 0.00196f;
        result.mBlue = mBlue * other.mBlue + 0.00196f;
        result.mAlpha = mAlpha * other.mAlpha + 0.00196f;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Color& Color::operator*=(const Color& other)
    {
        mRed = mRed * other.mRed;
        mGreen = mGreen * other.mGreen;
        mBlue = mBlue * other.mBlue;
        mAlpha = mAlpha * other.mAlpha;

        mRed = std::max(0.0f, std::min(1.0f, mRed));
        mGreen = std::max(0.0f, std::min(1.0f, mGreen));
        mBlue = std::max(0.0f, std::min(1.0f, mBlue));
        mAlpha = std::max(0.0f, std::min(1.0f, mAlpha));

        return *this;
    }

    Color Color::operator/(const Color& other) const
    {
        Color result;

        result.mRed = mRed / other.mRed + 0.00196f;
        result.mGreen = mGreen / other.mGreen + 0.00196f;
        result.mBlue = mBlue / other.mBlue + 0.00196f;
        result.mAlpha = mAlpha / other.mAlpha + 0.00196f;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Color& Color::operator/=(const Color& other)
    {
        mRed = mRed / other.mRed;
        mGreen = mGreen / other.mGreen;
        mBlue = mBlue / other.mBlue;
        mAlpha = mAlpha / other.mAlpha;

        mRed = std::max(0.0f, std::min(1.0f, mRed));
        mGreen = std::max(0.0f, std::min(1.0f, mGreen));
        mBlue = std::max(0.0f, std::min(1.0f, mBlue));
        mAlpha = std::max(0.0f, std::min(1.0f, mAlpha));

        return *this;
    }

    bool Color::operator==(const Color& other) const
    {
        uint8_t r = uint8_t(mRed * 255.0f);
		uint8_t g = uint8_t(mGreen * 255.0f);
		uint8_t b = uint8_t(mBlue * 255.0f);
		uint8_t a = uint8_t(mAlpha * 255.0f);

		uint8_t r2 = uint8_t(other.mRed * 255.0f);
		uint8_t g2 = uint8_t(other.mGreen * 255.0f);
		uint8_t b2 = uint8_t(other.mBlue * 255.0f);
		uint8_t a2 = uint8_t(other.mAlpha * 255.0f);

        return (r == r2) &&
               (b == b2) &&
               (g == g2) &&
               (a == a2);
    }

    bool Color::operator!=(const Color& other) const
    {
        uint8_t r = uint8_t(mRed * 255);
		uint8_t g = uint8_t(mGreen * 255);
		uint8_t b = uint8_t(mBlue * 255);
		uint8_t a = uint8_t(mAlpha * 255);

		uint8_t r2 = uint8_t(other.mRed * 255);
		uint8_t g2 = uint8_t(other.mGreen * 255);
		uint8_t b2 = uint8_t(other.mBlue * 255);
		uint8_t a2 = uint8_t(other.mAlpha * 255);

        return !((r == r2) &&
                 (b == b2) &&
                 (g == g2) &&
                 (a == a2));
    }


    float Color::r() const
    {
        return mRed;
    }

    float Color::g() const
    {
        return mGreen;
    }

    float Color::b() const
    {
        return mBlue;
    }

    float Color::a() const
    {
        return mAlpha;
    }

    uint8_t Color::rAsByte() const
    {
		return uint8_t(mRed * 255);
    }

    uint8_t Color::gAsByte() const
    {
		return uint8_t(mGreen * 255);
    }

    uint8_t Color::bAsByte() const
    {
		return uint8_t(mBlue * 255);
    }

    uint8_t Color::aAsByte() const
    {
		return uint8_t(mAlpha * 255);
    }

    void Color::setR(float r)
    {
        mRed = std::max(0.0f, std::min(1.0f, r));
    }

    void Color::setG(float g)
    {
        mGreen = std::max(0.0f, std::min(1.0f, g));
    }

    void Color::setB(float b)
    {
        mBlue = std::max(0.0f, std::min(1.0f, b));
    }

    void Color::setA(float a)
    {
        mAlpha = std::max(0.0f, std::min(1.0f, a));
    }

    void Color::setRAsByte(int32_t r)
    {
        mRed = (float)std::max(0, std::min(255, r));
    }

    void Color::setGAsByte(int32_t g)
    {
		mGreen = (float)std::max(0, std::min(255, g));
    }

    void Color::setBAsByte(int32_t b)
    {
		mBlue = (float)std::max(0, std::min(255, b));
    }

    void Color::setAAsByte(int32_t a)
    {
		mAlpha = (float)std::max(0, std::min(255, a));
    }
}
