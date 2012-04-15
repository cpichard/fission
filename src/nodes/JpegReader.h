#ifndef JPEGREADER_H
#define JPEGREADER_H

#include "Node.h"

// Simple jpeg reader only for testing

class JpegReader : public Node
{
public:
    JpegReader(const std::string &name);
    ~JpegReader();

protected:
    virtual void * getResult();
    virtual Status execute(Context &);
};


#endif//JPEGREADER_H
