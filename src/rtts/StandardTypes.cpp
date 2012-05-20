#include "StandardTypes.h"
namespace fission {

/// Float
Float * Float::m_instance=NULL;
BaseType * Float::getType() {
    // Singleton
    // TODO : deallocation
    // TODO : move the creation of the type 
    //  at the loading of the lib, not here
    if (!m_instance) {
        m_instance = new Float();
    }
    return m_instance;
}

Int * Int::m_instance=NULL;
BaseType * Int::getType() {
    // Singleton
    // TODO : deallocation
    if (!m_instance) {
        m_instance = new Int();
    }
    return m_instance;
}

}; // namespace fission
