#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>

// Base class for a parameter
class Parameter
{
public:
    template<typename TN> friend std::string Name(TN &p);

    Parameter();
    virtual ~Parameter();

protected:
    std::string m_name;
};


#endif//PARAMETER_H
