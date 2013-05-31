#include <framework/entity/entity.h>
#include <string>
#include <vector>

namespace windgale
{
    class DefaultSetterException : public std::runtime_error 
    {
        public:
            DefaultSetterException(const std::string& m) 
                : std::runtime_error(m) { };
    };

    void floatSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void doubleSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void int32Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void uint32Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void boolSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void byteSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);
    void idSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity);

    /** @addtogroup EntitySystem
     *@{
     *  @fn void floatSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type float and should be handled as such.
     *
     *  @fn void doubleSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type double and should be handled as such.
     *
     *  @fn void int32Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type int32 and should be handled as such.
     *
     *  @fn void uint32Setter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type uint32 and should be handled as such.
     *
     *  @fn void boolSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type bool and should be handled as such.
     *
     *  @fn void byteSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are of the type char and should be handled as such.
     *
     *  @fn void idSetter(std::string attribute, std::vector<std::string>& arguments, windgale::WeakEntityPtr entity)
     *  @brief Register this with the EntityManager::registerDefaultSetter function for the attributes that are meant to be identical to the ID numbers of the entities.
     *
     *  @class DefaultSetterException
     *@}
     ***
     *  @class DefaultSetterException
     *  @brief Exception used by the default setter functions system.
     *
     *  @fn DefaultSetterException::DefaultSetterException(const std::string& m)
     *  @brief Construct an exception to throw containing a message.
     *  @param m Message further describing the error.
     ***/
}
