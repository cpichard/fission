#include <iostream> // DEBUG
#include "StandardTypes.h"
#include "ValueModification.h"
#include <cstdlib> // malloc / free
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
void * Void::alloc() const {return NULL;}
void Void::free(void *data) const {}


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

void * Float::alloc() const { return malloc(size());}
void Float::free(void *data) const { free(data);}

Int * Int::m_instance=NULL;
const BaseType * Int::getType(){
    // Singleton
    // TODO : deallocation
    if (!m_instance) {
        m_instance = new Int();
    }
    return m_instance;
}

void * Int::alloc() const { return malloc(size());}
void Int::free(void *data) const { free(data); }

String *String::m_instance = NULL;
const BaseType * String::getType() {
    if (!m_instance) {
        m_instance = new String();
    }
    return m_instance;
}

void * String::alloc() const { return (void *)new std::string();}
void String::free( void *data ) const { delete static_cast<std::string*>(data);}

}; // namespace fission
