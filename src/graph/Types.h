#ifndef TYPES_H
#define TYPES_H

#include <string>
namespace fission {

// TODO : StandardTypes.h
//struct Integer {}
//alloc
//release
//assign
//cast

typedef enum {
    Unknown
    , ImageBuffer
    , Float
    , Integer
    , Bool
    , FileName
    , String
    , Custom
} KnownTypeId;

typedef int TypeId;

template<typename T>
const char * const TypeName(const T &t){return t.typeName();}

template<typename T>
const char * const TypeName(T *t){return t->typeName();}

template<typename T>
const char * const TypeName(){return T::s_typeName;}

}; // namespace fission
#endif//TYPES_H
