#include "ImageWriter.h"


ImageWriter::ImageWriter (const std::string &name)
: Node (name)
{
}

ImageWriter::~ImageWriter ()
{
}

void *
ImageWriter::getResult ()
{
    return NULL;
}

Status
ImageWriter::execute (Context &)
{
    return SUCCESS;
}
