#include "GLDisplay.h"

static NodeType glDisplayType=9;

GLDisplay::GLDisplay(const std::string &name)
: Node(name, 0, &glDisplayType)
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
