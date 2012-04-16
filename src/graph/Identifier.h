#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

// TODO : rename with a more familiar name

template<typename T>
struct Identifier
{
    Identifier(const std::string &name, size_t id, const T *type=NULL)
    : m_name(name)
    , m_id(id)
    , m_type(type){}

    std::string m_name;
    size_t      m_id;
    const T     *m_type;
    // TODO : does it need an owner as well ?
    // T::OwnerType *m_owner;
};



#endif//IDENTIFIER_H
