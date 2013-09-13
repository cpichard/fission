#ifndef TYPE_H
#define TYPE_H

/// TODO Still not sure
#include <string>

namespace fission {

struct ValueModification;
class ValueTuple;

/// The type class is the base class of all other types
/// The design is more than pretty similar to the llvm one
/// BaseType is the root of the type tree for the lib
/// The type tree may include parameters, node, values, etc
/// This is WIP
class BaseType {
public:

    /// Basic types used in the application
    /// Not used atm
    /// TODO : use c++0x enum class
    typedef enum {
          VoidId
        , BoolId
        , IntegerId
        , FloatId
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

    //
    virtual size_t size() const = 0;
    virtual void * alloc() const = 0;
    virtual void free(void *) const = 0;

    // See Value !!


protected:
    /// Constructor is protected, as it should be only one instance of
    /// each type in the application to make type comparison as easy as pointer comparison
    /// Therefore it's implemented as a singleton with the get function.
    BaseType(BaseTypeId id)
    //: m_typeId(id)
    {}

    /// This class can be inherited
    virtual ~BaseType(){}


private:
    /// The type id of this instance
    //BaseTypeId  m_typeId;
};


/// The function Type() returns an unique pointer on the type
/// passed in the template. So it's easy to have access to a
/// type : Type<Float>() or Type<Int> or Type<Node> or Type<Value>
template<typename DerivedType>
inline
const BaseType * Type() {
    return DerivedType::getType();
}

template<typename lType, typename rType>
inline bool isType(const rType &v) {
    return Type<lType>()==&v;
    ///return Type<lType>()==TypeOf(v);
}

template<typename lType, typename rType>
inline bool isType(const rType *v) {
    return Type<lType>()==v;
    ///return Type<lType>()==TypeOf(v);
}

// Unknown type is associated to Void.
// I may rename Void with a more precise name
// is it TypeOf
template <typename ValueType>
inline
const BaseType * TypeOf(ValueType &v){return v.getType();}

template <typename ValuedType>
inline
const BaseType * ValueTypeOf(const ValuedType &v){return v.m_valueType;}

template <typename ValuedType>
inline
const BaseType * ValueTypeOf(ValuedType *v){return v->m_valueType;}

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
