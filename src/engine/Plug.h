#ifndef PLUG_H
#define PLUG_H

#include <string>
#include "GraphVertex.h"

/// This class defines a plug, a entity that can be plug to another entity
class Plug : public GraphVertex<Plug*>
{

public: 
    Plug(const std::string &name)
    : m_name(name) {}
    ~Plug(){}   

    // Types definitions
    typedef size_t Id; // Type of a plug id

protected:
    // Plug infos
    std::string m_name;
    
    //
    Id  m_id;  
};

typedef Plug::Id PlugId;

#endif//PLUG_H
