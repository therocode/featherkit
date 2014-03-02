#pragma once
#include <memory>

namespace fea
{
    struct AudioData
    {
        std::shared_ptr<void> mData;
        size_t mDataAmount;
    };
}
