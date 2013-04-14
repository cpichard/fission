
%{
#include "graph/Node.h"
#include "graph/Name.h"
#include "graph/NodeDesc.h"
%}

%include "std_string.i"
%include "std_vector.i"
%include "graph/NodeDesc.i"

// TODO : check why template Name is not recognized 
//%include "graph/Name.i"
//%template(NodeName) fission::Name<fission::Node>;


%template(NodeVector) std::vector<fission::Node*>;

namespace fission {


class Node
{
public:
    Node(const std::string &name, const NodeDesc *type);
    virtual ~Node(){};

    // Extend with function name
    %extend {
        inline std::string name(){return fission::Name(*$self);}
    }

    const std::vector<Node*> & getNodes() const;
};

};

