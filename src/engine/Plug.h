#ifndef PLUG_H
#define PLUG_H

#include <string>
#include "GraphVertex.h"
/// This class defines a plug, a entity that can be plug to another entity
class Plug : GraphVertex<Plug>
{
public: 
    Plug(const std::string &name)
    : m_name(name) {}
    ~Plug(){}   

protected:
    std::string &m_name; 
};



#endif//PLUG_H
