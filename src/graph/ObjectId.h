#ifndef OBJECTID_H
#define OBJECTID_H

#include <string>

/// ObjectId stores data we need to
/// define an object : a name, an ID and a type

template<typename T>
struct ObjectId
{
    // NOTE : NULL type shouldn't be allowed
    ObjectId(const std::string &name, size_t id, const T *type=NULL)
    : m_name(name)
    , m_id(id)
    , m_type(type){}

    std::string m_name; // Can the name change ?
    size_t      m_id;
    const T     *m_type;
    // TODO : does it need an owner as well ?
    // T::OwnerType *m_owner;
};



#endif//OBJECTID_H
