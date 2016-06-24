#ifndef SLIBC_IMAGECONVERSION_H
#define SLIBC_IMAGECONVERSION_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

namespace slibc
{

    class ImageConversion {

    public:
        ImageConversion() {}
        std::vector<float> image2Array(std::vector<signed char> img);
        std::vector<float> image2Array(std::string imgpath, int size);
        std::vector<float> image2Array(std::string imgpath);

    private:
        std::vector<float> mat2Array(cv::Mat& mat);
    };
}

#endif //SLIBC_IMAGECONVERSION_H
