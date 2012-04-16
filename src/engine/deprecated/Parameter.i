%{
#include "Parameter.h"
#include "Node.h"
%}


class Parameter
{
public:
    Parameter();
    virtual ~Parameter();
};


// Parameter
%include "Name.i"
%template(NameParameter) Name<Parameter>;

