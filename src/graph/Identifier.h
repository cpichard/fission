#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include <string>

template<typename TypeInfo>
struct Identifier
{
    Identifier(const std::string &name, size_t id, TypeInfo *m_type=NULL)
    : m_name(name)
    , m_id(id)
    , m_type(NULL){}

    std::string m_name;
    size_t      m_id;
    TypeInfo *m_type;
    // TODO : does it need an owner as well ?
    // T::OwnerType *m_owner;
};



#endif//IDENTIFIER_H
