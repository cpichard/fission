
#include "TestOp.h"
#include "engine/Context.h"

ImplementNode(TestOp)

ImplementOutputs(TestOp, NewOutput("OutValue", Float))
ImplementInputs(TestOp, NewInput("InValue1", Float), NewInput("InValue2", Float))
ImplementParams(TestOp)

extern "C"
double TestOp_execute(const fission::Context &ctx, double a, double b) {
    return a+b;
}


#if 0

// Declare the structure needed to compute the data
ComputationDataStruct(TestOp, ComputeData)
{
    float val;
};

ComputeDataInContextFunc(TestOp)
{
   data.val=getParam("InValue", context);
   data.val*=Time(context);
}

PixelProcessFunc(TestOp)
{
    return in0*data.val+in1;
}

ComputeStruct(TestOp)
{
    float val;
    float k;
}

//double fission::TestOP_execute(const Context &ctx, double a, double b){
PixelProcess(TestOp)
{
    return in1*data.val+in2;
}

PixelProcessInPlace(TestOp)
{}


RegionProcess(TestOp)
{}


ContextChange()

ROIChange()

DODChange()
#endif
