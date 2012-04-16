
%{
#define SWIG_FILE_WITH_INIT
#include <Node.h>
#include <ImageWriter.h>
%}

%include "Node.i"

class ImageWriter : public Node
{
    friend class Engine;

public:
    ImageWriter(const std::string name);
    virtual ~ImageWriter();

protected:
    virtual void * getResult();
    Status execute(Context &);

};

