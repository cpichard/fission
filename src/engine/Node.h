#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>

#include "Parameter.h"
#include "Context.h"
#include "Status.h"
#include "Plug.h"
#include "List.h"

// Interface class for a computing node

class Node
{
    // Friend classes
    friend class Engine;
    friend bool connect(Node &src, Node &dst);
    friend bool disconnect(Node &src, Node &dst);
    template <typename TN> friend std::string Name(TN &p);

public:
    Node(const std::string &name)
    : m_name(name){};
    virtual ~Node(){};

protected:
    // TODO : find a way to add functions without using rtti and
    virtual void * getResult()=0;
    virtual Status execute(Context &)=0;
    // TODO 
    // Get tasks
    //
private:
    std::string m_name;         // Name of the node

    // Inputs and outputs of this node
    PlugPtrList m_inputs;   // Inputs
    PlugPtrList m_outputs;  // Outputs
    
    // Parameter of the node
    ParameterPtrList   m_params;
};


// API on the nodes
bool connect(Node &src, String &plugName, Node &dst, String &plugName);
bool disconnect(Node &src, Node &dst);

// TODO vaarg
bool setParameter(Node &node, const std::string &param, std::string value);

#endif//NODE_H
