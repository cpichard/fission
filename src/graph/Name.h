#ifndef NAME_H
#define NAME_H
#include <string>

namespace fission {

static const std::string NULLStr("NULL");


// Returns the name, if the structure have one
template<typename NamedType>
inline const std::string & Name(const NamedType &p){return p.m_name;}

template<typename NamedType>
inline const std::string & Name(NamedType *p){return p ? p->m_name : NULLStr;}
// TODO : unique name
//
//
};

#endif//NAME_H
