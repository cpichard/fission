#include "Context.h"

#include <stdio.h>

using namespace fission;

double TestSink_execute(const Context ctx, double a){
    printf("sink received: %g\n", a);
    // Returning a because we don't handle functions returning void atm
    return a;
}
