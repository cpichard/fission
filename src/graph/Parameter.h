#ifndef PARAMETER_H
#define PARAMETER_H

#include "Plug.h"
#include "rtts/Type.h"
#include "rtts/ValueModification.h"

namespace fission {

//class Value;

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

/// A Parameter is a plug that contains data during the whole life of the
/// program
class Parameter : public Plug {

    friend class Node;

public:
    Parameter( const char *name, const BaseType *valueType );
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

    float   asFloat();
    int     asInt();
    const char * asString();


private:
    //Value       *m_data;
    //const BaseType  *m_type; // Type of m_data, should be stored in Value
    char            *m_data; // Blind pointer to the data owned by the parameter

    // TODO properties of a parameter
    // Properties   m_properties;
};

}; // namespace fission
#endif//PARAMETER_H

