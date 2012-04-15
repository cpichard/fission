#ifndef NODE_H
#define NODE_H

#include <list>
#include "Types.h"

#include "Parameter.h"
#include "Context.h"
#include "Status.h"
#include "Plug.h"
#include "List.h"

// Interface class for a computing Node
// a Node is a plug with parameters and functions
// It provides utility methods for inherited classes

typedef int NodeId;
typedef int LinkId;

// NOTE : may be it can be a GraphVertex<Node*>
class Node : public Plug
{
    // Friend classes and functions
    friend class Engine;
    friend class NodeGraph;
    friend LinkId connect(Node &src, PlugId p, Node &dst, PlugId g);
    friend bool disconnect(Node &src, Node &dst);
    template <typename TN> friend std::string Name(TN &p);
    template <typename TN> friend const char * const TypeName(const TN &p);
    template <typename TN> friend const char * const TypeName();

public:
    Node(const std::string &name);
    virtual ~Node();

    // TOD : move in private ?
    virtual const char * typeName() const {return Node::s_typeName;} 

    Plug & input(int i){return *m_incoming[i];};
    Plug & output(int i){return *m_outgoing[i];};

protected:
    // Functions used by child nodes to register their inputs, results and parameters
    Plug & addInput(const std::string &name, TypeId);
    Plug & addOutput(const std::string &name, TypeId);
    bool addParameter(const std::string &name, TypeId);

    unsigned int nbInputs() const;
    unsigned int nbOutputs() const;

    bool removeInput(Plug & plug);
    bool removeOutput(Plug & plug);
    bool removeParameter(Plug & plug);

    // a table with function pointers
    //FunctionTable   m_functionTable;

    // TODO : find a way to add functions without using rtti and
    // virtual void * getResult()=0;
    // virtual Status execute(Context &)=0;
    // TODO 
    // Get tasks
    //

private:
    //std::string m_name;         // Name of the node
    size_t      m_id;           // Id of the node
    
    // Parameters of the node. They are not registered as plugs.
    ParameterPtrList   m_params;

    
    static const char * const s_typeName;

};


// API on the nodes
LinkId connect(Node &src, PlugId plugIdSrc, Node &dst, PlugId plugIdDst);
bool disconnect(Node &src, Node &dst);

// TODO vaarg
bool setParameter(Node &node, const std::string &param, std::string value);

#endif//NODE_H
