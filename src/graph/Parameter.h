#ifndef PARAMETER_H
#define PARAMETER_H

#include "Plug.h"
#include "rtts/Type.h"
#include "rtts/ValueModification.h"

namespace fission {

/// Parameter 
/// a parameter has :
/// * a name
/// * an id
/// * a value or an array of values
/// * a property or an array of properties per value
/// A parameter belongs to a node
/// A parameter can set or get its values
/// A parameter add rules to a value, like a range of an int, default value
/// or proper formatting of a filename

typedef int ParameterType;

typedef ValueModification ParameterModification;


/// A Parameter is a plug that contains data during the whole life of the
/// program
class Parameter : public Plug {

    friend class Node;

public:
    Parameter( const char *name, size_t id, const BaseType * );
    virtual ~Parameter();

    // wip, ParameterModification allows to store the 
    // kind of modifications we want to apply on the Parameter
    // wip
    //void apply( const ParameterModification &pm );

    // Simple accessors for now
    void setFloat(float val);
    void setInt(int val);
    void setString(const char *val);

    // set and get works for simple types,
    // later on we will see how to handle complex types
    // like curves, grids, etc...
    void evalFloat(float &val);
    void evalInt(int &val);
    void evalString(std::string &val);

private:
    char            *m_data; // Blind pointer to the data owned by the parameter
    void            *m_owner;// Owner of the parameter, might be a node
    const BaseType  *m_type; // Type of m_data

    // TODO properties of a parameter
    // Properties   m_properties;
};

}; // namespace fission
#endif//PARAMETER_H

