#pragma once
#include <unordered_map>
#include <vector>
#include <featherkit/entity/entitymanager.h>

namespace fea
{
    class EntityFactory
    {
        public:
            EntityFactory(EntityManager& entityManager);
            WeakEntityPtr createEntity(const std::string& templateName);
            void registerEntityTemplate(const std::string& templateName, const std::vector<std::pair<std::string, std::string>>& attributes);
            void registerEntityTemplates(const std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& templates);
            void registerDefaultSetter(const std::string& attribute, std::function<void(const std::string&, const std::vector<std::string>&, WeakEntityPtr)> defaultFunc);
            void clear();
        private:
            fea::EntityManager& mEntityManager;
            std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>> mEntityTemplates;
            std::unordered_map<std::string, std::function<void(const std::string&, const std::vector<std::string>&, WeakEntityPtr)>> mDefaultSetters;
    };
    /** @addtogroup EntitySystem
     *@{
     *  @class EntityFactory
     *@}
     ***
     *  @class EntityFactory
     *  @brief Can create pretefined entities based on entity templates.
     *
     *  Entity templates help you create entities easier without having to specify all attributes manually every time. This is done by registering templates. A template has a name and a list of attributes and default values. For instance, this can be a template (in JSON format):
     *  @code
     *  "turtle":
     *  {
     *      "health":"140", "position":"0.0f,0.0f", "velocity":"0.0f,0.0f", "maxvelocity":"5.5f", "collisiontype":"solid"
     *  }
     *  @endcode
     *
     *  This template describing a turtle entity has five attributes: health, position, velocity, maxvelocity and collisiontype. All of the attributes have to be registered at the entity manager. The numerical values next to the attribute names are their default values. These are the values that the attributes of a created turtle entity will attain. To give default values to an attribute, a default setter function has to be registered using EntityFactory::registerDefaultSetter. 
     *
     *  This class needs a reference to an EntityManager instance.
     ***
     *  @fn EntityFactory::EntityFactory(EntityManager& entityManager)
     *  @brief Construct an EntityFactory.
     *  @param entityManager EntityManager to use.
     ***
     *  @fn WeakEntityPtr EntityFactory::createEntity(const std::string& templateName)
     *  @brief Create an Entity from the given template.
     *  
     *  The template given must have been registered prior to creating the Entity, otherwise, an EntityException will be thrown. If the function succeeds in creating the Entity, it will be assigned a unique ID and a WeakEntityPtr pointing to the Entity will be returned.
     *  @param templateName The name of the template to instantiate.
     *  @return A pointer to the created Entity.
     ***
     *  @fn void EntityFactory::registerEntityTemplate(const std::string& templateName, const std::vector<std::pair<std::string, std::string> >& attributes)
     *  @brief Register an EntityTemplate. 
     *
     *  The entity template is a name mapped to a list of attributes and their default values. The registered entity template will have all the attributes provided in the list. For example, an Entity template called "Apple" might be registered with the attributes "weight", "brand" and "ripeness". Keep in mind that these attributes must have been registered using EntityManager::registerAttribute.
     *
     *  Default values are given as strings. They may be empty in which case the attribute does not have a default value. These strings have to be handled by a default setter function. These functions must be registered separately using EntityFactory::registerDefaultSetter. See that function for more information on default values.
     *  @param templateName Name of the new Entity template.
     *  @param attributes Vector containing attribute names and default values.
     ***
     *  @fn void EntityFactory::registerEntityTemplates(const std::unordered_map<std::string, std::vector<std::pair<std::string, std::string> > >& templates)
     *  @brief Register multiple Entity templates at once.
     *  
     *  Works the same as EntityFactory::registerEntityTemplate except it registers a whole map full of Entity templates at once. Useful for loading Entity template configurations that have been read from file.
     *  @param templates Map containing Entity template names and vectors with attribute information.
     ***
     *  @fn void EntityFactory::registerDefaultSetter(const std::string& attribute, std::function<void(const std::string&, const std::vector<std::string>&, WeakEntityPtr)> defaultFunc)
     *  @brief Register a default setter function for a given attribute.
     *
     *  When registering entity templates, default values are registered with their attributes. These default values are always just plain strings, and to make these actually being set to the attribute which might be of any given type in a correct way, a default setter function is needed.
     *
     *  This function should take a string for the attribute name, and a const std::vector<std::string>& which contains the default value string cut into pieces delimited by ",", and finally a pointer to the entity for which the attribute should be set. This function is responsible for setting the default value for the WeakEntityPtr instance.
     *
     *  For example, if the attribute "Colour has been registered and the data type that will be used for this attribute is this struct...
     *  @code
     *  struct Colour
     *  {
     *    float r;
     *    float g;
     *    float b;
     *   };
     *  @endcode
     *  ...and you have registered an entity template with that attribute, and the default value "1.0f,0.0f,0.0f" for it, then an appropriate default setting function would be:
     *  @code
     *  void colourSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
     *  {
     *    Colour col;
     *    col.r = std::stof(arguments[0]);
     *    col.g = std::stof(arguments[1]);
     *    col.b = std::stof(arguments[2]);
     *
     *    entity.lock()->setAttribute<Colour>(attribute, col);
     *  }
     *  @endcode
     *  This works since the default string "1.0f,0.0f,0.0f" will be given to the default setter function as "1.0f", "0.0f" and "0.0f" in the std::vector. It needs to be registered like so:
     *  @code
     *  entityManager.registerDefaultSetter("Colour", &colourSetter);
     *  @endcode
     *
     *  After this, whenever an entity of that template (or any other template using the "Colour" attribute) is created, the default value will be set according to the default string.
     *  
     *  If an entity template is registered with default values for an attribute, that attribute must have a default setter function registered or an InvalidAttributeException will be thrown.
     *  @param attribute Name of the attribute.
     *  @param defaultFunc Pointer to the default setter function.
     ***
     *  @fn void EntityFactory::clear()
     *  @brief Remove all registered templates and default setters.
     ***/
}
