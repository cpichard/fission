#ifndef IMAGEREADER_H
#define IMAGEREADER_H

#include "Node.h"

namespace fission {

class ImageReader : public Node
{
public:
    ImageReader(const std::string &name);
    virtual ~ImageReader();

protected:
    virtual void * getResult();
    virtual Status execute(Context &);
};

}; // namespace fission
#endif//IMAGEREADER_H
