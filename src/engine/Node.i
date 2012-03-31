
%{
#include "Node.h"
%}

%include "std_string.i"

// Name concept
%include "Name.i"
%template(nodename) Name<Node>;

class Node
{
public:
    Node(const std::string &name)
    : m_name(name){};
    virtual ~Node(){};

    // Extend with function name
    // Name concept
    %extend {
        inline std::string name(){return Name(*$self);}
    }

protected:
    virtual void * getResult()=0;
    virtual Status execute(Context &)=0;
};

bool connect(Node &src, Node &dst);
bool disconnect(Node &src, Node &dst);

// TODO vaarg
bool setParameter(Node &node, const std::string &param, std::string value);

