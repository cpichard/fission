#ifndef PARAMETERDESC_H
#define PARAMETERDESC_H

namespace fission {


struct ParameterDesc {

    //virtual bool isPOD()
    //bool isCompound()
    //bool alloc()
    //bool release()
    //size_t sizeOf()

};

template <typename PODType, const char *TypeName>
struct PODParameter : public ParameterDesc
{};




};
#endif//PARAMETERDESC_H
