#ifndef SLIBC_SWIG_H
#define SLIBC_SWIG_H

#ifdef SWIG
%include "std_string.i"
%include "std_vector.i"
%include "std_pair.i"
%include "various.i"
%template(RectangleVector) std::vector<sl::Rectangle>;
%template(ObjectModelVector) std::vector<sl::ObjectModel>;
%template(FloatVector) std::vector<float>;
%template(ByteVector) std::vector<signed char>;
#endif

#endif //SLIBC_SWIG_H
