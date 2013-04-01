#ifndef OBJECTID_H
#define OBJECTID_H

#include <string>

/// ObjectId 
/// defines an object : a name, an ID and a type
/// The type is stored as a pointer to an unique type description
/// This struct should be as small as possible

namespace fission {

struct ObjectCounter {
    static size_t next(){return s_lastObjectId++;}
    static size_t s_lastObjectId;
};

template<typename T>
struct ObjectId {

    // NOTE : NULL type shouldn't be allowed
    ObjectId(const std::string &name, const T *type=NULL)
    : m_name(name)
    , m_id(ObjectCounter::next())
    , m_type(type){}

    std::string m_name; // Can the name change ? should I use a const char * instead ?
                        // and add a m_displayName that can change ?
    size_t      m_id;
    const T     *m_type;

    // static m_objectLookup[]
    // static ObjectId * lookup(size_t id);
};

};



#endif//OBJECTID_H
