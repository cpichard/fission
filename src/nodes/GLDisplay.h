#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include "Node.h"
#include "Status.h"
#include "Context.h"

class GLDisplay : public Node
{
public:
    GLDisplay(const std::string &name);
    virtual ~GLDisplay();

    void displayLastResult();

protected:
    virtual void * getResult();
    Status execute(Context &);
};

#endif//GLDISPLAY_H