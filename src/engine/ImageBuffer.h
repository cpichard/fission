#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include <cstdlib>

class ImageBuffer
{
    //friend size_t ImageWidth(const ImageBuffer &ib);
    //friend size_t ImageHeight(const ImageBuffer &ib);

public:
    ImageBuffer()
    : m_bufferWidth(0)
    , m_bufferHeight(0)
    , m_bufferStrip(0)
    , m_imageWidth(0)
    , m_imageHeight(0){};

    virtual ~ImageBuffer(){};

private:
    size_t  m_bufferWidth;
    size_t  m_bufferHeight;
    size_t  m_bufferStrip;

    size_t  m_imageWidth;
    size_t  m_imageHeight;
    size_t  m_imageChannels;
    void    *m_data;
};

//size_t ImageWidth(const ImageBuffer &ib){return ib.m_imageWidth;}
//size_t ImageHeight(const ImageBuffer &ib){return ib.m_imageHeight;}

#endif//IMAGEBUFFER_H
