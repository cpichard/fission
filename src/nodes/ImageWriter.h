#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include "Node.h"

namespace fission {
class ImageWriter : public Node
{
    friend class Engine;

public:
    ImageWriter(const std::string &name);
    virtual ~ImageWriter();

protected:
    virtual void * getResult();
    Status execute(Context &);

};
}; // namespace fission
#endif//IMAGEWRITER_H
