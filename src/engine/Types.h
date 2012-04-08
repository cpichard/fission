#ifndef TYPES_H
#define TYPES_H

#include <string>

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
const char * const TypeName(){return T::s_typeName;}

#endif//TYPES_H
