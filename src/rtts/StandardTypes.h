#ifndef STANDARDTYPES_H
#define STANDARDTYPES_H

#include "Type.h"

/// This file contains all the standard types
/// we use in the library.
namespace fission {

/// TODO : should I add Node as a Basic type ?
/// Should Node have subclasses ?


class Void : public BaseType {
protected:
    Void()
    : BaseType(VoidId)
    {}
public:
    static const BaseType * getType();
private:
    static Void *m_instance;
};


///////////////////////////// Int /////////////////////////////

class Int : public BaseType {
protected:
    Int()
    : BaseType(IntegerId)
    {}
public:
    static const BaseType * getType();
private:
    static Int *m_instance;
};


/////////////////////////// Float //////////////////////////////

class Float : public BaseType {
protected:
    Float()
    : BaseType(FloatId)
    {}
public:
    static const BaseType * getType();
private:
    static Float *m_instance;
};

// Specialization for float

///////////////////////// String //////////////////////////////

class String : public BaseType {
};

/// Specialization for standard c++ types
template <> inline const BaseType * Type<int>(){return Int::getType();}
template <> inline const BaseType * Type<float>(){return Float::getType();}
template <> inline const BaseType * Type<double>(){return Float::getType();}

}; // namespace fission
#endif//STANDARDTYPES_H
