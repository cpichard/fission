
%{
#define SWIG_FILE_WITH_INIT
#include <NodeGraph.h>
%}

%include "std_string.i"
%include "Node.i"

class NodeGraph : public Node
{
public:
    NodeGraph(const std::string &name);
    ~NodeGraph();

    Node & createNode(const std::string &nodeType, const std::string &nodeName);
};
