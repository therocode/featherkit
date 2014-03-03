#include <featherkit/entity/entityfactory.hpp>
#include <featherkit/entity/entity.hpp>
#include <algorithm>

namespace fea
{
    bool EntityFactory::Prototype::Value::operator<(const Value& other) const
    {
        return mKey < other.mKey;
    }

    EntityFactory::EntityFactory(EntityManager& entityManager) : mManager(entityManager)
    {
    }

    void EntityFactory::registerAttribute(const std::string& attribute, const std::string& dataType)
    {
        FEA_ASSERT(mParsers.find(attribute) == mParsers.end(), "Trying to register attribute '" + attribute + "' which is already registered!");
        FEA_ASSERT(mRegistrators.find(dataType) != mRegistrators.end(), "Trying to register attribute '" + attribute + "' as the type '" + dataType + "' but such a type does not exist!");

        mParsers.emplace(attribute, mRegistrators.at(dataType)(attribute));
    }

    void EntityFactory::addTemplate(const std::string& name, const EntityTemplate& entityTemplate)
    {
        FEA_ASSERT(mPrototypes.find(name) == mPrototypes.end(), "Trying to add entity template '" + name + "' but there exists already such a template!");

        Prototype prototype;

        for(const auto& parentTemplate : entityTemplate.mInherits)
        {
            FEA_ASSERT(mPrototypes.find(parentTemplate) != mPrototypes.end(), "Trying to let entity template '" +name + "' inherit template called '" + parentTemplate + "' which has not been added!");
            auto& parent = mPrototypes.at(parentTemplate);
            
            std::set<std::string> result;
            std::set_union(parent.attributes.begin(), parent.attributes.end(), prototype.attributes.begin(), prototype.attributes.end(), std::inserter(result, result.begin()));

            prototype.attributes = result;

            std::set<Prototype::Value> result2;
            std::set_union(parent.values.begin(), parent.values.end(), prototype.values.begin(), prototype.values.end(), std::inserter(result2, result2.begin()));

            prototype.values = result2;
        }

        for(const auto& element : entityTemplate.mAttributes)
        {
            const std::string& attribute = element.first;
            const std::string& arguments = element.second;

            FEA_ASSERT(mParsers.find(attribute) != mParsers.end(), "Trying to add a template with the attribute '" + attribute + "' which doesn't exist!");

            if(prototype.attributes.find(attribute) == prototype.attributes.end())
            {
                prototype.attributes.insert(attribute);
                if(arguments.size() > 0)
                {
                    prototype.values.insert({attribute, mParsers.at(attribute)(arguments)}); 
                }
            }
            else
            {
                prototype.values.erase({attribute});
                if(arguments.size() > 0)
                {
                    prototype.values.insert({attribute, mParsers.at(attribute)(arguments)}); 
                }
            }
        }

        mPrototypes.emplace(name, std::move(prototype));
    }
    
    bool EntityFactory::hasTemplate(const std::string& name) const
    {
        return mPrototypes.find(name) != mPrototypes.end();
    }

    WeakEntityPtr EntityFactory::instantiate(const std::string& name)
    {
        FEA_ASSERT(mPrototypes.find(name) != mPrototypes.end(), "Trying to instantiate entity template '" + name + "' but such a template does not exist!");
        const Prototype& entityPrototype = mPrototypes.at(name);
        EntityPtr entity = mManager.createEntity(entityPrototype.attributes).lock();
        for(const auto& value : entityPrototype.values)
            value.mSetter(entity);

        return entity;
    }

    Parameters EntityFactory::splitByDelimeter(const std::string& in, char delimeter) const
    {
        Parameters parameters;
        std::string param;
        std::stringstream splitter(in);
        while (std::getline(splitter, param, delimeter))
        {
            parameters.push_back(param);
        }
        return parameters;
    }
}
