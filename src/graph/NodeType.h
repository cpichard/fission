#ifndef NODETYPE_H
#define NODETYPE_H

class NodeType
{
public: 
    virtual const char * typeName() const=0; 
    struct Input 
    {   
        Input(const char *name, const char *type)
        : m_name(name)
        , m_type(type)
        {}
        const char *m_name; 
        const char *m_type;
    };
    struct Output 
    {   
        Output(const char *name, const char *type)
        : m_name(name)
        , m_type(type)
        {}
        const char *m_name; 
        const char *m_type;
    };
    struct Param {const char *inputName; int inputType;};
};

#endif//NODETYPE_H
