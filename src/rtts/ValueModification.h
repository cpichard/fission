#ifndef VALUEMODIFICATION_H
#define VALUEMODIFICATION_H
#include <iostream>
#include <cstdarg>

/// Tests of encapsuling a value modification,
/// mainly to ease the undo/redo framework


namespace fission {

#define VA_ARG_START(a) \
{\
    char * arg_ptr = const_cast<char*>((a));\

#define VA_ARG_SET(V, T) \
    char * val_ptr = reinterpret_cast<char*>(&(V));\
    for(size_t i=0; i < sizeof(T); i++) { *arg_ptr++=*val_ptr++;} \

#define VA_ARG_GET(V, T) \
    char * val_ptr = reinterpret_cast<char*>(&(V)); \
    for(size_t i=0; i < sizeof(T); i++) { *val_ptr++=*arg_ptr++; } \

#define VA_ARG_STOP(a) \
}

// List of available parameter modifications
typedef enum {
    DoNothing = 0,
    SetIntValue,
    SetFloatValue,
    // TranslateCurve ?? // etc...
} ModificationKind;



/// Store a value modification in a compact structure
struct ValueModification {
    // Set modification arguments
    // it basically stores the passed values in the m_args buffer

    template <typename T1>
    inline void prepare( ModificationKind modifType, T1 arg1)
    {
        m_modification = modifType;
        VA_ARG_START(m_ap());
            VA_ARG_SET(arg1, T1);
        VA_ARG_STOP(m_ap());
    }

    template <typename T1>
    inline void unpack(T1 &arg1) const
    {
        VA_ARG_START(m_ap());
            VA_ARG_GET(arg1, T1);
        VA_ARG_STOP(m_ap());
    }

    void dump() const
    {
        float toto;
        VA_ARG_START(m_ap());
            VA_ARG_GET(toto, float);
        VA_ARG_STOP(m_ap());

        std::cout << "Dump=" << toto << std::endl;

    }
    enum    {MAX_ARGS_SIZE=64};

    inline char * m_ap()  { return m_args; }
    inline const char * m_ap() const { return const_cast<char *>(m_args); }

    // Modification kind
    ModificationKind m_modification;

    // Buffer of 32 bytes of args
    char    m_args[MAX_ARGS_SIZE];
};

};//namespace fission
#endif//VALUEMODIFICATION_H
