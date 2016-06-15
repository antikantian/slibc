#ifndef SLIBC_TYPES_H
#define SLIBC_TYPES_H

#include <dlib/pixel.h>
#include <dlib/array2d.h>
#include <dlib/image_processing.h>

namespace sl
{
    typedef dlib::array2d<dlib::rgb_pixel> ImageDArray;
    typedef std::shared_ptr<ImageDArray> ImageDArrayPtr;
    typedef dlib::matrix<dlib::rgb_pixel> ImageDMat;
    typedef dlib::full_object_detection ObjectModel;
    typedef dlib::rectangle Rectangle;
    typedef dlib::rgb_pixel RGB;
}

#endif //SLIBC_TYPES_H
