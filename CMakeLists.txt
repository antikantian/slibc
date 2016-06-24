cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/bin")
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  "${CMAKE_SOURCE_DIR}/lib")

project(slibc)
cmake_policy(SET CMP0048 OLD)

#find_package(X11)
#include_directories(${X11_INCLUDE_DIR})

include(external/dlib/dlib/cmake NO_POLICY_SCOPE)
set(DLIB_NO_GUI_SUPPORT ON CACHE "" INTERNAL FORCE)
set(USE_AVX_INSTRUCTIONS ON CACHE "" INTERNAL FORCE)

find_library(s3 aws-cpp-sdk-s3)

find_package(Boost COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIR})

find_package(OpenCV 3)
include_directories(${OpenCV_INCLUDE_DIR})

include_directories(${CMAKE_SOURCE_DIR}/include)
set(source_files
    FaceDetection.cpp
    ImageConversion.cpp)

add_library(slibc SHARED ${source_files})
target_link_libraries(slibc dlib ${Boost_LIBRARIES} ${OpenCV_LIBS})

find_package(Swig REQUIRED)
include(UseSwig)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

find_package(Java REQUIRED)
include(UseJava)

set(CMAKE_SWIG_FLAGS -package co.quine.slibj)
set(CMAKE_SWIG_OUTDIR "${CMAKE_SOURCE_DIR}/../slibj/src/main/java/co/quine/slibj")
set_source_files_properties(swig_interface.i PROPERTIES CPLUSPLUS ON)
set_property(SOURCE swig_interface.i PROPERTY SWIG_MODULE_NAME ${SWIG_MODULE_${name}_REAL_NAME})
swig_add_module(slibj java swig_interface.i ${source_files})
set_target_properties(slibj PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../slibj/src/main/resources/lib")
swig_link_libraries(slibj slibc)




