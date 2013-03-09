#include "Context.h"

using namespace fission;
//extern "C" {
double TestSource_execute(Context ctx)
{
    double tmp=0;
    for(int i=0; i < ctx.m_first;i++)
    {
        tmp=tmp+1.0;
    }
    return tmp;
};
