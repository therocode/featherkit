#pragma once
#include <featherkit/entity/entity.h>
#include <string>
#include <vector>

namespace fea
{
    namespace util
    {
        class DefaultSetterException : public std::runtime_error 
        {
            public:
                DefaultSetterException(const std::string& message);
        };

        void floatSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);
        void doubleSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);
        void int32Setter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);
        void uint32Setter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);
        void boolSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);
        void byteSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);
        void idSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity);

        /** @addtogroup EntitySystem
         *@{
         *  @fn void floatSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type float and should be handled as such.
         *
         *  @fn void doubleSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type double and should be handled as such.
         *
         *  @fn void int32Setter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type int32 and should be handled as such.
         *
         *  @fn void uint32Setter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type uint32 and should be handled as such.
         *
         *  @fn void boolSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type bool and should be handled as such.
         *
         *  @fn void byteSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type char and should be handled as such.
         *
         *  @fn void idSetter(const std::string& attribute, const std::vector<std::string>& arguments, fea::WeakEntityPtr entity)
         *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are meant to be identical to the ID numbers of the entities.
         *
         *  @class DefaultSetterException
         *@}
         ***
         *  @class DefaultSetterException
         *  @brief Exception used by the default setter functions system.
         *
         *  @fn DefaultSetterException::DefaultSetterException(const std::string& message)
         *  @brief Construct an exception to throw containing a message.
         *  @param message Message further describing the error.
         ***/
    }
}
