#include <featherkit/entity/entityfactory.h>
#include <featherkit/entity/entityexceptions.h>
#include <featherkit/entity/entity.h>
#include <sstream>

namespace fea
{
    EntityFactory::EntityFactory(EntityManager& entityManager) : mEntityManager(entityManager)
    {
    }

    WeakEntityPtr EntityFactory::createEntity(const std::string& templateName)
    {
        WeakEntityPtr created;
        std::vector<std::pair<std::string, std::string>> entityTemplate;

        try
        {
            entityTemplate = mEntityTemplates.at(templateName);
        }
        catch(std::out_of_range)
        {
            throw(EntityException("Error! Entity template '" + templateName + "' does not exist!\n"));
        }

        std::vector<std::string> attributes;

        for(const auto& pair : entityTemplate)
            attributes.push_back(pair.first);

        created = mEntityManager.createEntity(attributes);
        
        for(const auto& pair : entityTemplate)
        {
            if(pair.second == "")
                continue;


            std::function<void(std::string, std::vector<std::string>&, WeakEntityPtr)> defaultSetter;
            try
            {
                defaultSetter = mDefaultSetters.at(pair.first);
            }
            catch(std::out_of_range)
            {
                throw(EntityException("Error! Default value '" + pair.second + "' given to attribute '" + pair.first + "' but no default setter function registered!\n"));
            }
            //TODO: add exception for malformatted strings
            std::vector<std::string> parameters;
            std::stringstream splitter(pair.second);
            std::string parameter;
            while(std::getline(splitter, parameter, ','))
                parameters.push_back(parameter);
            defaultSetter(pair.first, parameters, WeakEntityPtr(created));
        }
        return created;
    }

    void EntityFactory::registerEntityTemplate(const std::string& templateName, const std::vector<std::pair<std::string, std::string>>& attributes)
    {
        if(mEntityTemplates.find(templateName) == mEntityTemplates.end())
        {
            mEntityTemplates.emplace(templateName, attributes);
        }
        else
        {
            throw(EntityException("Error! Trying to add entity template '" + templateName + "' which already exist!\n"));
        }
    }

    void EntityFactory::registerEntityTemplates(const std::unordered_map<std::string, std::vector<std::pair<std::string, std::string>>>& templates)
    {
        for(const auto& pair : templates)
        {
            registerEntityTemplate(pair.first, pair.second);
        }
    }
    
    void EntityFactory::registerDefaultSetter(const std::string& attribute, std::function<void(const std::string&, const std::vector<std::string>&, WeakEntityPtr)> defaultFunc)
    {
        if(mEntityManager.attributeIsValid(attribute))
        {
            mDefaultSetters.emplace(attribute, defaultFunc);
        }
        else
        {
            throw(EntityException("Error! Cannot register default function for attribute '" + attribute + "' since the attribute is not valid!\n"));
        }
    }

    void EntityFactory::clear()
    {
        mEntityTemplates.clear();
        mDefaultSetters.clear();
    }
}
