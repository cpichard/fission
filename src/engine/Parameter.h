#ifndef __PARAMETER_H__
#define __PARAMETER_H__

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


#endif//__PARAMETER_H__
