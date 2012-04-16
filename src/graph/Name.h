

// Name concept
template<typename NamedType>
inline const std::string & Name(NamedType &p){return p.m_name;}

template<typename NamedType>
inline const std::string & Name(NamedType *p){return p->m_name;}
// TODO : unique name 
//
//

