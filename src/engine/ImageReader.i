
%{
#define SWIG_FILE_WITH_INIT
#include <Node.h>
#include <ImageReader.h>
%}

%include "Node.i"

class ImageReader : public Node
{
public:
    ImageReader(const std::string &name);
    virtual ~ImageReader();

protected:
    virtual void * getResult();
    virtual Status execute(Context &);
};
