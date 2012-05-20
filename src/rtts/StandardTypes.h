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
};

class Int : public BaseType {
protected:
    Int()
    : BaseType(IntegerId)
    {}
public:
    static BaseType * getType();
private:
    static Int *m_instance;
};

class Float : public BaseType {
protected:
    Float()
    : BaseType(FloatId)
    {}
public:
    static BaseType * getType();
private:
    static Float *m_instance;
};

class String : public BaseType {
};

}; // namespace fission
#endif//STANDARDTYPES_H
