
%{
#include "engine/JITEngine.h"
%}
namespace fission {
class JITEngine
{
public:
    JITEngine();
    ~JITEngine();

    NodeDesc * loadNodeDescription(const char *filename);
};
};
