#ifndef TYPE_H
#define TYPE_H

/// TODO Still not sure
#include <string>

namespace fission {

/// The type class is the base class of all other types
/// The design is more than pretty similar to the llvm one
/// BaseType is the root of the type tree for the lib
/// The type tree may include parameters, node, values, etc
/// This is WIP
class BaseType {
public:

    /// Basic types used in the application
    /// TODO : use c++0x enum class
    typedef enum {
          VoidId
        , BoolId
        , IntegerId
        , FloatId
        , FilenameId  // Not sure for that type, but why not as it will be used a lot !
                    // I am now thinking of making Filename as String with properties
                    // So this has to be removed at some point.. just I don't forget
        , StringId    // Not sure
        , StructureId // A structure contains different types
        , ArrayId     // An array of one type
        , PointerId   // Not sure ....
        , LastTypeId
        // , Value ??
        // , Parameter ??
        // , Node ??
    } BaseTypeId;
    // TODO : ?? Add Plug and Parameter ?


protected:
    /// Constructor is protected, as it should be only one instance of
    /// each type in the application to make type comparison as easy as pointer comparison
    /// Therefore it's implemented as a singleton with the get function.
    BaseType(BaseTypeId id)
    : m_typeId(id)
    {}

    /// This class can be inherited
    virtual ~BaseType(){}

private:
    /// The type id of this instance
    BaseTypeId  m_typeId;
};


/// The function Type() returns an unique pointer on the type
/// passed in the template. So it's easy to have access to a
/// type : Type<Float>() or Type<Int> or Type<Node> or Type<Value>
template<typename DerivedType>
inline
BaseType * Type() {
    return DerivedType::getType();
}

// TODO remove
typedef int TypeId;


/// STILL to be implemented and tested
template<typename T>
const char * const TypeName(const T &t){return t.typeName();}

template<typename T>
const char * const TypeName(T *t){return t->typeName();}

template<typename T>
const char * const TypeName(){return T::s_typeName;}

}; // namespace fission
#endif//TYPE_H
