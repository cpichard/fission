
%include "std_string.i"
%{
#include "graph/Plug.h"
%}

typedef int fission::PlugType;

namespace fission {

class Plug
{
public:
    Plug(const std::string &name, const fission::PlugType *info, const BaseType *valueType);
};

};
