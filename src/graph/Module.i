%include "std_list.i"
%include "std_string.i"
%include "graph/Node.i"
%include "graph/NodeDesc.i"
%include "graph/Plug.i"
%{
#include "graph/Module.h"
%}

%feature("notabstract") fission::Module;

namespace fission {

class Module : public Node
{
public:
    Module(const std::string &name);

    Node *createNode(const std::string &nodeName, const std::string &nodeTypeName);
    void disposeNode(Node *);

    void registerNodeDesc(NodeDesc *newType);
    void unregisterNodeDesc(NodeDesc *type);

    void connect(Plug *src, Plug *dst);
};

};
