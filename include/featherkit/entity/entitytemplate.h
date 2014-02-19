#pragma once

namespace fea
{
    using EntityTemplateAttributes = std::unordered_map<std::string, std::string>;

    struct EntityTemplate
    {
        std::vector<std::string> mInherits;
        std::unordered_map<std::string, std::string> mAttributes;
    };
}
