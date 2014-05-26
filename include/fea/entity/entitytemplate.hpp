#pragma once
#include <fea/config.hpp>

namespace fea
{
    using EntityTemplateAttributes = std::unordered_map<std::string, std::string>;

    struct FEA_API EntityTemplate
    {
        std::vector<std::string> mInherits;
        std::unordered_map<std::string, std::string> mAttributes;
    };

    /** @addtogroup EntitySystem
     *@{
     *  @class EntityTemplate
     *@}
     ***
     *  @class EntityTemplate
     *  @brief Defines an entity template
     *
     *  Entity templates contain a list of other templates they inherit from, and a map of attributes with default values.
     ***
     *  @var EntityTemplate::mInherits
     *  @brief List of templates to inherit from.
     ***
     *  @var EntityTemplate::mAttributes
     *  @brief Map of attributes with default values.
     ***/
}
