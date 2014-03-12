#pragma once
#include <vector>
#include <cstdint>
#include <cstring>

namespace fea
{
    struct AudioData
    {
        AudioData();
        std::vector<int16_t> mSamples;
        size_t mSampleAmount;
    };
}
