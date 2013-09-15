#include "TestSource.h"
#include "engine/Context.h"
#include <cstdio> // fopen, fread, fclose

ImplementNode(TestSource)

ImplementOutput(TestSource, NewOutput("Value", Float))
ImplementInputs(TestSource)

ImplementParams(TestSource,
    NewParam("val", Int),
    NewParam("file", String))

extern "C" {
double TestSource_execute(fission::Context ctx, const int val, const char *file)
{
    const size_t array_size = val;
    // Open a file and read the values in it
    FILE *fp = fopen(file, "rb");
    if(fp) {
        double *buffer = (double*)malloc(array_size*sizeof(double));
        fread(buffer, sizeof(double), array_size, fp);
        fclose(fp);
        double toto[255];
        for(int i=0; i<255; i++) {
            toto[i] = buffer[i];
        }
    } 
    else {
        printf("unable to open file %s, returning 100\n", file);
        return 100;
    }

    return (double)ctx.m_first;
};
};
