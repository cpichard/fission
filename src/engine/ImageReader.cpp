
#include "ImageReader.h"

ImageReader::ImageReader(const std::string &name)
: Node(name)
{
    // Parameters
    //addParameter("filename", FileName);
    // Input/outputs
    //addInput(); // the same for all plugs !
    //addResult("imageOut", ImageBuffer);
}

ImageReader::~ImageReader()
{}

void * ImageReader::getResult(){return NULL;}
Status ImageReader::execute(Context &){return SUCCESS;}
