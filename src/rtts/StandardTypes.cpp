#include "StandardTypes.h"
namespace fission {

/// Void
Void * Void::m_instance=NULL;
const BaseType * Void::getType() {
    // Singleton
    // TODO : deallocation
    // TODO : move the creation of the type 
    //  at the loading of the lib, not here
    if (!m_instance) {
        m_instance = new Void();
    }
    return m_instance;
}

/// Float
Float * Float::m_instance=NULL;
const BaseType * Float::getType() {
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
const BaseType * Int::getType() {
    // Singleton
    // TODO : deallocation
    if (!m_instance) {
        m_instance = new Int();
    }
    return m_instance;
}

}; // namespace fission
