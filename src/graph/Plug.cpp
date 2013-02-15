#include "Plug.h"

using namespace fission;

// These two values are used a pointers to discriminate between 
// input and output plugs
// In the future we might need more complex structure, or may be not
const PlugType fission::PlugInputType=0;
const PlugType fission::PlugOutputType=1;
