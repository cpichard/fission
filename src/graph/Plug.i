
%include "std_string.i"
%{
#include "graph/Plug.h"
%}

namespace fission {
class Plug
{
public:
    Plug(const std::string &name, size_t id, const fission::PlugType *info);
};

};
