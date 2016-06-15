#ifndef SLIBC_FACEDETECTION_H
#define SLIBC_FACEDETECTION_H

#include "Types.h"
#include <dlib/image_processing/frontal_face_detector.h>

namespace slibc
{
    class FaceDetection {

    public:
        // TODO: Train dataset
        // TODO: From URL
        FaceDetection(const char* model);
        std::string largestFace(std::string path, unsigned long cropSize, std::string outpath = ".");

    private:
        dlib::frontal_face_detector detector;
        dlib::shape_predictor predictorModel;

        void getDetector();
        void deserializeModel(const char* modelFile);
        void loadFile(std::string filename, sl::ImageDArray& dest);

        sl::Rectangle maxRect(const std::vector<sl::Rectangle>& vec) {
            auto maxBB = std::max_element(vec.begin(), vec.end(), [](const sl::Rectangle& lhs, const sl::Rectangle& rhs) {
                return lhs.area() < rhs.area();
            });

            return *maxBB;
        }

        std::vector<sl::Rectangle> detectFaces(std::string filename);
        std::vector<sl::Rectangle> detectFaces(const sl::ImageDArray& img);

        sl::ObjectModel modelLandmarks(const sl::ImageDArray& img, const sl::Rectangle bb);
        std::vector<sl::ObjectModel> modelLandmarks(const sl::ImageDArray& img, const std::vector<sl::Rectangle> bb);
        dlib::chip_details getCropParams(const sl::ObjectModel& landmarks, unsigned long croppedSize);
        void cropFace(const sl::ObjectModel& model, const sl::ImageDArray& src, sl::ImageDArray& dest, unsigned long size);

    };
}

#endif //SLIBC_FACEDETECTION_H
