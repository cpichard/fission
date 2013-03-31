#ifndef OBJECTID_H
#define OBJECTID_H

#include <string>

/// ObjectId 
/// defines an object : a name, an ID and a type
/// The type is stored as a pointer to an unique type description
/// This struct should be as small as possible
template<typename T>
struct ObjectId
{
    // NOTE : NULL type shouldn't be allowed
    ObjectId(const std::string &name, size_t id, const T *type=NULL)
    : m_name(name)
    , m_id(id)
    , m_type(type){}

    std::string m_name; // Can the name change ? should I use a const char * instead ?
                        // and add a m_displayName that can change ?
    size_t      m_id;
    const T     *m_type;
    // TODO : does it need an owner as well ?
    // T::OwnerType *m_owner;

    // static m_objectLookup[]
    // static ObjectId * lookup(size_t id);
    // static m_lastId;

};



#endif//OBJECTID_H
