%include "std_list.i"
%include "Node.i"
%include "Plug.i"

namespace fission {

class Module : public Node
{
public:
    Module(const std::string &name);
    Node *createNode(const std::string &nodeName, const std::string &nodeTypeName);

    void connect(fission::Plug *src, fission::Plug *dst);
};

};
