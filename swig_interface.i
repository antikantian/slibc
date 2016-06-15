%module slibj

%{
#include "Swig.h"
#include "Types.h"
#include "FaceDetection.h"
%}

// Convert all C++ exceptions into java.lang.Exception
%exception {
    try {
        $action
    } catch(std::exception& e) {
        jclass clazz = jenv->FindClass("java/lang/Exception");
        jenv->ThrowNew(clazz, e.what());
        return $null;
    }
}

%exception largestFace {
    try {
        $action
    } catch(std::runtime_error& e) {
        jclass clazz = jenv->FindClass("co/quine/slibj/NoFacesFoundException");
        jenv->ThrowNew(clazz, e.what());
        return $null;
    }
}

%pragma(java) jniclassimports=%{
import java.io.*;
%}

%pragma(java) jniclasscode=%{
static {
    try {
        LoadLib.fromJar("/resources/lib/libslibj.jnilib");
    } catch (IOException e) {
        try {
            File model = new File("src/main/resources/lib/libslibj.jnilib");
            String absPath = model.getAbsolutePath();
            System.load(absPath);
        } catch (UnsatisfiedLinkError err) {
            err.printStackTrace();
            System.exit(1);
        }
    }
}
%}

%include "include/Types.h"
%include "include/Swig.h"
%include "include/FaceDetection.h"