#include "include/ImageConversion.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <iostream>

using namespace slibc;

std::vector<float> ImageConversion::mat2Array(cv::Mat& mat) {
    int size = mat.rows;
    std::vector<float> array;

    for (int c = 0; c < 3; ++c) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                array.push_back((float)(mat.data[(i * size + j) * 3 + c]));
            }
        }
    }
    return array;
}

std::vector<float> ImageConversion::image2Array(std::vector<signed char> img) {
    cv::Mat mat;
    cv::imdecode(img, 1, &mat);
    return this->mat2Array(mat);
}

std::vector<float> ImageConversion::image2Array(std::string imgpath, int size) {
    cv::Mat mat = cv::imread(imgpath);

    if (mat.rows != size && mat.cols != size) {
        cv::resize(mat, mat, cv::Size(size, size));
    }

    return this->mat2Array(mat);
}

std::vector<float> ImageConversion::image2Array(std::string imgpath) {
    cv::Mat mat = cv::imread(imgpath);
    return this->mat2Array(mat);
}



