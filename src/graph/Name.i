
%module fission
#include "std_string.i"
%{
#include "graph/Name.h"
%}

// Returns the name, if the structure have one
template<typename NamedType>
inline const std::string & Name(NamedType &p){return p.m_name;}

template<typename NamedType>
inline const std::string & Name(NamedType *p){return p ? p->m_name:NULLStr;}

