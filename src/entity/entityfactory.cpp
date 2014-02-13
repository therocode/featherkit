#include <featherkit/entity/entityfactory.h>
#include <featherkit/entity/entityexceptions.h>
#include <featherkit/entity/entity.h>

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

        for(const auto& element : entityTemplate)
        {
            const std::string& attribute = element.first;
            const std::string& arguments = element.second;

            FEA_ASSERT(mParsers.find(attribute) != mParsers.end(), "Trying to add a template with the attribute '" + attribute + "' which doesn't exist!");
            prototype.attributes.insert(attribute);
            if(arguments.size() > 0)
            {
                prototype.values.insert({attribute, mParsers.at(attribute)(arguments)}); 
            }
        }

        mPrototypes.emplace(name, std::move(prototype));
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
