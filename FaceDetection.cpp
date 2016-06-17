#include "include/FaceDetection.h"
#include <dlib/image_io.h>

using namespace slibc;

FaceDetection::FaceDetection(const char *model) {
    getDetector();
    deserializeModel(model);
}

// <--- Public interface ------------------------------------------->
std::string FaceDetection::largestFace(std::string path, unsigned long cropSize) {
    std::string op = "./";
    std::string tmpName = this->getUniquePath();
    return this->largestFace(path, cropSize, op, tmpName);
}

std::string FaceDetection::largestFace(std::string path, unsigned long cropSize, std::string outpath) {
    std::string tmpName = this->getUniquePath();
    return this->largestFace(path, cropSize, outpath, tmpName);
}

std::string FaceDetection::largestFace(std::string path, unsigned long cropSize, std::string outpath, std::string outfile) {
    sl::ImageDArray img;
    dlib::load_image(img, path);

    std::vector<sl::Rectangle> faces = this->detectFaces(img);

    sl::ObjectModel landmarks;

    if (faces.size() == 1) {
        landmarks = this->modelLandmarks(img, faces.front());
    } else if (faces.size() > 1) {
        landmarks = this->modelLandmarks(img, this->maxRect(faces));
    } else {
        dlib::pyramid_up(img);
        std::vector<sl::Rectangle> upsampled = this->detectFaces(img);

        if (upsampled.size() > 0) {
            landmarks = this->modelLandmarks(img, this->maxRect(upsampled));
        } else throw std::runtime_error("No faces detected in image");
    }

    sl::ImageDArray cropped;
    this->cropFace(landmarks, img, cropped, cropSize);

    std::string op = (outpath.back() == '/') ? outpath : outpath + "/";
    std::ostringstream filepath;
    filepath << op << outfile << ".jpg";
    dlib::save_jpeg(cropped, filepath.str());
    return filepath.str();
}

// <--- Private methods -------------------------------------------->

// <--- IO --->
void FaceDetection::getDetector() {
    detector = dlib::get_frontal_face_detector();
}

void FaceDetection::deserializeModel(const char *modelFile) {
    dlib::deserialize(modelFile) >> predictorModel;
}

void FaceDetection::loadFile(std::string filename, sl::ImageDArray& dest) {
    dlib::load_image(dest, filename);
}
// <--- End IO --->

// <--- Methods that return bounding boxes (i.e. rectangles) --->
std::vector<sl::Rectangle> FaceDetection::detectFaces(std::string filename) {
    sl::ImageDArray img;
    this->loadFile(filename, img);
    return this->detectFaces(img);
}

std::vector<sl::Rectangle> FaceDetection::detectFaces(const sl::ImageDArray& img) {
    std::vector<sl::Rectangle> bb = detector(img, 1);
    return bb;
}
// <--- End bounding box methods --->

// <--- Methods that return landmarks (i.e. sl::ObjectModel == dlib::full_object_detection --->
sl::ObjectModel FaceDetection::modelLandmarks(const sl::ImageDArray& img, const sl::Rectangle bb) {
    return predictorModel(img, bb);
}

std::vector<sl::ObjectModel> FaceDetection::modelLandmarks(const sl::ImageDArray& img, const std::vector<sl::Rectangle> bb) {
    std::vector<sl::ObjectModel> models;
    for (unsigned long i = 0; i < bb.size(); ++i)
    {
        sl::ObjectModel m = modelLandmarks(img, bb[i]);
        models.push_back(m);
    }
    return models;
}
// <--- End landmark methods --->

// <--- Methods for cropping images --->
// Given a face model and an output size, returns an object that can be given to dlib::extract_image_chip
dlib::chip_details FaceDetection::getCropParams(const sl::ObjectModel& landmarks, unsigned long croppedSize) {
    return dlib::get_face_chip_details(landmarks, croppedSize, 0.0);
}

void FaceDetection::cropFace(const sl::ObjectModel& model, const sl::ImageDArray& src, sl::ImageDArray& dest, unsigned long size) {
    dlib::chip_details trans = getCropParams(model, size);
    dlib::extract_image_chip(src, trans, dest);
}
// <--- End cropping methods --->


