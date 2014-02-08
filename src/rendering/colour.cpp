#include <featherkit/rendering/colour.h>

namespace fea
{
    Colour::Colour()
    {
        mRed = 0.0f;
        mGreen = 0.0f;
        mBlue = 0.0f;
        mAlpha = 1.0f;
    }

    Colour::Colour(float r, float g, float b, float a)
    {
        mRed = std::max(0.0f, std::min(1.0f, r));
        mGreen = std::max(0.0f, std::min(1.0f, g));
        mBlue = std::max(0.0f, std::min(1.0f, b));
        mAlpha = std::max(0.0f, std::min(1.0f, a));
    }

    Colour::Colour(int32_t r, int32_t g, int32_t b, int32_t a)
    {
        mRed = float(std::max(0, std::min(255, r)))/255.0f;
        mGreen = float(std::max(0, std::min(255, g)))/255.0f;
        mBlue = float(std::max(0, std::min(255, b)))/255.0f;
        mAlpha = float(std::max(0, std::min(255, a)))/255.0f;
    }

    Colour::Colour(int32_t hexValue, float a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        mRed = float((hexValue >> 16) & 0xFF)/255.0f;
        mGreen = float((hexValue >> 8) & 0xFF)/255.0f;
        mBlue = float(hexValue & 0xFF)/255.0f;
        mAlpha = std::max(0.0f, std::min(1.0f, a));
    }

    Colour::Colour(int32_t hexValue, int32_t a)
    {
        hexValue = std::max(0, std::min(0xFFFFFF, hexValue));

        mRed = float((hexValue >> 16) & 0xFF)/255.0f;
        mGreen = float((hexValue >> 8) & 0xFF)/255.0f;
        mBlue = float(hexValue & 0xFF)/255.0f;
        mAlpha = float(std::max(0, std::min(255, a)))/255.0f;
    }

    Colour Colour::operator+(const Colour& other) const
    {
        Colour result;

        result.mRed = mRed + other.mRed + 0.00196;
        result.mGreen = mGreen + other.mGreen + 0.00196;
        result.mBlue = mBlue + other.mBlue + 0.00196;
        result.mAlpha = mAlpha + other.mAlpha + 0.00196;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Colour& Colour::operator+=(const Colour& other)
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

    Colour Colour::operator-(const Colour& other) const
    {
        Colour result;

        result.mRed = mRed - other.mRed + 0.00196;
        result.mGreen = mGreen - other.mGreen + 0.00196;
        result.mBlue = mBlue - other.mBlue + 0.00196;
        result.mAlpha = mAlpha - other.mAlpha + 0.00196;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Colour& Colour::operator-=(const Colour& other)
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

    Colour Colour::operator*(const Colour& other) const
    {
        Colour result;

        result.mRed = mRed * other.mRed + 0.00196;
        result.mGreen = mGreen * other.mGreen + 0.00196;
        result.mBlue = mBlue * other.mBlue + 0.00196;
        result.mAlpha = mAlpha * other.mAlpha + 0.00196;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Colour& Colour::operator*=(const Colour& other)
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

    Colour Colour::operator/(const Colour& other) const
    {
        Colour result;

        result.mRed = mRed / other.mRed + 0.00196;
        result.mGreen = mGreen / other.mGreen + 0.00196;
        result.mBlue = mBlue / other.mBlue + 0.00196;
        result.mAlpha = mAlpha / other.mAlpha + 0.00196;

        result.mRed = std::max(0.0f, std::min(1.0f, result.mRed));
        result.mGreen = std::max(0.0f, std::min(1.0f, result.mGreen));
        result.mBlue = std::max(0.0f, std::min(1.0f, result.mBlue));
        result.mAlpha = std::max(0.0f, std::min(1.0f, result.mAlpha));

        return result;
    }

    Colour& Colour::operator/=(const Colour& other)
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

    bool Colour::operator==(const Colour& other) const
    {
        uint8_t r = mRed * 255;
        uint8_t g = mGreen * 255;
        uint8_t b = mBlue * 255;
        uint8_t a = mAlpha * 255;

        uint8_t r2 = other.mRed * 255;
        uint8_t g2 = other.mGreen * 255;
        uint8_t b2 = other.mBlue * 255;
        uint8_t a2 = other.mAlpha * 255;

        return (r == r2) &&
               (b == b2) &&
               (g == g2) &&
               (a == a2);
    }

    bool Colour::operator!=(const Colour& other) const
    {
        uint8_t r = mRed * 255;
        uint8_t g = mGreen * 255;
        uint8_t b = mBlue * 255;
        uint8_t a = mAlpha * 255;

        uint8_t r2 = other.mRed * 255;
        uint8_t g2 = other.mGreen * 255;
        uint8_t b2 = other.mBlue * 255;
        uint8_t a2 = other.mAlpha * 255;

        return !((r == r2) &&
                 (b == b2) &&
                 (g == g2) &&
                 (a == a2));
    }


    float Colour::r() const
    {
        return mRed;
    }

    float Colour::g() const
    {
        return mGreen;
    }

    float Colour::b() const
    {
        return mBlue;
    }

    float Colour::a() const
    {
        return mAlpha;
    }

    uint8_t Colour::rAsByte() const
    {
        return mRed * 255;
    }

    uint8_t Colour::gAsByte() const
    {
        return mGreen * 255;
    }

    uint8_t Colour::bAsByte() const
    {
        return mBlue * 255;
    }

    uint8_t Colour::aAsByte() const
    {
        return mAlpha * 255;
    }

    void Colour::setR(float r)
    {
        mRed = std::max(0.0f, std::min(1.0f, r));
    }

    void Colour::setG(float g)
    {
        mGreen = std::max(0.0f, std::min(1.0f, g));
    }

    void Colour::setB(float b)
    {
        mBlue = std::max(0.0f, std::min(1.0f, b));
    }

    void Colour::setA(float a)
    {
        mAlpha = std::max(0.0f, std::min(1.0f, a));
    }

    void Colour::setRAsByte(int32_t r)
    {
        mRed = std::max(0, std::min(255, r));
    }

    void Colour::setGAsByte(int32_t g)
    {
        mGreen = std::max(0, std::min(255, g));
    }

    void Colour::setBAsByte(int32_t b)
    {
        mBlue = std::max(0, std::min(255, b));
    }

    void Colour::setAAsByte(int32_t a)
    {
        mAlpha = std::max(0, std::min(255, a));
    }
}
