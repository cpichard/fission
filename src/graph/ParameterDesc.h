#ifndef PARAMETERDESC_H
#define PARAMETERDESC_H


namespace fission {


struct ParameterDesc {
    
    // TODO ValueType *m_type;

    //virtual bool isPOD()
    //bool isCompound()
    //bool alloc()
    //bool release()
    //size_t sizeOf()
    // standard properties ?

};

template <typename PODType, const char *TypeName>
struct PODParameter : public ParameterDesc
{};






};
#endif//PARAMETERDESC_H
