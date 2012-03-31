
#include "ImageReader.h"

ImageReader::ImageReader(const std::string &name)
: Node(name)
{}


ImageReader::~ImageReader()
{}

void * ImageReader::getResult(){return NULL;};
Status ImageReader::execute(Context &){return SUCCESS;};
