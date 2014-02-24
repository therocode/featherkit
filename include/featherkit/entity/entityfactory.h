#pragma once
#include <featherkit/entity/entitymanager.h>
#include <featherkit/entity/entitytemplate.h>
#include <featherkit/entity/entity.h>

namespace fea
{
    using Parameters     = std::vector<std::string>;
    using Setter         = std::function<void(EntityPtr&)>;
    using Parser         = std::function<Setter(const std::string&)>;
    using Registrator   = std::function<Parser(const std::string&)>;

    class EntityFactory
    {
        public:
            EntityFactory(EntityManager& entityManager);
            template<typename Function>
            void addDataType(const std::string& dataTypeName, Function parser);
            template<typename Type>
            void addDataType(const std::string& dataTypeName);
            void registerAttribute(const std::string& attribute, const std::string& dataType);
            void addTemplate(const std::string& name, const EntityTemplate& entityTemplate);
            bool hasTemplate(const std::string& name) const;
            WeakEntityPtr instantiate(const std::string& name);
        private:
            Parameters splitByDelimeter(const std::string& in, char delimeter) const;

            struct Prototype
            {
                struct Value
                {
                    bool operator<(const Value& other) const;
                    std::string mKey;
                    Setter mSetter;
                };

                std::set<std::string> attributes;
                std::set<Value> values;
            };

            std::unordered_map<std::string, Prototype> mPrototypes;
            std::unordered_map<std::string, Parser> mParsers;
            std::unordered_map<std::string, Registrator> mRegistrators;

            EntityManager& mManager;
    };

    template<typename Function>
    void EntityFactory::addDataType(const std::string& dataTypeName, Function parser)
    {
        FEA_ASSERT(mRegistrators.find(dataTypeName) == mRegistrators.end(),"Trying to add data type '" + dataTypeName + "' but it already exists!");
        using Type = typename std::result_of<Function(const Parameters&)>::type;
        //Make attribute registrator
        mRegistrators[dataTypeName] = [this, parser](const std::string& attributeName)->Parser
        {
            mManager.registerAttribute<Type>(attributeName);
            //Make parser
            return [this, parser, attributeName](const std::string& params)->Setter
            {
                auto value = parser(splitByDelimeter(params, ','));
                //make setter.
                return [attributeName, value](EntityPtr& entity)
                {
                    entity->setAttribute<Type>(attributeName, value);
                };
            };
        };
    }

    template<typename Type>
    void EntityFactory::addDataType(const std::string& dataTypeName)
    {
        FEA_ASSERT(mRegistrators.find(dataTypeName) == mRegistrators.end(),"Trying to add data type '" + dataTypeName + "' but it already exists!");
        //Make attribute registrator
        mRegistrators[dataTypeName] = [this](const std::string& attributeName)->Parser
        {
            mManager.registerAttribute<Type>(attributeName);
            //Make parser
            return [attributeName](const std::string& params)->Setter
            {
                FEA_ASSERT(1 == 0, "Trying to register a template where a default value has been added to the attribute '" + attributeName + "' which doesn't have a parser function!");
                return [](EntityPtr& entity)
                {
                };
            };
        };
    }
    /** @addtogroup EntitySystem
     *@{
     *  @class EntityFactory
     *@}
     ***
     *  @class EntityFactory
     *  @brief Can create predefined entities based on entity templates.
     *
     *  Entity templates help you create entities easier without having to specify all attributes manually every time. This is done using entity templates. A template has a name and a list of attributes and default values. For instance, this can be a template (in JSON format):
     *  @code
     *  "turtle":
     *  {
     *      "health":"140", "position":"0.0f,0.0f", "velocity":"0.0f,0.0f", "maxvelocity":"5.5f", "collisiontype":"solid"
     *  }
     *  @endcode
     *
     *  This template describing a turtle entity has five attributes: health, position, velocity, maxvelocity and collisiontype. All of the attributes have to be registered at the entity manager. The numerical values next to the attribute names are their default values. These are the values that the attributes of a created turtle entity will attain. To give default values to an attribute, a parser function must be provided to the data type registration.
     *
     *  This class needs a reference to an EntityManager instance.
     ***
     *  @fn EntityFactory::EntityFactory(EntityManager& entityManager)
     *  @brief Construct an EntityFactory.
     *  @param entityManager EntityManager to use.
     ***
     *  @fn void EntityFactory::addDataType(const std::string& dataTypeName, Function parser)
     *  @brief Add a data type with a parser to the entity factory.
     *
     *  To be able to register any attributes, data types must first be added. Data types are the basic types that attributes can have. For example, you can have the attributes "position" and "velocity" which are both of the data type "vec2". By adding a data type with a parser, entity templates can be given comma separated default values. This code shows how to add the type glm::vec2 as "vec2" with a reasonable parser.
     *  @code
     *  factory.addDataType("vec2", [](const fea::Parameters& params)
     *  {  
     *      FEA_ASSERT(params.size() == 2, "Wrong amount of parameters! Expected 2, got " + std::to_string(params.size()) + "!"); //Make sure the right amount of paramters are provided.
     *      return glm::vec2({std::stof(params[0]), std::stof(params[1])});
     *  });
     *  @endcode
     *
     *  "vec2" is now a valid data type and can be used to register attributes using the EntityFactory::registerAttribute method.
     *
     *  Assert/undefined behaviour if the data type name already exists.
     *  @tparam Parser function. Can often be inferred automatically.
     *  @param dataTypeName Name of the data type.
     *  @param parser Parser function. Should return a valid instance of the type.
     ***
     *  @fn void EntityFactory::addDataType(const std::string& dataTypeName)
     *  @brief Add a data type without a parser to the entity factory.
     *
     *  See EntityFactory::addDataType(const std::string& dataTypeName, Function parser) for more information.
     *
     *  Assert/undefined behaviour if the data type name already exists.
     *  @tparam Type Type of attribute to add.
     *  @param dataTypeName Name of the data type.
     ***
     *  @fn void EntityFactory::registerAttribute(const std::string& attribute, const std::string& dataType)
     *  @brief Register an attribute as a data type.
     *
     *  Before any attribute is used, it has to be registered using this function. This will also register the attribute with the underlying EntityManager. The type provided must have been previously added using EntityFactory::addDataType. Example usage:
     *  @code
     *  factory.registerAttribute("position", "vec2");  //vec2 must have been previously added
     *  @endcode
     *
     *  Assert/undefined behaviour if the attribute name already exists or if the data type does not exist.
     *  @param attribute Name of the attribute.
     *  @param dataType Which type to register the attribute as.
     ***
     *  @fn void EntityFactory::addTemplate(const std::string& name, const EntityTemplate& entityTemplate)
     *  @brief Add an EntityTemplate. 
     *
     *  Assert/undefined behaviour if the template already exists, contains invalid attributes or tries to inherit from an invalid template.
     *  @param name Name of the template.
     *  @param entityTemplate Template.
     ***
     *  @fn bool EntityFactory::hasTemplate(const std::string& name) const
     *  @brief Check if a template has been added.
     *  @param name Name of the template.
     *  @return True if it exists.
     ***
     *  @fn WeakEntityPtr EntityFactory::instantiate(const std::string& name)
     *  @brief Create an Entity from the given template.
     *  
     *  The template given must have been registered prior to creating the Entity. If the function succeeds in creating the Entity, it will be assigned a unique ID and a WeakEntityPtr pointing to the Entity will be returned. The returned pointer is not meant to be stored in a locked state since that entity would still become invalid if the entity is deleted using the EntityManager::removeEntity method.
     *
     *  Assert/undefined behaviour if the template given does not exist.
     *
     *  @param name The name of the template to instantiate.
     *  @return A pointer to the created Entity.
     ***/
}
