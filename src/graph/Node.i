
%{
#include "Node.h"
%}

%include "std_string.i"

// Name concept
%include "Name.i"


namespace fission {

%template(nodename) fission::Name<fission::Node>;

class Node
{
public:
    Node(const std::string &name)
    : m_name(name){};
    virtual ~Node(){};

    // Extend with function name
    %extend {
        inline std::string name(){return fission::Name(*$self);}
    }

protected:
    virtual void * getResult()=0;
    virtual Status execute(Context &)=0;
};

};

