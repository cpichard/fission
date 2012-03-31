#include "GLDisplay.h"


GLDisplay::GLDisplay(const std::string &name)
: Node(name)
{}

GLDisplay::~GLDisplay()
{}
    
void GLDisplay::displayLastResult(){}

void * GLDisplay::getResult()
{
    return NULL;
}

Status GLDisplay::execute(Context &)
{
}
