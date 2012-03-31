#include "JpegReader.h"
#include "jpeglib.h"


JpegReader::JpegReader(const std::string &name)
: Node(name)
{
    // Set parameters : file name    
}

JpegReader::~JpegReader()
{}


void * JpegReader::getResult(){ return NULL; }
Status JpegReader::execute(Context &){ return SUCCESS; }


void readJpeg( const std::string &filename, ImageBuffer &imageBuffer )
{ }

