#include "../include/FaceDetection.h"

using namespace slibc;

int main(int argc, char** argv) {

    try {
        if (argc == 1) {
            std::cout << "./maxface [model file] path-to-jpeg(s)" << std::endl;
            return 0;
        }

        FaceDetection detect(argv[1]);

        for (int i = 2; i < argc; ++i) {
            std::cout << detect.largestFace(argv[i], 96) << std::endl;
        }
    } catch (std::exception& e) {
        std::cout << "\nError..." << std::endl;
        std::cout << e.what() << std::endl;
    }

}